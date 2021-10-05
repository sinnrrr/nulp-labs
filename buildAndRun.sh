#!/bin/bash

filepath="$1/main.c"
calculations="$1/calculations.c"

readonly OUTPUT_FILE_NAME="a.out"

function clean() {
    rm $OUTPUT_FILE_NAME
}

trap clean EXIT

if ! [[ -d $1 ]]; then
    echo "\"$1\" is not valid path or folder/file does not exist"
    exit 1
fi

clang $filepath $calculations -o $OUTPUT_FILE_NAME && chmod +x $OUTPUT_FILE_NAME && ./$OUTPUT_FILE_NAME
