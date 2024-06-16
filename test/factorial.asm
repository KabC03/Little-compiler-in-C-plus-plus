#Prints the factorial of an input number



[J] JUM start



[L] LABEL factorial
    [C] BEQ_I R2 R0 set_one_and_return 

    [I] ADD_I R4 R2 0 
    [I] ADD_I R2 R2 -1 
    [J] JAL factorial 


    [I] ADD_I R4 R4 1
    [R] MUL_I R3 R4 R3 
    [J] JRT R1

[L] LABEL set_one_and_return
    [I] ADD_I R3 R0 1
    [J] JRT R1 

[L] LABEL start
    [A] INPUT R2 R2 INTEGER
    [I] SUB_I R2 R2 1


    [J] JAL factorial
    [A] PRINT R3 R3 INTEGER





