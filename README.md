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
| `MOD`         | `remnant`              | Modulo (`%`)                        |
| `EQ`          | `claimeth`             | Equality (`==`)                     |
| `LT`          | `unworthy`             | Less than (`<`)                     |
| `GT`          | `mightier`             | Greater than (`>`)                  |
| `LEQ`         | `nohigher`             | Less than or equal (`<=`)           |
| `GEQ`         | `nobelow`              | Greater than or equal (`>=`)        |
| `NEQ`         | `reject`               | Not equal (`!=`)                    |
| `AND`         | `united`               | Logical AND (`&&`)                  |
| `OR`          | `either`               | Logical OR (`\|\|`)                 |
| `NOT`         | `deny`                 | Logical NOT (`!`)                   |
| `OP`          | `invoke`               | Open parenthesis (`(`)              |
| `CP`          | `dismiss`              | Close parenthesis (`)`)             |
| `OB`          | `commence`             | Open block (`{`)                    |
| `CB`          | `conclude`             | Close block (`}`)                   |
| `IF`          | `suppose`              | If statement                        |
| `ELSE`        | `elsewise`             | Else statement (also used in ternary if)               |
| `QUESTION`    | `perchance`            | Ternary if expression (`?`)         |
| `WHILE`       | `aslongas`             | While loop                          |
| `FOR`         | `upon`                 | For loop                            |
| `BREAK`       | `flee`                 | Break out of loop                   |
| `CONTINUE`    | `onward`               | Continue to next iteration of loop  |
| `VAR`         | `henceforth`           | Variable declaration                |
| `TRUE`        | `aye`                  | Boolean `true`                      |
| `FALSE`       | `nay`                  | Boolean `false`                     |
| `PRINT`       | `proclaim`             | Print statement                     |
| `ASSIGN`      | `bestow`               | Assignment (`=`)                    |
| `FUNCTION`    | `inscribe`             | Function definition                 |
| `COMMA`       | `also`                 | Comma (`,`) separator for function calls and definitions                |
| `RETURN`      | `yield`                | Return statement                    |
| `EOL`         | *(newline)*            | End of line                         |
| `NUMBER`      | *(digits)*             | Integer literals                    |
| `DOUBLE`      | *(digits, separated by one `.`)* | Floating point values     |
| `IDENTIFIER`  | *(identifiers)*        | Variable/function names             |
| `STRING`      | *(quoted text)*        | String literals                     |

## 🏗️ Parsing Rules

Parsing productions are as follows, presented in BNF:

```bnf
program ::= statements

statements ::= statement EOL statements
             | statement EOL
             | EOL statements
             | EOL

statement ::= print_statement
            | expression_statement
            | if_statement
            | while_statement
            | for_statement
            | break_statement
            | continue_statement
            | block
            | function_declaration
            | return_statement

function_declaration ::= FUNCTION IDENTIFIER OP parameters CP block

return_statement ::= RETURN expression

parameters ::= IDENTIFIER
             | IDENTIFIER COMMA parameters
             | ε

block ::= OB statements CB

print_statement ::= PRINT expression

expression_statement ::= expression

if_statement ::= IF OP expression CP block ELSE block
               | IF OP expression CP block

while_statement ::= WHILE OP expression CP block

for_statement ::= FOR OP expression COMMA expression COMMA expression CP block

break_statement ::= BREAK

continue_statement ::= CONTINUE

expression ::= assignment QUESTION expression ELSE expression
             | assignment

assignment ::= IDENTIFIER ASSIGN assignment
             | VAR IDENTIFIER ASSIGN assignment
             | logical_or

logical_or ::= logical_or OR logical_and
             | logical_and

logical_and ::= logical_and AND equalty
              | equalty

equalty ::= comparison EQ comparison
          | comparison NEQ comparison
          | comparison

comparison ::= term LT term
             | term GT term
             | term GEQ term
             | term LEQ term
             | term

term ::= term PLUS factor
       | term MINUS factor
       | factor

factor ::= factor STAR unary
         | factor SLASH unary
         | factor MOD unary
         | unary

unary ::= MINUS unary
        | NOT unary
        | primary

primary ::= FALSE
          | TRUE
          | NUMBER
          | DOUBLE
          | IDENTIFIER
          | STRING
          | OP expression CP
          | function_call

function_call ::= function_call OP arguments CP
                | IDENTIFIER OP arguments CP

arguments ::= expression
            | expression COMMA arguments
            | ε

```

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
| 2   | Interpreter: short-circuit          | Make logical operators (AND, OR) short circuit to remove unnecessary computations  | ⚙️ Mandatory   | ✅ DONE         |
| 3   | Parser + Interpreter: error handling          | Add better error handling. For compiletion errors - user should be able to see on which line of code an error occurred. For runtime errors - actual error messages instead of C++ messages | ⚙️ Mandatory   | ❌ NOT IMPLEMENTED         |
| 4   | Parser + Interpreter: FP values support          | Add floating point values support  | ⚙️ Mandatory   | ✅ DONE         |
| 5   | Parser + Interpreter: arrays support          | Add arrays support. User should be able to iterate over arrays and strings  | ⚙️ Mandatory   | ✅ DONE         |
| 6   | Parser + Interpreter: functions support          | Add functions support  | ⚙️ Mandatory   | ✅ DONE         |
| 7   | Tester: cover with tests          | Come up with tests for the language. Try reaching maximum test coverage  | ⚙️ Mandatory   | ❌ NOT IMPLEMENTED         |
| 8   | Parser: comments         | Add comments support. Both single line and multiline  | ✨ Additional   | ❌ NOT IMPLEMENTED         |
| 9   | Parser + Interpreter: ternary IF         | Add ternary IF support. Syntax: (condition)? true : false  | ✨ Additional   | ✅ DONE         |
| 10   | Parser + Interpreter: for loops          | Add 'for' loops. 'For' loops are desugared while loops  | ✨ Additional   | ✅ DONE         |
| 11   | Parser + Interpreter: break/continue          | Add ability to break loops and continue iteration | ✨ Additional   | ✅ DONE         |
| 12   | Parser + Interpreter: iterator          | Add ability to iterate over values in array (or string). For example, for (x : arr) or for (c : str). Should be implemented after array support and for loop support  | ✨ Additional   | ❌ NOT IMPLEMENTED         |
| 13   | Parser + Interpreter: closures          | Add ability to make closures | ✨ Additional   | ❌ NOT IMPLEMENTED         |
| 14   | Parser + Interpreter: lambda functions          | Add lambda functions support | ✨ Additional   | ❌ NOT IMPLEMENTED         |

### 🛞 Stage 2: Assembly

TODO
