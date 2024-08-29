#Compile and run everything and check error codes


clear


#Run python script
python3 ./src/set\ compiler\ data.py
if [[ $? -ne 0 ]]; then

    printf "\n\n[SHELL] Compiler data was not initialised\n\n"
    exit -1 

fi


#Create directory and compile
mkdir -p ./output
clang++ -std=c++11 ./src/*.c++ -Wall -Werror -fsanitize=address -g -fno-inline -O0 -o ./output/executable

if [[ $? -ne 0 ]]; then

    printf "\n\n[SHELL] Compilation failed\n\n"
    exit -2 

fi
printf "\n\n[SHELL] Compiled\n\n"


#Run executable
./output/executable

if [[ $? -ne 0 ]]; then

    printf "\n\n[SHELL] Compiler did not successfully execute\n\n"
    exit -3

fi
printf "\n\n[SHELL] Executed\n\n"

