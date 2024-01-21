#!/bin/bash

SUCCESS=0
FAIL=0
RED="$(tput setaf 1)"
GREEN="$(tput setaf 2)"
BASE="$(tput setaf 7)"

function runTest {
    local testName=$1
    local arg=$2
    local pattern=$3
    local test_file=$4
    local success=0
    local fail=0


    grep $pattern $test_file > result.txt
    ./s21_grep $pattern $test_file > result1.txt
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

runTest "#0 test open file" "" "FILE" "tests/test1.txt"
runTest "#1 test ignore" "-i" "FILE" "tests/test2.txt"
runTest "#2 test invert" "-v" "FILE" "tests/test1.txt"
runTest "#3 test counter" "-c" "FILE" "tests/test1.txt"
runTest "#4 test number" "-n" "file" "tests/test2.txt"
runTest "#5 test pattern" "-e" "[0-9]" "tests/test1.txt"
runTest "#6 test pattern" "-E" "[0-9]" "tests/test1.txt"
runTest "#7 test no message" "-s" "[0-9]" "no_file.txt"
runTest "#8 test only matches" "-o" "file" "tests/test2.txt"
runTest "#9 test ignore and invert" "-iv" "file" "tests/test2.txt"
runTest "#10 test ignore and number" "-in" "file" "tests/test2.txt"
runTest "#11 test wrong pattern" "-i" "(0-2]" "tests/test1.txt"
runTest "#12 test wrong file" "-i" "file" "no_file.txt"
runTest "#13 test wrong file" "" "file" "no_file.txt"



function runFilesTest {
    local testName=$1
    local catArgs=$2
    local pattern=$3
    local testFile=$4
    local files=("$@")
    local success=0
    local fail=0

    for file in "${files[@]}"; do
    grep $catArgs $pattern $testFile > result.txt
    ./s21_grep $catArgs $pattern $testFile > result1.txt
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

runFilesTest "#11 test open files" "" "file" "tests/test1.txt" "tests/test2.txt" "tests/test3.txt"
runFilesTest "#12 test ignore files" "-i" "FiLE" "tests/test1.txt" "tests/test2.txt" "tests/test3.txt"
runFilesTest "#13 test invert files" "-v" "file" "tests/test1.txt" "tests/test2.txt" "tests/test3.txt"
runFilesTest "#14 test count files" "-c" "FILE" "tests/test1.txt" "tests/test2.txt" "tests/test3.txt"
runFilesTest "#15 test ignore files" "-n" "FILE" "tests/test1.txt" "tests/test2.txt" "tests/test3.txt"
runFilesTest "#16 test pattern files" "-e" "[0-9]" "tests/test1.txt" "tests/test2.txt" "tests/test3.txt"
runFilesTest "#17 test pattern files" "-E" "[0-9]" "tests/test1.txt" "tests/test2.txt" "tests/test3.txt"
runFilesTest "#18 test with mathces files" "-l" "file" "tests/test1.txt" "tests/test2.txt" "tests/test3.txt"
runFilesTest "#19 test no names files" "-h" "file" "tests/test1.txt" "tests/test2.txt" "tests/test3.txt"
runFilesTest "#20 test no message files" "-s" "FILE" "tests/test1.txt" "no_file.txt" "tests/test3.txt"
runFilesTest "#21 test only matches files" "-o" "FILE" "tests/test1.txt" "tests/test2.txt" "tests/test3.txt"
# runFilesTest "#22 test file pattern in files" "-f" "tests/test1.txt" "tests/test2.txt" "tests/test3.txt"
runFilesTest "#23 test ignore and invert files" "-iv" "fIle" "tests/test1.txt" "tests/test2.txt" "tests/test3.txt"
runFilesTest "#24 test ignore and number files" "-in" "fIle" "tests/test1.txt" "tests/test2.txt" "tests/test3.txt"
runFilesTest "#25 test wrong files" "" "FILE" "no_file.txt" "tests/test2.txt" "tests/test3.txt"
runFilesTest "#26 test wrong pattern files" "-i" "0-2" "tests/test1.txt" "tests/test2.txt" "tests/test3.txt"


printf "\tTOTAL\n"
echo "${RED}FAIL: ${FAIL}${BASE}"
echo "${GREEN}SUCCESS: ${SUCCESS}${BASE}"