# KMap solver
Karnaugh Map solver on 4 var map: this is a side project we made in the sophomore year while taking a Digital Circuit Design course to help solving Karnaugh Maps. It's not perfect, but it works. It's a simple program that takes a Karnaugh Map expression and gives you the solution. It can handle up to 4 variables.

## How to use
It is a simple kMap.exe file, just run it and follow the instructions. 

## Example
when you run the program, you will see the following:
```
Your literals are A, B, C and D capital or small letters (you can mix in between) in addition to these letters you only can enter the plus sign "+" and the apostrophe sign to negate the literal (e.g., A' or b')

For example A'B'CD+A'BCD+ABCD+AB'CD+ABC'D'+ABC'D+ ABCD' will give you the following kMap:

0, 0, 1, 0,
0, 0, 1, 0,
1, 1, 1, 1,
0, 0, 1, 0,
```
you can enter the expression you want to solve, and the program will give you the solution.
```
A'Bc'+abc'+ ab'c +a'b'c
```
will give you the following:
```
your input is: 
A'BC'+ABC'+AB'C+A'B'C

0, 0, 1, 1, 
1, 1, 0, 0,
1, 1, 0, 0, 
0, 0, 1, 1, 
```