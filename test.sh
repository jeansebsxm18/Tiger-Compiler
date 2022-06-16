#!/bin/sh

if [ $1 == "-t" ]; then
    ./src/tc --scan-trace -XA $2

else
    ./src/tc -XA $1

fi
