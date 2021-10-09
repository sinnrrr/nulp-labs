#!/bin/bash

readonly MAIN_FILE_NAME="main.c"
readonly OUTPUT_FILE_NAME="a.out"
readonly LINK_FILE_NAME="calculation.c"

function clean() {
    rm $OUTPUT_FILE_NAME
}

trap clean EXIT

filepath="$1/$MAIN_FILE_NAME"
calculations="$1/$LINK_FILE_NAME"

if ! [[ -d $1 ]]; then
    echo "\"$1\" is not valid path or folder does not exist"
    exit 1
fi

if [[ -f $2 ]]; then
    if ! [[ $2 == *.c ]]; then
        echo "\"$2\" is not valid: file must exist or end with \".c\""
        exit 1
    fi

    calculations=$2
elif [[ -d $2 ]]; then 
    calculations="$2/$LINK_FILE_NAME"
fi

clang $filepath $calculations -o $OUTPUT_FILE_NAME && chmod +x $OUTPUT_FILE_NAME && ./$OUTPUT_FILE_NAME
