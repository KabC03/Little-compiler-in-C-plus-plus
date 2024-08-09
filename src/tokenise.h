//10, Jul, 24

#ifndef TOKENISE_H
#define TOKENISE_H 
#include <ctype.h> 
#include <stdlib.h>
#include "compiler data.h"
#include "../libraries/datastructures.h"
#include "../libraries/static hashmap.h"
#include "../libraries/string hashmap.h"
#include "../libraries/vector.h"
#include "../libraries/return codes.h"


RETURN_CODE print_tokens(Vector *tokensToPrint);
RETURN_CODE tokenise(char *inputString, Vector *tokensOut);
 
#endif // TOKENISE_H 


