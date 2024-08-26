
//Parser - generates IR

#ifndef PARSE_H 
#define PARSE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include "../libraries/return codes.h"
#include "../libraries/datastructures.h"
#include "compiler data.h"
#include "../libraries/string hashmap.h"
#include "architecture pneumonics.h"
#include "tokenise.h"

RETURN_CODE parse_initialise(void);
RETURN_CODE parse(Vector *tokens, FILE *irOut);


#endif //PARSE_H



