#!/bin/bash

git status | grep -q "On branch master
Your branch is up to date with 'origin/master'.

nothing to commit, working tree clean
"

if (( $? != 0 )); then
  echo "Your working tree is not clean"
  exit 1
fi

BRANCH=$(git rev-parse --abbrev-ref HEAD)

git fetch --all
git checkout Dev
git pull
git checkout "$BRANCH"
git merge Dev

if (( $? != 0 )); then
  echo "Error when merging Dev into $BRANCH"
  exit 1
fi

git push
git checkout Dev
git merge "$BRANCH"

if (( $? != 0 )); then
  echo "Error when merging $BRANCH into Dev"
  exit 1
fi

git push
git checkout "$BRANCH"