//10, Jul, 24

#ifndef TOKENISE_H
#define TOKENISE_H 
#include <ctype.h> 
#include <stdlib.h>
#include "compiler data.h"
#include "datastructures.h"
#include "static hashmap.h"
#include "string hashmap.h"
#include "vector.h"
#include "return codes.h"


RETURN_CODE print_tokens(Vector *tokensToPrint);
RETURN_CODE tokenise(char *srcFilename, Vector *tokensOut);
 
#endif // TOKENISE_H 


