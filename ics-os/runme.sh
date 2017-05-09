#!/bin/bash
cd contrib/budget-tracker
make clean
make
make install
cd ../..
make clean
sudo make install
