#!/bin/sh
../../../pasc $1'.p' -o $1'.s'
gcc -m32 $1'.s' -g -o $1
