#Generates the data section for the asm program - also write the hash table in assembly

import sys;

dataFileName = "data.asm";
djb2HashSeed = 5381; #Will get changed by perfect hash function generator
maxTableTries = 10; #Max tries to find a perfect constant before giving up
perfectHashTable = []; #Perfect hash table array

#Number of bytes required for inidividual items - update manually
pneumonicLength = 3;
machineCodeLength = 1;



sourceCodePneumonics = {

    #Pneumonic : Machine code

    #Instructions
    "ADD" : "0", "LIR" : "1", "PSH" : "2", "POP" : "3", "JEQ" : "4", "BLK" : "-1",

    #Registers
    "EAX" : "0", "EBX" : "1", "ECX" : "2", "EDX" : "3",

};
hashTableSize = len(sourceCodePneumonics.keys());
preAppendDefines = {

    #File processing
    "LINE_BUFFER_SIZE" : 1000, 

};




#Hash a key
def djb2_hash(key):



    djb2Hash = djb2HashSeed;
    for character in key:
        djb2Hash = ((djb2Hash * 33) + djb2Hash) + ord(character);

    #print(str(djb2Hash % 10) + "   "  + str(key));

    return djb2Hash % hashTableSize;


#Convert a string into ASCII
def convert_string_to_ASCII(string):

    asciiString = "";
    for character in string:
        asciiString += str(ord(character));
    return asciiString;


#Find a perfect hash function
def find_perfect_djb2_hash_constant():
    global djb2HashSeed;
    global perfectHashTable;

    perfectHashTable = list(sourceCodePneumonics.keys());
    tableIsPerfect = False;
    tries = 0;
    while(tableIsPerfect == False):

        #Exit if max tries are reached
        if(tries == maxTableTries):
            print("Could not find perfect hash within '" + str(maxTableTries) + "' tries\n");
            return False;



        #Zero out the table
        for i in range(0,len(perfectHashTable)):
            perfectHashTable[i] = None;


        #Hash all keys in the table - if a collision is detected try again with a different hash constant
        tableIsPerfect = True; #Assume table is perfect until collision met
        for key in sourceCodePneumonics:

            indexToInsert = djb2_hash(key);

            if(perfectHashTable[indexToInsert] != None):
                #Collision detected
                #print("Collision with: " + str(hashTable[indexToInsert]));
                tableIsPerfect = False;
                break;
            
            else:
                #Insert at the index - mark it as used
                perfectHashTable[indexToInsert] = str(indexToInsert);

        djb2HashSeed += 1;
        tries += 1; 

    return True;




def write_defines():
    try:
        with open(dataFileName, 'w') as file:

            file.write("; Defines section\n\n");

            for key, value in preAppendDefines.items():
                file.write("%define " + str(key) + " " + str(value) + "\n");


            file.write("\n\n\n");

        return True;
    except:
        return False;




#Write .data section
def write_data_section() :
    try:
        with open(dataFileName, 'a') as file:

            file.write("; .data section\n");
            file.write("section .data\n");


            file.write("\n\n\n");
        return True;
    except:
        return False;


#Write .bss section
def write_bss_section():


    try:
        with open(dataFileName, 'a') as file:

            file.write("; .bss section\n");
            file.write("section .bss\n");

            #Space for key hashmap
            #file.write("    keyBuffer: db " + str(len(sourceCodePneumonocs.keys()) * pneumonicLength) + "\n"); #Keys dont need to be stored
            file.write("    valueBuffer: db " + str(len(sourceCodePneumonics.values()) * machineCodeLength) + "\n");




        return True;
    except:
        return False;



def write_text_section():


    try:
        with open(dataFileName, 'a') as file:

            file.write("; .text section\n");
            file.write("section .section\n\n");

            #Store the perfect hash table in the .bss block
            #Just iterate over each character and store it as a byte
            #Store 1, 2 or 4 bytes depending on the remaining lenght of the string

            file.write("    push eax\n");
            file.write("    lea edi, [valueBuffer]\n");
            index = 0;
            remainingLength = len(sourceCodePneumonics.values());

            perfectHashTable = sourceCodePneumonics.keys();
            stringToWrite = "".join(perfectHashTable);

            while(remainingLength != 0):
                immediate = 0;

                if(remainingLength - 4 >= 0):
                    #Write the next 4 characters
                    
                    immediate = convert_string_to_ASCII(stringToWrite[index:index+4]);
                    file.write("    mov dword [edi], " + str(immediate) + "\n");
                    remainingLength -= 4;
                    index += 4;

                elif(remainingLength - 2 >= 0):
                    #Write the next 2 characters
                    immediate = convert_string_to_ASCII(stringToWrite[index:index+2]);
                    file.write("    mov word [edi], " + str(immediate) + "\n");
                    remainingLength -= 2;
                    index += 2;

                else:
                    #Write only one character
                    immediate = convert_string_to_ASCII(stringToWrite[index:index+1]);
                    file.write("    mov byte [edi], " + str(immediate) + "\n");
                    remainingLength -= 1;
                    index += 1;
        return True;
    except:
        return False;




def main():

    if(find_perfect_djb2_hash_constant() == False):
        print("Failed to find perfect hash seed\n");
        return -1;
        pass;


    #MUST call this first - since it opens for writing NOT appending
    if(write_defines() == False):
        print("Failed to write defines section\n");
        return -2;
    if(write_data_section() == False):
        print("Failed to write .data section\n");
        return -3;
    if(write_bss_section() == False):
        print("Failed to write .bss section");
        return -4;
    if(write_text_section() == False):
        print("Failed to write .text section");
        return -5; 



    #In .text section write a function that inserts values at their index found in find_perfect_hash_function();
    return 0;




if __name__ == "__main__":
    sys.exit(main());






