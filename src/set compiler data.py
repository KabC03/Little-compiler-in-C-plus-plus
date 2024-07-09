# 10, Jul, 24
# This file generates the compiler data.h and compiler data.c files



#Print a newline every newLineConstant lines in the .c and .h files
newLineConstant = 5;


defineNameNumberOfTokens = "NUMBER_OF_TOKENS";
defineNameMaxTokenLength = "MAX_TOKEN_LENGTH";

hFile = "./compiler data.h";
cFile = "./compiler data.c";
headerGuardName = "COMPILE_H";

#Tokens to append to the files
tokens = {

    #Datatypes
    "int" : "TOK_INT", "flt" : "TOK_FLT", "chr" : "TOK_CHR", "@" : "TOK_PTR",

    #Operators
    "+" : "TOK_ADD", "-" : "TOK_SUB", "*" : "TOK_MUL", "/" : "TOK_DIV","%%" : "TOK_MOD","||" : "TOK_OR", "&&" : "TOK_AND",
    "==" : "TOK_EQUAL_TO", "!=" : "TOK_NOT_EQUAL_TO", ">=" : "TOK_GREATER_EQUAL_TO", "<=" : "TOK_LESS_EQUAL_TO", ">>" : "TOK_GREATER_TO", "<<" : "TOK_LESS_TO", 


    #Control flow
    "if" : "TOK_IF", "gto" : "TOK_GTO", "lbl" : "TOK_LBL",

    #Functions
    "fn" : "TOK_FN", "ret" : "TOK_RET",

    #Inbuilt functions
    "allocate" : "TOK_ALLOCATE", "free" : "TOK_FREE", "sizeof" : "TOK_SIZEOF",

    #Organisation
    "//" : "TOK_COMMENT",

    #Misc
    "<" : "TOK_OPEN_ANGLE", ">" : "TOK_CLOSE_ANGLE", "[" : "TOK_OPEN_SQUAER", "]" : "TOK_CLOSE_SQUARE", 
    "(" : "TOK_OPEN_PAREN", ")" : "TOK_CLOSE_PAREN", "{" : "TOK_OPEN_CURLEY", "}" : "TOK_CLOSE_CURLEY", 
    "," : "TOK_COMMA", "." : "TOK_DOT", ";" : "TOK_SEMICOLEN",
};

numberOfTokens = 0;
maxTokenSize = 0;




librariesToInclude = [

    "<stdlib.h>",
    "<stdio.h>",
    "<stdbool.h>",
    "<string.h>",
    "<stdint.h>",
    "\"vector.h\"",
    "\"datastructures.h\"",
    "\"static hashmap.h\"",
];



#Write to the .h file
def write_h_file():

    try:
        
        with open(hFile, 'w') as file:
        
            #Write header guards
            file.write("#ifndef " + str(headerGuardName) + "\n");
            file.write("#define " + str(headerGuardName) + "\n\n\n");

            #Define constants
            file.write("#define " + str(defineNameNumberOfTokens) + " " + str(numberOfTokens) + "\n");
            file.write("#define " + str(defineNameMaxTokenLength) + " " + str(maxTokenSize) + "\n\n\n");


            #Include libraries
            for library in librariesToInclude:
                file.write("#include " + str(library) + "\n");
        

            file.write("\n\ntypedef enum VALID_TOKEN_ENUM {\n");

            counter = 0;
            for value in tokens.values():

                if counter % newLineConstant == 0:
                    file.write("\n\n");

                file.write("    " + str(value) + " = " + str(counter) + ",\n");
                counter += 1;

            file.write("\n\n} VALID_TOKEN_ENUM;\n");

            file.write("\n\n#endif //" + str(headerGuardName) + "\n\n");
            file.write("//NOTE: Generated by python script\n\n\n\n");

        return True; 
    
    
    except:
        return False;




#Write to the .c file
def write_c_file():

    global numberOfTokens;
    global maxTokenSize;

    numberOfTokens = len(tokens);
    maxTokenSize = 0;
    for token in tokens:
        if len(token) > maxTokenSize:
            maxTokenSize = len(token);

    try:
        with open(cFile, 'w') as file:
            file.write("#include " + "\"" + str(hFile) + "\"\n\n\n");


            file.write("const char validTokens[" + str(defineNameNumberOfTokens) + "][" + str(defineNameMaxTokenLength) + "] = {\n");

            counter = 0;
            for key in tokens.keys():

                if counter % newLineConstant == 0:
                    file.write("\n\n\n\n    ");

                file.write("\"" + key + "\",");
            
                counter += 1;

            file.write("\n\n};\n\n");
        
            file.write("//NOTE: Generated by python script\n\n\n\n");
        return True; 
    
    
    except:
        return False;



#Main function
def main():
    
    if(write_c_file() == False):
        print("Failed to write data to .c file: " + str(cFile));
        return -1;


    if(write_h_file() == False):
        print("Failed to write data to .c file: " + str(hFile));
        return -2;


    return 0;







if __name__ == "__main__":
    main();













