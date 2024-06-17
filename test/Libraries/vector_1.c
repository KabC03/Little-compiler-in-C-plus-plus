#include "vector.h"

int main() {
    Vector vector;
    int data;

    vector_initialise(&vector, sizeof(int));

    vector_resize(&vector, 11);
    for(int i = 0; i < 10; i++) {
        vector_insert_index(&vector, i, &i);
    }

    vector_resize(&vector, -5);
    printf("Last element: %d || index: %zu || capacity: %zu\n",
    *(int*)(vector_get_index(&vector,vector_get_length(&vector))),
    vector_get_length(&vector), vector_get_size(&vector));

    vector_print(&vector);
    vector_destroy(&vector);

    return 0;
}


