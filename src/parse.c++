//30 Aug 2024
#include "parse.h++"
#define APPEND_INPUT_LABEL_STR "__USR"
#define OPERAND_RESERVE 10
#define LABEL_RESERVE 10
#define IF_STACK_RESERVE 10
#define internal_macro_parser_print_invalid_token(stringToPrint, tokenToPrint)\
    cout << stringToPrint;\
    debug_tokenise_singular_token_print(tokenToPrint);\
    cout << endl;






/**
 * parser_initialise
 * ===============================================
 * Brief: Initialise register vector with empty values and set the global file pointer
 * 
 * Param: 
 *        outputFilePath
 * 
 * Return: bool 
 * 
 */
bool parser_initialise(string outputFilePath, ParserData &parserData) {

    //outputFile = outputFileSet;

    parserData.outputFile.open(outputFilePath);
    if(parserData.outputFile.is_open() == false) {
        cout << "ERROR: Unable to open output file" << endl;
        return false;
    }

    Operand operand;
    operand.memoryOffset = 0;
    operand.isFree = true;
    parserData.registerStates.resize(NUMBER_OF_REGISTERS, operand); //Fill with operand

    parserData.operandMap.reserve(OPERAND_RESERVE);
    parserData.knownLabels.reserve(LABEL_RESERVE);


    return true;
}




//Parse a variable declaration
bool internal_parse_dec(vector<Token> &tokens, size_t numberOfTokens, ParserData &parserData) {

    static size_t newVarMemOffset = 0; //Base offset address
    if(numberOfTokens < 3) {
        cout << "ERROR: Expected declaration expression but recieved: " << endl;
        return false;
    } else {

        //Expect a variable name
        if(tokens[1].tokenType != TOK_STRING) {
            internal_macro_parser_print_invalid_token("ERROR: Expected variable: \n", tokens[1]);
        }

        //Check for redefinition
        auto varMapIterator = parserData.operandMap.find(tokens[1].string);
        if(varMapIterator != parserData.operandMap.end()) { //Variable found
            cout << "ERROR: Redefinition of '" << tokens[1].string << "'" << endl;
            return false;

        } else {
            Operand newOperand;
            newOperand.memoryOffset = newVarMemOffset+=DATA_SIZE;
            newOperand.timesRequested = 0;
            parserData.operandMap[tokens[1].string] = newOperand;

        }

        parserData.outputFile << "##DEC " << tokens[1].string << endl;
    }

    return true;
}


