#VM intepreter ASM
#Prints letters from a start to stop char

    [J] JUM start


[L] LABEL start


    [I] ADD_I R3 R0 1


    [A] INPUT R2 R3 INTEGER
    [A] INPUT R4 R3 INTEGER

    [I] ADD_I R4 R4 1
[L] LABEL for_start
    [C] BEQ_I R2 R4 for_end

    [A] PRINT R2 R3 INTEGER

    [I] ADD_I R2 R2 1

    [J] JUM for_start
[L] LABEL for_end



