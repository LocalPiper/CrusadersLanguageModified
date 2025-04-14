# 🏰 CrusadersLanguageModified (.cl2)

> **"May your compiler never segfault, and your registers never spill."**

CrusadersLanguageModified is a custom programming language forged with the ancient wisdom of **Flex**, **Bison**, and the legendary steel of **C++**. The language embraces a medieval aesthetic — every keyword speaks in the tongue of knights, squires, and lords.

This project includes a full toolchain:
- Lexical analyzer
- Parser
- Abstract Syntax Tree (AST)
- (WIP) Semantic analyzer
- (WIP) RISCV32 codegen

---

## 🗂️ Table of Contents

- [🧾 Description](#-description)
- [🛡️ Team Members](#%EF%B8%8F-team-members)
- [📜 Lexical Structure](#-lexical-structure)
- [🏗️ Parsing Rules](#%EF%B8%8F-parsing-rules)
- [🗺️ Development Stages](#%EF%B8%8F-development-stages)
  - [🌲 Stage 1 Treewalker](#-stage-1-treewalker)
  - [🛞 Stage 2 Assembly](#-stage-2-assembly)


---

## 🧾 Description

CrusadersLanguageModified is a successor to [SCLanguage](https://github.com/LocalPiper/SCLanguage), continuing to follow the medieval theme of it's predecessor while including new features. This language is developed as a project for discipline "Compiler Developement" at University of ITMO.

---

## 🛡️ Team Members

| Name                     | Role                      |
|--------------------------|---------------------------|
| LocalPiper 🧙‍♂️            | Language Designer / Dev   |
| uvusibuneka ⚜️    | Grammar Knight / Dev    |

---


## 📜 Lexical Structure

TODO

## 🏗️ Parsing Rules

TODO

## 🗺️ Development Stages
Here is what we are going to implement in our language. Each task is marked with:
- ✅ DONE
- 🛠️ IN PROGRESS
- ❌ NOT IMPLEMENTED
Tasks can be mandatory (features that WILL be implemented) and additional (features that MAY be implemented)

### 🌲 Stage 1: Treewalker
| #️⃣ | Feature Name         | Description                                     | Priority    | Status           |
|-----|---------------------|-------------------------------------------------|-------------|------------------|
| 1   | Lexer: New naming          | Rename keywords so they would make more sense  | ⚙️ Mandatory   | 🛠️ IN PROGRESS         |
| 2   | Interpreter: short-circuit          | Make logical operators (AND, OR) short circuit to remove unnecessary computations  | ⚙️ Mandatory   | ❌ NOT IMPLEMENTED         |
| 3   | Parser + Interpreter: error handling          | Add better error handling. For compiletion errors - user should be able to see on which line of code an error occurred. For runtime errors - actual error messages instead of C++ messages | ⚙️ Mandatory   | ❌ NOT IMPLEMENTED         |
| 4   | Parser + Interpreter: FP values support          | Add floating point values support  | ⚙️ Mandatory   | ❌ NOT IMPLEMENTED         |
| 5   | Parser + Interpreter: arrays support          | Add arrays support. User should be able to iterate over arrays and strings  | ⚙️ Mandatory   | ❌ NOT IMPLEMENTED         |
| 6   | Parser + Interpreter: functions support          | Add functions support  | ⚙️ Mandatory   | ❌ NOT IMPLEMENTED         |
| 7   | Parser: comments         | Add comments support. Both single line and multiline  | ✨ Additional   | ❌ NOT IMPLEMENTED         |
| 8   | Parser + Interpreter: ternary IF         | Add ternary IF support. Syntax: (condition)? true : false  | ✨ Additional   | ❌ NOT IMPLEMENTED         |
| 9   | Parser + Interpreter: for loops          | Add 'for' loops. 'For' loops are desugared while loops  | ✨ Additional   | ❌ NOT IMPLEMENTED         |
| 10   | Parser + Interpreter: break/continue          | Add ability to break loops and continue iteration | ✨ Additional   | ❌ NOT IMPLEMENTED         |
| 11   | Parser + Interpreter: iterator          | Add ability to iterate over values in array (or string). For example, for (x : arr) or for (c : str). Should be implemented after array support and for loop support  | ✨ Additional   | ❌ NOT IMPLEMENTED         |
| 12   | Parser + Interpreter: closures          | Add ability to make closures | ✨ Additional   | ❌ NOT IMPLEMENTED         |
| 13   | Parser + Interpreter: lambda functions          | Add lambda functions support | ✨ Additional   | ❌ NOT IMPLEMENTED         |

### 🛞 Stage 2: Assembly
TODO