//Parse set
bool internal_parse_set(vector<Token> &tokens, size_t numberOfTokens, ParserData &parserData) {

    if(numberOfTokens < 5) {
        cout << "ERROR: Expected declaration expression but recieved: " << endl;
        return false;
    } else {

        //Expect a variable name
        if(tokens[1].tokenType != TOK_STRING) {
            internal_macro_parser_print_invalid_token("ERROR: Expected variable: \n", tokens[1]);
        }

        //Check for redefinition
        auto varMapIterator = parserData.operandMap.find(tokens[1].string);
        if(varMapIterator != parserData.operandMap.end()) { //Variable found



        } else {
            cout << "ERROR: Unrecognised variable: '" << tokens[1].string << "'" << endl;
            return false;
        }






        Token &arithmaticOperator = tokens[2];

        Operand operand;

        int targetRegister = 0;
        int sourceRegister = 0;  

        if(tokens[3].tokenType == TOK_IMM_INT) {
            operand.immediate = tokens[2].immInt;
            operand.isFree = true;

        } else if(tokens[3].tokenType == TOK_STRING) {

            auto varMapIterator = parserData.operandMap.find(tokens[1].string);
            if(varMapIterator != parserData.operandMap.end()) { //Variable found
                cout << "ERROR: Unrecognised variable '" << tokens[1].string << "'" << endl;
                return false;

            } else {
                operand = parserData.operandMap[tokens[2].string];
            }

        } else {
            internal_macro_parser_print_invalid_token("ERROR: Expected operand but recieved: \n", tokens[2]);
            return false;
        }
        register_push(parserData, operand);
        sourceRegister = operand.registerIndex;

        //Target register
        register_push(parserData, parserData.operandMap[tokens[1].string]);
        targetRegister = parserData.operandMap[tokens[1].string].registerIndex;



        sourceRegister = operand.registerIndex;
        switch (arithmaticOperator.tokenType) {
        
        case TOK_MOV: {

            //WORK HERE
            parserData.operandMap[tokens[1].string].registerIndex = sourceRegister;
            //macro_pneumonic_move(targetRegister, sourceRegister, parserData.outputFile);
            break;

        } case TOK_ADD: {
            macro_pneumonic_add(targetRegister, sourceRegister, parserData.outputFile);
            break;

        } case TOK_SUB: {
            macro_pneumonic_sub(targetRegister, sourceRegister, parserData.outputFile);
            break;

        } case TOK_MUL: {
            macro_pneumonic_mul(targetRegister, sourceRegister, parserData.outputFile);
            break;

        } case TOK_DIV: {
            macro_pneumonic_div(targetRegister, sourceRegister, parserData.outputFile);
            break;

        } case TOK_MOD: {
            macro_pneumonic_mod(targetRegister, sourceRegister, parserData.outputFile);
            break;

        } default: {
            internal_macro_parser_print_invalid_token("ERROR: Expected arithmatic operator but recieved: \n", tokens[2]);
            break;
        }
        
        }


        if(tokens[1].tokenType == TOK_IMM_INT) {

            parserData.outputFile << "##SET " << tokens[1].immInt << endl;
        } else {

            parserData.outputFile << "##SET " << tokens[1].string << endl;
        }
    }

    return true;
}

//Parse if statement
bool internal_parse_if(vector<Token> &tokens, size_t numberOfTokens, ParserData &parserData) {

    static int labelNumber = 0;
    if(numberOfTokens != 4) {
        cout << "ERROR: Expected if" << endl;
        return false;
    } else {

        Operand arg1;
        Operand arg2;

        if(tokens[1].tokenType != TOK_STRING) {
            internal_macro_parser_print_invalid_token("ERROR: Expected variable: \n", tokens[1]);
        }

        auto varMapIterator = parserData.operandMap.find(tokens[1].string);
        if(varMapIterator != parserData.operandMap.end()) { //Variable found
            arg1 = parserData.operandMap[tokens[1].string];
        } else {
            cout << "ERROR: Unrecognised variable: '" << tokens[1].string << "'" << endl;
            return false;
        }

        varMapIterator = parserData.operandMap.find(tokens[3].string);
        if(varMapIterator != parserData.operandMap.end()) { //Variable found
            arg2 = parserData.operandMap[tokens[3].string];
        } else {
            cout << "ERROR: Unrecognised variable: '" << tokens[3].string << "'" << endl;
            return false;
        }

        register_push(parserData, arg1);
        register_push(parserData, arg2);
        int arg1Register = arg1.registerIndex;
        int arg2Register = arg2.registerIndex;

        switch(tokens[2].tokenType) {
            case TOK_EQUAL: {

                macro_pneumonic_equal(arg1Register, arg2Register, labelNumber, parserData.outputFile);
                break;
            } case TOK_LESS: {

                macro_pneumonic_less(arg1Register, arg2Register, labelNumber, parserData.outputFile);
                break;
            } case TOK_LESS_EQUAL: {

                macro_pneumonic_less_equal(arg1Register, arg2Register, labelNumber, parserData.outputFile);
                break;
            } default: {

                internal_macro_parser_print_invalid_token("ERROR: Expected comparator but recieved: \n", tokens[2]); 
                break;
            }
        }


        parserData.ifStack.push(labelNumber);
        labelNumber++;

        parserData.outputFile << "##IF" << tokens[1].immInt << endl;
    }



    return true;
}

