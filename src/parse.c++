//30 Aug 2024
#include "parse.h++"
#define APPEND_INPUT_LABEL_STR "__USR"
#define OPERAND_RESERVE 10
#define LABEL_RESERVE 10
#define IF_STACK_RESERVE 10
#define internal_macro_parser_print_invalid_token(stringToPrint, tokenToPrint)  cout << stringToPrint;\
    debug_tokenise_singular_token_print(tokenToPrint);\
    cout << "" << endl;






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
    operand.isVar = false; //Indicates position can be overwritten
    operand.memoryOffset = -1;
    operand.varName = "\0";
    parserData.registerStates.resize(NUMBER_OF_REGISTERS, operand); //Fill with operand

    parserData.operandMap.reserve(OPERAND_RESERVE);
    parserData.knownLabels.reserve(LABEL_RESERVE);


    return true;
}


//Parse an expression
bool parse_expression(vector<Token> &tokens, size_t startIndex, size_t stopIndex, ParserData &parserData) {


    return true;
}










//Parse a variable declaration
bool internal_parse_dec(vector<Token> &tokens, size_t numberOfTokens, ParserData &parserData) {

    static size_t newVarMemOffset = 0; //Base offset address
    if(numberOfTokens < 5) {
        cout << "ERROR: Expected declaration expression but recieved: " << endl;
        return false;
    } else {

        //Expect a variable name
        if(tokens[1].tokenType != TOK_STRING) {
            internal_macro_parser_print_invalid_token("Expected variable: \n", tokens[1]);
        }

        //Check for redefinition
        auto varMapIterator = parserData.operandMap.find(tokens[1].string);
        if(varMapIterator != parserData.operandMap.end()) { //Variable found
            cout << "Redefinition of '" << tokens[1].string << "'" << endl;
            return false;

        } else {
            Operand newOperand;
            newOperand.isVar = true;
            newOperand.memoryOffset = newVarMemOffset+=DATA_SIZE;
            newOperand.varName = tokens[1].string; //Used for debugging, remove later
            parserData.operandMap[tokens[1].string] = newOperand;
        }


        //Expect an equals
        if(tokens[2].tokenType != TOK_EQUAL) {
            internal_macro_parser_print_invalid_token("Expected assignment operator but recieved: \n", tokens[2]);
        }


        //Parse expression    
        if(parse_expression(tokens, 3, numberOfTokens - 1, parserData) == false) {
            return false;
        }
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
            internal_macro_parser_print_invalid_token("Expected variable: \n", tokens[1]);
        }

        //Check for redefinition
        auto varMapIterator = parserData.operandMap.find(tokens[1].string);
        if(varMapIterator != parserData.operandMap.end()) { //Variable found



        } else {
            cout << "Unrecognised variable: '" << tokens[1].string << "'" << endl;
            return false;
        }


        //Expect an equals
        if(tokens[2].tokenType != TOK_EQUAL) {
            internal_macro_parser_print_invalid_token("Expected assignment operator but recieved: \n", tokens[2]);
        }


        //Parse expression    
        if(parse_expression(tokens, 3, numberOfTokens - 1, parserData) == false) {
            return false;
        }
    }

    return true;
}

//Parse if statement
bool internal_parse_if(vector<Token> &tokens, size_t numberOfTokens, ParserData &parserData) {


    return true;
}

//Parse an endif statement
bool internal_parse_endif(vector<Token> &tokens, size_t numberOfTokens, ParserData &parserData) {

    if(numberOfTokens != 2) {
        cout << "ERROR: Expected endif" << endl;
        return false;
    } else {
        if(parserData.ifStack.size() == 0) {
            cout << "ERROR: Expected an if statement" << endl;
            return false;
        }

        macro_pneumonic_print_label(parserData.ifStack.top(), parserData.outputFile);
        parserData.ifStack.pop();
    }

    return true;
}



//Parse a label  statement
bool internal_parse_label(vector<Token> &tokens, size_t numberOfTokens, ParserData &parserData) {

    //goto label
    if(numberOfTokens != 3) {
        cout << "ERROR: Expected label" << endl;
        return false;

    } else {

        //Preappend string to garuntee it will not collide with compiler labels
        tokens[1].string += APPEND_INPUT_LABEL_STR;
        auto labelMapIterator = parserData.knownLabels.find(tokens[1].string);

        if(labelMapIterator != parserData.knownLabels.end()) { //Label found
            cout << "Redefinition of '" << tokens[1].string << "'" << endl;
            return false;

        } else {
            
            macro_pneumonic_print_label(tokens[1].string, parserData.outputFile);
            parserData.knownLabels.insert(tokens[1].string);
        }
    }

    return true;
}


//Parse a goto  statement
bool internal_parse_goto(vector<Token> &tokens, size_t numberOfTokens, ParserData &parserData) {

    //goto label
    if(numberOfTokens != 3) {
        cout << "ERROR: Expected label" << endl;
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



































