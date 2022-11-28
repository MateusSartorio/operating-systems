#!/bin/bash

trap "echo SIGTERM Received! Exiting with 0!; exit 0" SIGTERM

while [ 1 -eq 1 ]
do
    echo "nothing" > /dev/null
done
