# Language

The language is a compiled/intepreted low level language designed to mesh well with a variety of computer organisations.

Similar to C, a high level of control is provided over the computer's resources while also providing a high level of abstraction over control structures.

No runtime checks are performed on compiled code. It is possible to write and execute unsafe code.




# Syntax

__Note: Whitespace (including indentation) is ignored__


#### Variable declaration

- Declarations are performed at the beggining of the program in the 'data' section
- Each variable has a base type as well as type modifiers

  __Datatype size can be modified with compiler flags__

| Base datatypes | Syntax      | 
|----------------|-------------|
| integer        | int         |
| IEEE754 float  | float       |
| UTF8 character | char        |

| Datatype modifiers | Syntax      | Extra                                                           |
|--------------------|-------------|-----------------------------------------------------------------|
| array              | [n]         | static array holding n of the base datatype, zero base indexing |
| pointer            | n@          | pointer with indirection level n                                |



##### Examples

    ||data||          # Data section specifies variable declarations are made here
    
      int: x |2@;       # A double pointer named 'x' that points to an integer
      char: abc |[20];  # An array of 20 characters
      float: number|;   #A float named 'number'
    
    ||program||       # Rest of the program is below

















































































































































































