# Vector


## NOTE: 
- Vectors do NOT automatically resize, they must be MANUALLY resized before insertion and optionally after a deletion
- Vectors may hold ANY datatype without any modification to the library (including structs or unions)


## Functions:

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

- Inserting into a veector

  Inserts an item into a vector at any valid index (0 -> end)



```c
Vector vector;
//Initialisation
int data = 10;
if(vector_insert_index(&vector, 0, &data) == false) {

  printf("Insertion failed\n);
}

/*
The code above:
  - Inserts the value '10' into a vector of ints called 'vector'
  - Checks if insertion was successful
*/
```


































































































