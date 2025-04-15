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

CrusadersLanguageModified is a successor to [SCLanguage](https://github.com/LocalPiper/SCLanguage), continuing to follow the medieval theme of it's predecessor while including new features. This language is developed as a project for discipline "Compiler Development" at University of ITMO.

---

## 🛡️ Team Members

| Name                     | Role                      |
|--------------------------|---------------------------|
| [LocalPiper](https://github.com/LocalPiper) 🧙‍♂️            | Language Designer / Dev   |
| [uvusibuneka](https://github.com/uvusibuneka) ⚜️    | Grammar Knight / Dev    |

---


## 📜 Lexical Structure

| 🏷️ Token Name | 🧙‍♂️ Crusader Keyword | 🪄 Meaning / Description              |
|---------------|------------------------|--------------------------------------|
| `PLUS`        | `amass`                | Addition (`+`)                       |
| `MINUS`       | `sacrifice`            | Subtraction (`-`)                    |
| `STAR`        | `conjure`              | Multiplication (`*`)                |
| `SLASH`       | `split`                | Division (`/`)                      |
| `EQ`          | `claimeth`             | Equality (`==`)                     |
| `LT`          | `unworthy`             | Less than (`<`)                     |
| `GT`          | `mightier`             | Greater than (`>`)                  |
| `LEQ`         | `nohigher`             | Less than or equal (`<=`)           |
| `GEQ`         | `nobelow`              | Greater than or equal (`>=`)        |
| `NEQ`         | `reject`               | Not equal (`!=`)                    |
| `AND`         | `united`               | Logical AND (`&&`)                  |
| `OR`          | `either`               | Logical OR (`\|\|`)                   |
| `NOT`         | `deny`                 | Logical NOT (`!`)                   |
| `OP`          | `invoke`               | Open parenthesis (`(`)              |
| `CP`          | `dismiss`              | Close parenthesis (`)`)             |
| `OB`          | `commence`             | Open block (`{`)                    |
| `CB`          | `conclude`             | Close block (`}`)                   |
| `IF`          | `suppose`              | If statement                        |
| `ELSE`        | `elsewise`             | Else statement                      |
| `WHILE`       | `aslongas`             | While loop                          |
| `VAR`         | `henceforth`           | Variable declaration                |
| `TRUE`        | `aye`                  | Boolean `true`                      |
| `FALSE`       | `nay`                  | Boolean `false`                     |
| `PRINT`       | `proclaim`             | Print statement                     |
| `ASSIGN`      | `bestow`               | Assignment (`=`)                    |
| `EOL`         | *(newline)*            | End of line                         |
| `NUMBER`      | *(digits)*             | Integer literals                    |
| `IDENTIFIER`  | *(identifiers)*        | Variable/function names             |
| `STRING`      | *(quoted text)*        | String literals                     |


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
| 1   | Lexer: New naming          | Rename keywords so they would make more sense  | ⚙️ Mandatory   | ✅ DONE         |
| 2   | Interpreter: short-circuit          | Make logical operators (AND, OR) short circuit to remove unnecessary computations  | ⚙️ Mandatory   | 🛠️ IN PROGRESS         |
| 3   | Parser + Interpreter: error handling          | Add better error handling. For compiletion errors - user should be able to see on which line of code an error occurred. For runtime errors - actual error messages instead of C++ messages | ⚙️ Mandatory   | ❌ NOT IMPLEMENTED         |
| 4   | Parser + Interpreter: FP values support          | Add floating point values support  | ⚙️ Mandatory   | ❌ NOT IMPLEMENTED         |
| 5   | Parser + Interpreter: arrays support          | Add arrays support. User should be able to iterate over arrays and strings  | ⚙️ Mandatory   | ❌ NOT IMPLEMENTED         |
| 6   | Parser + Interpreter: functions support          | Add functions support  | ⚙️ Mandatory   | ❌ NOT IMPLEMENTED         |
| 7   | Tester: cover with tests          | Come up with tests for the language. Try reaching maximum test coverage  | ⚙️ Mandatory   | ❌ NOT IMPLEMENTED         |
| 8   | Parser: comments         | Add comments support. Both single line and multiline  | ✨ Additional   | ❌ NOT IMPLEMENTED         |
| 9   | Parser + Interpreter: ternary IF         | Add ternary IF support. Syntax: (condition)? true : false  | ✨ Additional   | ❌ NOT IMPLEMENTED         |
| 10   | Parser + Interpreter: for loops          | Add 'for' loops. 'For' loops are desugared while loops  | ✨ Additional   | ❌ NOT IMPLEMENTED         |
| 11   | Parser + Interpreter: break/continue          | Add ability to break loops and continue iteration | ✨ Additional   | ❌ NOT IMPLEMENTED         |
| 12   | Parser + Interpreter: iterator          | Add ability to iterate over values in array (or string). For example, for (x : arr) or for (c : str). Should be implemented after array support and for loop support  | ✨ Additional   | ❌ NOT IMPLEMENTED         |
| 13   | Parser + Interpreter: closures          | Add ability to make closures | ✨ Additional   | ❌ NOT IMPLEMENTED         |
| 14   | Parser + Interpreter: lambda functions          | Add lambda functions support | ✨ Additional   | ❌ NOT IMPLEMENTED         |

### 🛞 Stage 2: Assembly
TODO
