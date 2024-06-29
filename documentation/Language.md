# Language

The language is a compiled/intepreted low level language designed to mesh well with a variety of computer organisations.

Similar to C, a high level of control is provided over the computer's resources while also providing a high level of abstraction over control structures.

No runtime checks are performed on compiled code. It is possible to write and execute unsafe code.




# Syntax

__Note: Whitespace (including indentation) is ignored__


#### Variable declaration

- Declarations are performed at the beggining of the program in the 'data' section
- Each variable has a base type as well as type modifiers
- Variable types cannot be changed past the 'program' declaration
- Expressions must not appear in declarations
- A NULL pointer points to address 0x0

  __Datatype size can be modified with compiler flags__

| Base datatypes | Syntax      | 
|----------------|-------------|
| integer        | int         |
| IEEE754 float  | float       |
| UTF8 character | char        |
| pointer        | @           |



##### Example

    $data$              # Data section specifies variable declarations are made here
    
      int @@: x;        # A double pointer named 'x' that points to an integer
      char: abc;        # An array of 20 characters
      float: number|;   #A float named 'number'
    
    $program$           # Rest of the program is below




#### Variable assignments

- Variables can be updated in the program section
- An expresion may appear as any part of the assignment

##### Example

    $data$
      # Do something
    
    $program$
  
      x[5 + y] = 100;    # Index x at the index 5 + y then assign 100 to this position
      @@(y+2) = x;       # Add two to y then dereference it twice


#### If statement

- Check if two values meet a condition
- Can chain conditions together with || (or) and && (and) tokens
  - Expression is evaluated via BODMAS, && has higher precedence than ||
- If statements are concluded with an 'end'
- Expressions may appear as either operand in the statement


| Condition               | Syntax       | 
|-------------------------|--------------|
| Equal                   | ==           |
| Not equal               | !=           |
| Greater than            | >            |
| Less than               | <            |
| Greater than or equal   | >=           |
| Less than or equal      | <=           |

##### Example

    $data$
      # Something
    $program$

      if((x == 0 || y == 3) && x != 99): # Check if x == 0 or y == 3 first, then AND that with if x != 99
        # Do something

      elif(x == 0): # If the top if statement is false test this condition
        # Do something else
        
      elif(y == 0): # Another else if statement
        # Do something else

      else: # If neither conditions are true the else statement will run
        # Do this if the other two are not true
      end;



#### For loop


- Iterate through a number range
- For loops are concluded with an 'end'
- The iterating variable will go out of scope and be cleared once the loop completes
- Expressions may appear as the start, stop and iteration values in the loop

##### Example

    $data$
      # Something
    $program$

      for(i, 0, 10, 1): # For i = 0 to i == 10, run the loop. Each time increment i by 1
        # Do something
      end;




#### While loop

- Run while a condition is true
- Check if two values meet a condition
- Can chain conditions together with || (or) and && (and) tokens
  - Expression is evaluated via BODMAS, && has higher precedence than ||
- If statements are concluded with an 'end'
- Expressions may appear as either operand in the statement


| Condition               | Syntax       | 
|-------------------------|--------------|
| Equal                   | ==           |
| Not equal               | !=           |
| Greater than            | >            |
| Less than               | <            |
| Greater than or equal   | >=           |
| Less than or equal      | <=           |


##### Example


    $data$
      # Something
    $program$

      while(x != 2 || y == 0):
        # Do something
      end;
  



#### Declaring functions

- Functions allow the same code to be used at multiple places in the program - preventing code duplication
- Declared in the 'function' section of the program above 'program'
- This section does not need to be present if no functions are defined
- All arguments are passed by reference
- Functions have their own 'data' and 'program' sections
  - Variables must be declared in the data section before their use in 'program'
- Function declarations are finished with a return
- Arrays cannot be returned

##### Example

      $data$
        # Something
      $function$
  
        decl my_function(int x, int y, char @@ z, ...) -> int @:
            $data$
              # Data here
            $program$

              result = x;
              return result;

      $program$
        # Something
      


#### Calling functions

- Functions are called in the 'program' section with the 'call' keyword
- Can be assigned to a value

##### Example
      $data$
        # Something
      $function$
        # Something
  
      $program$
        x[i] = my_function(a,b,c); # Assign the array x at index i to the return value of my_function when passed values a,b and c




#### Dynamic memory functions

- Allocate and free are used to request and free dynamic memory the program requires

  
  - Allocate takes the datatype and number of the datatype to allocate memory for
    - Continguous block of memory returned, can be indexed into
    - If an array is passed as a datatype, its value must be a constant
    - A NULL pointer of value 0 is returned if allocation fails
    - On success a pointer to the new memory block is returned


  - Free frees a variable given a pointer
    - Does not return a value
   
    
__Memory saftey is NOT checked at compiletime or runtime - includes OOB access, null pointer access and overflow errors__

      $data$
        # Something
      $function$
        # Something
  
      $program$
        x = allocate(10, int |@); # Allocate space for 10 integer pointers
        y = allocate(1, float |); # Allocate space for 1 float
        free(x);                  # Free dynamic memory
        free(y);                  # Free dynamic memory





























































































































