
// Compiler data

#ifndef TOKENISE_H
#define TOKENISE_H 

#include "compiler data.h"
#include "datastructures.h"
#include "hashmap.h"
#include "vector.h"


bool initialise_valid_token_hashmap(void);
bool tokenise(char *line, Vector tokensOut);



#endif // TOKENISE_H 


