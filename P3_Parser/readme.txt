# Parser Project3

## Overview

This project is a simple parser implementation with static semantics checking. It includes a basic parser for a custom language, a symbol table for variable tracking, and static semantics checking functionality.

## Project Structure

- **main.c:** The main program that initiates the parsing process.
- **scanner.c:** Contains the code for lexical analysis, tokenizing the input source code.
- **parser.c:** Implements a basic recursive descent parser for the custom language.
- **testTree.c:** Defines the data structure for the parse tree.
- **staticSemantics.c:** Implements static semantics checking, including symbol table operations.
- **symbolTable.c:** Provides a simple symbol table implementation.

## How to Build

To build the project, navigate to the project directory in your terminal and run:

```bash
make
```

This will compile the source files and generate an executable named `P3`.

## How to Run

After building the project, run the executable:

```bash
./P3 input.txt
```

Replace `input.txt` with the path to your source code file.

## Example

Suppose you have the following source code in a file named `example.txt`:

```text
let x = 42;
print(x);
```

To parse and perform static semantics checking on this code, run:

```bash
./P3 example.txt
```

The program will output any errors related to syntax and static semantics.