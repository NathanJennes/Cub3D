#!/bin/bash

cd Libft/Leaky
if (( $? != 0 )); then
  echo "You must be in the root directory of the project to push!"
  exit 1
fi

git status | grep -q "Leaky "
if (( $? == 0 )); then
  echo "Changes were made to Leaky, please commit them manually"
  exit 1
fi

git status | grep -q "Your branch is ahead of"
if (( $? == 0 )); then
  echo "Please push your local commits made in Leaky manually"
  exit 1
fi

cd ..
git status | grep -q "Libft "
if (( $? == 0 )); then
  echo "Changes were made to Libft, please commit them manually"
  exit 1
fi

git status | grep -q "Your branch is ahead of"
if (( $? == 0 )); then
  echo "Please push your local commits made in Libft manually"
  exit 1
fi

cd ..
git status | grep -q "Changes to be committed"
if (( $? != 0 )); then
  echo "Nothing was added to be commited"
  exit 1
fi

if (( ${#1} > 0 )); then
  git commit -m "$1"
  if (( $? != 0 )); then
    echo "Could not commit the changes"
    exit 1
  fi
else
  git commit
  if (( $? != 0 )); then
    echo "Could not commit the changes"
    exit 1
  fi
fi

git push
if (( $? != 0 )); then
  echo "Could not push changes"
  exit 1
fi
