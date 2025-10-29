#!/bin/sh

cd test
rm *.out

tests=$(ls -1 ./ | grep -v test.sh | sed 's/\..*//' | uniq)
echo $tests

for test in $tests; do
  ../bin/example > ${test}.out $(< ${test}.in)
  diff -u ${test}.out.test ${test}.out

  exit_code=$?
  if [ $exit_code == 0 ]; then
    printf "${test} test pass!\n"
  fi
done
