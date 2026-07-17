#!/bin/bash
if [ -d "$1" ]
then
  filesdir=$1
else
  echo "First argument must be a dir."
  exit 1
fi
if [ -n "$2" ]
then
  searchstr=$2
else
  echo "Second argument must be a search string."
  exit 1
fi
total_matches=$(ls ${filesdir} | wc -l)
sub_matches=$(grep -Rc ${searchstr} ${filesdir} | wc -l)
echo "The number of files are ${total_matches} and the number of matching lines are ${sub_matches}"
