#!/bin/bash

cd Libft
if (( $? != 0 )); then
  echo "You must be in the root directory of the project to push!"
  exit 1
fi
cd ..

git status | grep -q "Changes to be committed"
if (( $? == 0 )); then
  echo "Please commit your local changes before you commit"
  exit 1
fi

cd Libft
if (( $? != 0 )); then
  echo "You must be in the root directory of the project to push!"
  exit 1
fi

git status | grep -q "Changes to be committed"
if (( $? == 0 )); then
  echo "Please commit your local changes in Libft before you commit"
  exit 1
fi

cd Leaky
git status | grep -q "Changes to be committed"
if (( $? == 0 )); then
  echo "Please commit your local changes in Leaky before you commit"
  exit 1
fi

git checkout Dev 2> /dev/null | grep -q "M       "
if (( $? == 0 )); then
  echo "Warning, you have made changed to Leaky that are not committed"
fi

LK_COMMITS=$(git rev-list --count HEAD)
git pull origin Dev &> /dev/null
LK_COMMITS_AFTER=$(git rev-list --count HEAD)
LK_DIFFERENCE=$((LK_COMMITS_AFTER-LK_COMMITS))

if (( LK_DIFFERENCE != 0 )); then
  echo "Pulling $LK_DIFFERENCE commits from Leaky"
else
  echo "No new commits from leaky"
fi

LK_LAST=$(git log -1 --pretty=%B | sed 's/ *$//g')
echo "Last commit of Leaky: $LK_LAST"

cd ..
git checkout master 2> /dev/null | grep -q "M       "
if (( $? == 0 )); then
  echo "Warning, you have made changed to Libft that are not committed"
fi

FT_COMMITS=$(git rev-list --count HEAD)
git pull origin master &> /dev/null
FT_COMMITS_AFTER=$(git rev-list --count HEAD)
FT_DIFFERENCE=$((FT_COMMITS_AFTER-FT_COMMITS))

if (( FT_DIFFERENCE != 0 )); then
  echo "Pulling $FT_DIFFERENCE commits from Libft"
else
  echo "No new commits from Libft"
fi

FT_LAST=$(git log -1 --pretty=%B | sed 's/ *$//g')
echo "Last commit of Libft: $FT_LAST"

cd ..

CUBE_COMMITS=$(git rev-list --count HEAD)
git pull &> /dev/null
CUBE_COMMITS_AFTER=$(git rev-list --count HEAD)
CUBE_DIFFERENCE=$((CUBE_COMMITS_AFTER-CUBE_COMMITS))

if (( CUBE_DIFFERENCE != 0 )); then
  echo "Pulling $CUBE_DIFFERENCE commits from Cube3D"
else
  echo "No new commits from Cube3D"
fi

CUBE_LAST=$(git log -1 --pretty=%B | sed 's/ *$//g')
echo "Last commit of Cube3D: $CUBE_LAST"
