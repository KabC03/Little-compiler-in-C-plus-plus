#!/bin/bash
#Compile everything in ./src then run if compilation was ok


files=""
flags="-Wall -Werror -fsanitize=address -fno-omit-frame-pointer "


for file in "./src"/*.c; do

    files+="$file "
done


mkdir -p output
gcc $files $flags -o ./output/out
prevOutput=$?



if [[ $prevOutput -eq 0 ]]; then
    clear
    ./output/out

else
    echo "Compilation error"
fi




















