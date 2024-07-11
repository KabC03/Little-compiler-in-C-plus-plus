
//Parser - generates IR

#ifndef PARSE_H 
#define PARSE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include "return codes.h"
#include "compiler data.h"


RETURN_CODE parse(Vector *tokens, char *fileName);


#endif //PARSE_H


