//30 Aug 2024
//Includes macros for assembly generation by parser
//Some architectures may require multiple lines to perform the same operations as others

#ifndef ARCHITECTURE_PNEUMONICS_HH
#define ARCHITECTURE_PNEUMONICS_HH

#define NUMBER_OF_REGISTERS 5 //Number of general purpose registers
#define DATA_SIZE 4
/*
Note: 
If stack pointer is not available,
should use one of the general purpose registers in macros below (not allow compiler to use it for storage)
*/

#define macro_pneumonic_unconditional_jump(labelName, outputFile)\
    outputFile << "JUM " << labelName << endl;
#define macro_pneumonic_print_label(labelName, outputFile)\
    outputFile << "label: " << labelName << endl;


#endif // ARCHITECTURE_PNEUMONICS_HH







