# Vector


__NOTE: Vectors do NOT automatically resize, they must be MANUALLY resized before insertion and optionally after a deletion__


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

  Can be a negative or positive number - where negative offsets shrink the vector (excess memory automatically freed)


```c
Vector vector;
//Initialisation
if(vector_resize(&vector, 10) == false) {
  printf("Vector resizing failed\n);
}

/*
The code above:
  - Resizes 'vector' to hold a maximum of 10 elements
  - Checks if resizing was successful
*/
```








































































































