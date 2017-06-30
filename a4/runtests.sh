#!/bin/bash
./vote -1
./vote 1 2 3 4 5 6
./vote 0 1 2
./vote 1 2 0
./vote 10 2 123
./vote 10 3 12
./vote "This is false" 12
./vote 1aqwe 12 34
./vote 12 3 0
./vote 12 0 3
./vote 42 21 0
./vote 45 -3 23
./vote 4 1 -4
./vote 5 1 4.3
./vote 0
./vote 4 2
./vote 1.2
