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
#define macro_pneumonic_save(registerIndex, baseOffset, outputFile)\
    outputFile << "save R" << registerIndex << " esp + " << baseOffset << endl;
#define macro_pneumonic_load(registerIndex, baseOffset, outputFile)\
    outputFile << "load R" << registerIndex << " esp + " << baseOffset << endl;



#define macro_pneumonic_load_immediate(dest, immediate, outputFile)\
    outputFile << "immediate R" << dest << " " << immediate << endl;
#define macro_pneumonic_move(dest, source, outputFile)\
    outputFile << "move R" << dest << " " << source << endl;
#define macro_pneumonic_add(dest, source, outputFile)\
    outputFile << "add R" << dest << " " << source << endl;
#define macro_pneumonic_sub(dest, source, outputFile)\
    outputFile << "sub R" << dest  << " " << source << endl;
#define macro_pneumonic_mul(dest, source, outputFile)\
    outputFile << "mul R" << dest << " " << source << endl;
#define macro_pneumonic_div(dest, source, outputFile)\
    outputFile << "div R" << dest << " " << source << endl;
#define macro_pneumonic_mod(dest, source, outputFile)\
    outputFile << "mod R" << dest << " " << source << endl;

#endif // ARCHITECTURE_PNEUMONICS_HH







