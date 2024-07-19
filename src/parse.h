
//Parser - generates IR

#ifndef PARSE_H 
#define PARSE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include "../libraries/return codes.h"
#include "compiler data.h"
#include "../libraries/string hashmap.h"
#include "IR grammer.h"


RETURN_CODE parse(Vector *tokens, char *irOutputFileName);


#endif //PARSE_H



