# Vector


__NOTE: Vectors do NOT automatically resize, they must be MANUALLY resized before insertion__


- Initialising a vector

  Must be done before usage

```c
Vector vector;
if(vector_initialise(&vector, sizeof(int)) == false) {
  printf("Failed to initialise vector");
}

/*
The code above:
  - Instantiates a Vector named 'vector'
  - Initialises it to hold integers
  - Checks to make sure initialisation was successful
*/

```

- Resizing a vector

  Offsets the amount of items that can be held in the vector








































































