//Parse an endif statement
bool internal_parse_endif(vector<Token> &tokens, size_t numberOfTokens, ParserData &parserData) {

    if(numberOfTokens != 1) {
        internal_macro_parser_print_invalid_token("ERROR: Expected endif but recieved: \n", tokens[0]); 
        return false;
    } else {
        if(parserData.ifStack.size() == 0) {
            cout << "ERROR: Expected an if statement" << endl;
            return false;
        }

        macro_pneumonic_print_label(parserData.ifStack.top(), parserData.outputFile);
        parserData.ifStack.pop();
    }

    parserData.outputFile << "##ENDIF" << tokens[1].immInt << endl;
    return true;
}



//Parse a label  statement
bool internal_parse_label(vector<Token> &tokens, size_t numberOfTokens, ParserData &parserData) {

    //goto label
    if(numberOfTokens != 3) {
        internal_macro_parser_print_invalid_token("ERROR: Expected a label but recieved: \n", tokens[0]); 
        return false;

    } else {

        //Preappend string to garuntee it will not collide with compiler labels
        tokens[1].string += APPEND_INPUT_LABEL_STR;
        auto labelMapIterator = parserData.knownLabels.find(tokens[1].string);

        if(labelMapIterator != parserData.knownLabels.end()) { //Label found
            cout << "ERROR: Redefinition of '" << tokens[1].string << "'" << endl;
            return false;

        } else {
            
            macro_pneumonic_print_label(tokens[1].string, parserData.outputFile);
            parserData.knownLabels.insert(tokens[1].string);
        }
    }

    parserData.outputFile << "##LAB " << tokens[1].string<< endl;

    return true;
}


//Parse a goto  statement
bool internal_parse_goto(vector<Token> &tokens, size_t numberOfTokens, ParserData &parserData) {

    //goto label
    if(numberOfTokens != 3) {
        internal_macro_parser_print_invalid_token("ERROR: Expected a label but recieved: \n", tokens[0]); 
        return false;

    } else {
        tokens[1].string += APPEND_INPUT_LABEL_STR;
        auto labelMapIterator = parserData.knownLabels.find(tokens[1].string);
        if(labelMapIterator != parserData.knownLabels.end()) { //Label found

            macro_pneumonic_unconditional_jump(tokens[1].string, parserData.outputFile);
        } else {

            internal_macro_parser_print_invalid_token("ERROR: Unrecognised label:", tokens[1]);
            return false;
        }

        parserData.outputFile << "##GOTO " << tokens[1].string<< endl;
    }

    return true;
}




/**
 * parser_parse 
 * ===============================================
 * Brief: Parse a stream of tokens
 * 
 * Param: 
 *        &tokens - Tokens to be parsed
 * 
 * Return: bool - Indicating if parsing was successful
 * 
 */
bool parser_parse(vector<Token> &tokens, ParserData &parserData) {


    size_t numberOfTokens = tokens.size();
    if(numberOfTokens < 1) {
        cout << "ERROR: Insufficient tokens" << endl;
        return false;
    }

    switch(tokens[0].tokenType) {

    case TOK_DEC: {
        if(internal_parse_dec(tokens, numberOfTokens, parserData) == false) {
            return false;
        }
        break;
    } case TOK_SET: {
        if(internal_parse_set(tokens, numberOfTokens, parserData) == false) {
            return false;
        }
        break;
    } case TOK_IF: {
        if(internal_parse_if(tokens, numberOfTokens, parserData) == false) {
            return false;
        }
        break;
    } case TOK_ENDIF: {
        if(internal_parse_endif(tokens, numberOfTokens, parserData) == false) {
            return false;
        }
        break;
    } case TOK_LABEL: {
        if(internal_parse_label(tokens, numberOfTokens, parserData) == false) {
            return false;
        }
        break;
    } case TOK_GOTO: {
        if(internal_parse_goto(tokens, numberOfTokens, parserData) == false) {
            return false;
        }
        break;
    } case TOK_END_OF_STREAM: {
        break;
    } default: {
        internal_macro_parser_print_invalid_token("ERROR: Unrecognised instruction:", tokens[0]);
        return false;
        break;
    }
    }




    return true;
}



































