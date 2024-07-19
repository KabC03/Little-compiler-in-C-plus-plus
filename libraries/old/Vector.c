#include "Vector.h"

#define min(a, b) ((a) < (b) ? (a) : (b))

vector* create_vector(int initialSize, char type)
{
    vector* vectorPtr = NULL;
    vectorPtr = malloc(sizeof(vector));
    if(vectorPtr == NULL) return NULL;
    vectorPtr->currentSize = initialSize;
    vectorPtr->currentTop = initialSize;
    vectorPtr->vectorDataType = type;

    switch (type)
    {
    case 'i':

        vectorPtr->vectorData.intData = malloc(sizeof(int) * initialSize);
        if(vectorPtr->vectorData.intData == NULL)
        {
            free(vectorPtr);
            return NULL;
        }
        break;

    case 'f':

        vectorPtr->vectorData.floatData = malloc(sizeof(float) * initialSize);
        if(vectorPtr->vectorData.floatData == NULL)
        {
            free(vectorPtr);
            return NULL;
        }
        break;

    case 'c':

        vectorPtr->vectorData.charData = malloc(sizeof(char) * initialSize);
        if(vectorPtr->vectorData.charData == NULL)
        {
            free(vectorPtr);
            return NULL;
        }
        break;
    
    default:
        return NULL;
    }



    return vectorPtr;
}


bool print_vector(vector * vector)
{
    if(vector == NULL) return false;
    else if(vector->vectorData.intData == NULL) return false;


    switch (vector->vectorDataType)
    {
    case 'i':

        printf("[");
        for (size_t i = 0; i < vector->currentTop - 1; i++)
        {
            printf("%d, ",vector->vectorData.intData[i]);
        }
        printf("%d]",vector->vectorData.intData[vector->currentTop - 1]);
        

        break;

    case 'f':

        printf("[");
        for (size_t i = 0; i < vector->currentTop - 1; i++)
        {
            printf("%f, ",vector->vectorData.floatData[i]);
        }
        printf("%f]",vector->vectorData.floatData[vector->currentTop - 1]);

        break;

    case 'c':

        printf("[");
        for (size_t i = 0; i < vector->currentTop - 1; i++)
        {
            printf("%c, ",vector->vectorData.charData[i]);
        }
        printf("%c]",vector->vectorData.charData[vector->currentTop - 1]);

        break;
    
    default:
        return false;
    }



    return true;
}

bool destroy_vector(vector* vector)
{

    if(vector == NULL) return false;
    else if(vector->vectorData.intData == NULL) return false;

    free(vector->vectorData.intData);
    free(vector);

    return true;
}

int get_vector_size(vector* vector)
{
    if(vector == NULL) return -1;

    return vector->currentTop;
}

int get_vector_memory_size(vector* vector)
{
    if(vector == NULL) return -1;

    return vector->currentSize;
}

bool append_vector(vector* vector, void* newData, size_t offsetSize)
{
    if(vector == NULL) return false;
    else if(vector->vectorData.intData == NULL) return false;

    switch (vector->vectorDataType)
    {
    case 'i':

        if(vector->currentTop + offsetSize > vector->currentSize) //Check data will not fit into vector
        {
            vector->vectorData.intData = realloc(vector->vectorData.intData, (vector->currentSize + offsetSize) * sizeof(int));
        }
        for (size_t i = 0; i < offsetSize; i++) 
        {
            vector->vectorData.intData[vector->currentTop + i] = ((int*)newData)[i];
        }
        vector->currentTop += offsetSize;

        break;

    case 'f':

        if(vector->currentTop + offsetSize > vector->currentSize) //Check data will not fit into vector
        {
            vector->vectorData.floatData = realloc(vector->vectorData.floatData, (vector->currentSize + offsetSize) * sizeof(float));
        }
        for (size_t i = 0; i < offsetSize; i++) 
        {
            vector->vectorData.floatData[vector->currentTop + i] = ((float*)newData)[i];
        }
        vector->currentTop += offsetSize;

        break;

    case 'c':

        if(vector->currentTop + offsetSize > vector->currentSize) //Check data will not fit into vector
        {
            vector->vectorData.charData = realloc(vector->vectorData.charData, (vector->currentSize + offsetSize) * sizeof(char));
        }
        for (size_t i = 0; i < offsetSize; i++) 
        {
            vector->vectorData.charData[vector->currentTop + i] = ((char*)newData)[i];
        }
        vector->currentTop += offsetSize;

        break;
    
    default:
        return false;
    }

    if(vector->currentTop + offsetSize > vector->currentSize) 
    {
        vector->currentSize += offsetSize;
    }



    return true;
}

bool get_index_vector(vector* vector, size_t index, returnData* returnData)
{
    if(vector == NULL) return false;
    else if(vector->vectorData.intData == NULL) return false;
    if(index >= vector->currentSize) return false;

    switch (vector->vectorDataType)
    {
    case 'i':

        returnData->rInt = vector->vectorData.intData[index];

        break;

    case 'f':

        returnData->rFloat = vector->vectorData.floatData[index];

        break;

    case 'c':

        returnData->rChar = vector->vectorData.charData[index];

        break;
    
    default:
        return false;
    }


    return true;
}

bool set_index_vector(vector* vector, size_t index, void* newData)
{
    if(vector == NULL) return false;
    else if(vector->vectorData.intData == NULL) return false;
    if(index >= vector->currentSize) return false;

    switch (vector->vectorDataType)
    {
    case 'i':

        vector->vectorData.intData[index] = *((int*)newData);

        break;

    case 'f':

        vector->vectorData.floatData[index] = *((float*)newData);

        break;

    case 'c':

        vector->vectorData.charData[index] = *((char*)newData);

        break;
    
    default:
        return false;
    }

    return true;
}

bool offset_vector_size(vector* vector, int offsetSize)
{
    if(vector == NULL || vector->vectorData.intData == NULL) return false;
    if(vector->currentSize + offsetSize < 0) return false;

    void* newMemory = NULL;
    switch (vector->vectorDataType)
    {
        case 'i':
            newMemory = realloc(vector->vectorData.intData, (vector->currentSize + offsetSize) * sizeof(int));
            break;

        case 'f':
            newMemory = realloc(vector->vectorData.floatData, (vector->currentSize + offsetSize) * sizeof(float));
            break;

        case 'c':
            newMemory = realloc(vector->vectorData.charData, (vector->currentSize + offsetSize) * sizeof(char));
            break;

        default:
            return false;
    }

    if(newMemory == NULL)
    {
        free(vector);
        vector = NULL;
        return false;
    }

    // Update the vector data pointer and size
    if(vector->vectorDataType == 'i')
        vector->vectorData.intData = newMemory;
    else if(vector->vectorDataType == 'f')
        vector->vectorData.floatData = newMemory;
    else if(vector->vectorDataType == 'c')
        vector->vectorData.charData = newMemory;

    vector->currentSize += offsetSize;
    vector->currentTop = min(vector->currentTop, vector->currentSize);

    return true;
}


