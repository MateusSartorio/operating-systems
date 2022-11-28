#!/bin/bash

set -m
trap "echo Triggering a child process termination with a silet ls; ls" USR1
trap "echo SIGCHLD Received! Exiting!; exit 0" CHLD
while [ 1 -eq 1 ]
do
    echo "nothing" > /dev/null
done
