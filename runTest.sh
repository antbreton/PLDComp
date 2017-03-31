#!/bin/bash

echo "## TEST 1 ##"
./gc+ <test/test1.test >> RES

echo "## TEST 2 ##"
./gc+ <test/test2.test 2> /dev/null
