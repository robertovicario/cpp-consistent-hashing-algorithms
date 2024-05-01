#!/bin/bash

# Ensure script has executable permissions:
# chmod +x main.sh

cd build || exit
ninja

if [ $# -gt 0 ]; then
    if [ "$1" == "main" ]; then
        ./main
    else
        echo "[ERR] Invalid argument: $1"
        exit 1
    fi
else
    ./main
fi
