#!/bin/bash
DIR="$( cd "$( dirname "$0" )" && pwd -P )"
cd $DIR
mkdir build
cd build
cmake ..
make
