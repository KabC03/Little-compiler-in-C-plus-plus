# Language features and design #
## 10 Aug 2024 ##



### Introduction ###

This project aims to create a simple 'high level' assembly language that can be quickly compiled for a range of ISAs.
The compiler backend is designed to be highly modular such that it is simple to generate basic assembly for any ISA.
The compiler is a causal system - employing a linear scanning approach through source code to generate output.
No major optimisations are employed; but register allocation is based on a last recently use (LRU) policy.

No type checking or bounds checking is employed in the compiler.



### Programming ###



#### Declaring a variable ####

Declare a variable with the 'dec' keyword.


- Variables cannot be declared more than once
- Variables may be initialised with expressions (expressions are evaluated left to right)
- All types have the same size
- Note due to no typechecking it is possible to dereference a standard integer as a pointer

__Example:__
Declare an integer variable named 'myVar123' that is initialised with a value of 10

```
dec myVar123 = 10;
```


#### Setting a variable ####

Set a variable to another value with the 'set' keyword

- Expressions are evaluated left to right


__Example:__
Set the variable 'myVariable123' to 100 + x

```
set myVar123 = 99 + 1 + x; //Assuming variables are declared elsewhere
```



#### Defining a function ####

Functions are declared with the 'fnc' keyword and ended with 'endfn'

- All functions share the same scope
- A function cannot be declared more than once


__Example:__
Declare a function named my_function

```
fnc my_function:

    set x = x + 1; //Note that 'x' must be declared somewhere else in the program already

endfn;
```


#### Calling a function ####

Functions are called with the 'cal' keyword

- Functions are statements not expressions, so cannot be assigned to a value



__Example:__
Call a function called 'my_function'



```
cal my_function //Assuming the function is defined above this statement
```



#### If statements ####

Standard conditional logic structure - where the statement runs if the condition is true by use of the 'if' keyword


__Example:__
Check if x equals 1 + 2 + y, if so then increment x


```
if (x == 1 + 2 + y): //Assuming values are defined elsewhere
    
    x = x + 1;

endif;
```



#### goto statements ####

Unconditionally jumps to a label by use of the 'gto' keyword


__Example:__
Go to the label 'my_label'

```
gto my_label;
```



#### Label declaration ####

Declare a label for jumping to by use of the 'lbl' keyword

- Labels cannot be declared more than once


__Example:__
Declare a label 'my_label'

```
lbl my_label;
```



#### Comments ####

Everything after a '//' to a '\n' delimeter is considered a comment

- There are no character limitations of what can be placed within a comment
- Comments may appear after another instruction

__Example:__
Write a comment with the text 'hello this is a comment'

```
//Hello this is a comment
```




### Arithmatic operators ###


'+' - Addition
'-' - Subtraction
'/' - Division
'\*' - Multiplication
'%' - Modulo
'==' - Equal to
'!=' - Not equal to
'>>' - Greater than
'<<' - Less than
'>=' - Greater or equal to
'<=' - Less or equal to
'?' - Pointer dereference

















