#!/bin/sh
make
if [ $? -eq 0 ]; then
    ./AQFFOS $1 $2 $3
fi
