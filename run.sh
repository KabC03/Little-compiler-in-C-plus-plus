#Compile and run everything


clear


#Run python script
python3 ./src/set\ compiler\ data.py
if [[ $? -ne 0 ]]; then

    printf "\n\n[SHELL] Compiler data was not initialised\n\n"
    exit -1 

fi


#Create directory and compile
mkdir -p ./output
clang ./src/*.c ./libraries/*.c -Wall -Werror -fsanitize=address -o ./output/executable
if [[ $? -ne 0 ]]; then

    printf "\n\n[SHELL] Compilation failed\n\n"
    exit -2 

fi



#Run executable
./output/executable
if [[ $? -ne 0 ]]; then

    printf "\n\n[SHELL] Program did not successfully execute\n\n"
    exit -3

fi


