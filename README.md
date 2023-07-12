# BORG Interpreter in C++
This repository contains a C++ interpreter for the BORG language. The BORG language includes a set of simple commands, as described below.

# BORG Language Commands
START - FINISH blocks: These commands indicate different scopes.

cpp
Copy code
START
// Your code here
FINISH
COM: Single line comments. Text following this command on the same line will be ignored.

cpp
Copy code
COM This is a comment
VAR: Variable Declaration. This adds a new variable to the hash table.

cpp
Copy code
VAR varName
Assignment Statement: This assigns a value to a variable.

cpp
Copy code
varName = expression
Increment and Decrement Operators: These operators increment or decrement a variable.

cpp
Copy code
varName++
varName--
Expressions: Expressions are limited to unary and binary arithmetic operations, or variable names. The supported operators include: + (plus), - (minus), / (divide), * (multiply), % (modulo), ^ (exponent).

cpp
Copy code
varName = var1 + var2 - var3 / var4 * var5 % var6 ^ var7
PRINT: This command prints the result of an expression. If the expression is a variable and this variable is not in scope, an error message is displayed.

cpp
Copy code
PRINT expression
PRINT varName
Errors: The interpreter assumes the source file is correct. Syntax errors, if encountered, will be disregarded.

# Screenshots
![image](https://github.com/OppedRawen/BORG/assets/95009568/ff37b25c-4c07-4cec-bf8d-9ee673a90651)
