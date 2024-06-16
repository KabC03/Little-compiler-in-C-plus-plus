#VM intepreter ASM
#Prints letters from a start to stop char

    [J] JUM start


[L] LABEL start
    #char charVal = 'a'; for(int i = 0; i < 26; i++) {printf("%c", charVal++);};

    [I] ADD_I R3 R0 1


    [A] INPUT R2 R3 INTEGER
    [A] INPUT R4 R3 INTEGER


[L] LABEL for_start
    [C] BEQ_I R2 R4 end

    [A] PRINT R2 R3 INTEGER

    [I] ADD_I R2 R3 1

    [J] JUM for_start
[L] LABEL for_end



