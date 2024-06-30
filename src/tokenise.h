
// Compiler data

#ifndef TOKENISE_H
#define TOKENISE_H 
#include <ctype.h> 
#include <stdlib.h>
#include "compiler data.h"
#include "datastructures.h"
#include "hashmap.h"
#include "vector.h"


bool initialise_compiler_hashmaps(void);
bool tokenise(char *line, Vector *const tokensOut);



#endif // TOKENISE_H 


