

#ifndef PARSE_H
#define PARSE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include "vector.h"
#include "datastructures.h"
#include "dynamic string.h"
#include "static hashmap.h"
#include "string hashmap.h"
#include "compiler data.h"
#include "tokenise.h"
#include "IR grammer.h"
#include "error codes.h"
#define INITIAL_MAP_SIZE 100


bool parser_initialise_structures(FILE *irFile);
bool parse(Vector *tokens);


#endif // PARSE_H
