#!/bin/bash
# Automated script to make a 
# git commit & push

git pull
git add .
git add -u
git commit -m update
git push
git status
