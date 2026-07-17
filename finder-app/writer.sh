#!/bin/bash

set -e
set -u

if [ $# -lt 2 ]
then 
  echo "Example writer.sh /path/to/filename.txt string_to_write"
  exit 1
else 
  dirpath=$(dirname "$1")
  mkdir -p "$dirpath" 
  touch "$1"
  if ! [ -f $1 ]
    then
      echo "First argument must be a path to a regular file"
      exit 1 
    else 
      if ! [ -n $2 ]
        then
          echo "Second argument must be a string"
          exit 1
      else
        writestr=$2
    fi
  fi
fi
echo "$2" > "$1"
exit 0
