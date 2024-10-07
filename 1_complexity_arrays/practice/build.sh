#!/bin/bash

rm -rdf build
cmake . -Bbuild
cd build
make -j8
make install
cd ..
