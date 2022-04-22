#!/bin/bash

cd Libft
if (( $? != 0 )); then
  echo "You must be in the root directory of the project to push!"
  exit 1
fi

git checkout master
git pull origin master

cd Leaky
git checkout Dev
git pull origin Dev
