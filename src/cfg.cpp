#include "cfg.hpp"
#include "ir_struct.hpp"
#include <unordered_map>

std::vector<BasicBlock *> buildBasicBlocks(const IR &code) {
  std::vector<BasicBlock *> blocks;
  std::unordered_map<std::string, BasicBlock *> labelToBlock;
  std::unordered_map<int, BasicBlock *> startToBlock;

  BasicBlock *current = new BasicBlock();
  current->name = "entry";
  blocks.push_back(current);

  for (size_t i = 0; i < code.size(); ++i) {
    const auto &instr = code[i];

    if (instr.opcode == IROpcode::LABEL ||
        instr.opcode == IROpcode::FUNC_BEGIN) {
      current = new BasicBlock();
      current->name = instr.result;
      labelToBlock[instr.result] = current;
      blocks.push_back(current);
    }

    current->instructions.push_back(instr);

    if (instr.opcode == IROpcode::JUMP ||
        instr.opcode == IROpcode::JUMP_IF_FALSE ||
        instr.opcode == IROpcode::FUNC_END) {
      current = new BasicBlock();
      current->name = "block_" + std::to_string(i);
      blocks.push_back(current);
    }
  }

  return blocks;
}

void linkBasicBlocks(
    std::vector<BasicBlock *> &blocks,
    std::unordered_map<std::string, BasicBlock *> &labelToBlock) {
  for (size_t i = 0; i < blocks.size(); ++i) {
    auto *block = blocks[i];
    if (block->instructions.empty())
      continue;

    const IRInstruction &last = block->instructions.back();

    if (last.opcode == IROpcode::JUMP) {
      auto it = labelToBlock.find(last.arg1);
      if (it != labelToBlock.end()) {
        block->succ.push_back(it->second);
        it->second->pred.push_back(block);
      }
    } else if (last.opcode == IROpcode::JUMP_IF_FALSE) {
      auto it = labelToBlock.find(last.arg1);
      if (it != labelToBlock.end()) {
        block->succ.push_back(it->second);
        it->second->pred.push_back(block);
      }
      if (i + 1 < blocks.size()) {
        block->succ.push_back(blocks[i + 1]);
        blocks[i + 1]->pred.push_back(block);
      }
    } else {
      if (i + 1 < blocks.size()) {
        block->succ.push_back(blocks[i + 1]);
        blocks[i + 1]->pred.push_back(block);
      }
    }
  }
}

std::vector<BasicBlock *> buildCFG(const IR &code) {
  auto blocks = buildBasicBlocks(code);
  std::unordered_map<std::string, BasicBlock *> labelToBlock;

  for (auto *block : blocks) {
    if (!block->instructions.empty()) {
      const auto &instr = block->instructions.front();
      if (instr.opcode == IROpcode::LABEL ||
          instr.opcode == IROpcode::FUNC_BEGIN) {
        labelToBlock[instr.result] = block;
      }
    }
  }

  linkBasicBlocks(blocks, labelToBlock);
  return blocks;
}

IR flattenCFG(const std::vector<BasicBlock *> &cfg) {
  IR flattened;
  for (auto *block : cfg) {
    flattened.insert(flattened.end(), block->instructions.begin(),
                     block->instructions.end());
  }
  return flattened;
}
