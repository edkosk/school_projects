#!/bin/bash

SUCCESS=0
FAIL=0
RED="$(tput setaf 1)"
GREEN="$(tput setaf 2)"
BASE="$(tput setaf 7)"

function runTest {
    local testName=$1
    local catArgs=$2
    local testFile=$3
    local success=0
    local fail=0

    cat $catArgs $testFile > result.txt
    ./s21_cat $catArgs $testFile > result1.txt
    diff result.txt result1.txt

    if [ $? -eq 0 ]; then
        ((success++))
        (( SUCCESS++ ))
    else
        ((fail++))
        (( FAIL++ ))
    fi

    echo "Test $testName completed"
    echo "${GREEN}Success: ${success}${BASE}, ${RED}Fail: ${fail}${BASE}"
}

runTest "#0 test only cat" "" ""
runTest "#1 test open file" "" "tests/test1.txt"
runTest "#2 test number-nonblank" "-b" "tests/test3.txt"
runTest "#3 test number-nonblank" "--number-nonblank" "tests/test3.txt"
runTest "#4 test numbers" "-n" "tests/test1.txt"
runTest "#5 test numbers" "--number" "tests/test1.txt"
runTest "#6 test ends" "-e" "tests/test3.txt"
runTest "#7 test ends" "-E" "tests/test3.txt"
runTest "#8 test ends" "-vE" "tests/test3.txt"
runTest "#9 test ends" "--show-ends" "tests/test3.txt"
runTest "#10 test tabs" "-t" "tests/test2.txt"
runTest "#11 test tabs" "-T" "tests/test2.txt"
runTest "#12 test tabs" "-vT" "tests/test2.txt"
runTest "#13 test squeze" "-s" "tests/test3.txt"


function runFilesTest {
    local testName=$1
    local catArgs=$2
    local testFile=$3
    local files=("$@")
    local success=0
    local fail=0

    for file in "${files[@]}"; do
    cat $catArgs $testFile > result.txt
    ./s21_cat $catArgs $testFile > result1.txt
    diff result.txt result1.txt

    if [ $? -eq 0 ]; then
        (( success++ ))
        ((SUCCESS++))
    else
        (( fail++ ))
        ((FAIL++))
    fi
    done

    echo "Test $testName completed"
    echo "${GREEN}Success: ${success}${BASE}, ${RED}Fail: ${fail}${BASE}"
}

runFilesTest "#14 test number-nonblank files" "-b" "tests/test1.txt" "tests/test2.txt" "tests/test3.txt"
runFilesTest "#15 test number-nonblank files" "--number-nonblank" "tests/test1.txt" "tests/test2.txt" "tests/test3.txt"
runFilesTest "#16 test numbers files" "-n" "tests/test1.txt" "tests/test2.txt" "tests/test3.txt"
runFilesTest "#17 test numbers files" "--number" "tests/test1.txt" "tests/test2.txt" "tests/test3.txt"
runFilesTest "#18 test ends files" "-e" "tests/test1.txt" "tests/test2.txt" "tests/test3.txt"
runFilesTest "#19 test ends files" "-E" "tests/test1.txt" "tests/test2.txt" "tests/test3.txt"
runFilesTest "#20 test ends files" "-vE" "tests/test1.txt" "tests/test3.txt" "tests/test3.txt"
runFilesTest "#21 test ends files" "--show-ends" "tests/test1.txt" "tests/test3.txt" "tests/test3.txt"
runFilesTest "#22 test tabs files" "-t" "tests/test1.txt" "tests/test2.txt" "tests/test3.txt"
runFilesTest "#23 test tabs files" "-T" "tests/test1.txt" "tests/test2.txt" "tests/test3.txt"
runFilesTest "#23 test tabs files" "-vT" "tests/test1.txt" "tests/test2.txt" "tests/test3.txt"
runFilesTest "#25 test squeze files" "-s" "tests/test1.txt" "tests/test2.txt" "tests/test3.txt"



printf "\tTOTAL\n"
echo "${RED}FAIL: ${FAIL}${BASE}"
echo "${GREEN}SUCCESS: ${SUCCESS}${BASE}"