#/bin/bash

# Import some functions for a
# fancy output
resources=".resources"
newProjPath="$resources/newProject"
source "$newProjPath/errors.sh"

# No args? -> exit
if [ $# -eq 0 ]; then
  printError "No arguments provided."
  exit $exitError
fi;

# Variables
project=""
lang="c"  
langs=("c" "cpp" "rust")


for arg in "$@"; do
 
  # Display the help message??
  if [[ $arg == "--help" ]]; then
    if [ $# -eq 1 ]; then
      # Only if '--help' is the only 
      # parameter to the script
      cat "$newProjPath/help.txt"
      exit $exitSuccess
    else
      printError "Bad argument list."
      exit $exitError
    fi
  fi

  # Get the project's name. 
  if [[ $arg == --name=* ]]; then
    project="${arg#*=}"
    continue 
  fi

  # Get the project's languaje
  if [[ $arg == --lang=* ]]; then  
    lang="${arg#*=}"
    found=0
    for item in "${langs[@]}"; do
      if [ $item == $lang ]; then
        found=1
        break
      fi
    done
    if [ $found -eq 0 ]; then
      printError "'$lang': Language not available."
      exit $exitError
    fi
    continue
  fi
  
  # No matching arguments
  printError "'$arg': Unknown argument."
  exit $exitError
done

if [[ $project == "" ]]; then 
  # After arguments parsing, there was no "--name"
  # parameter or it was empty
  printError "Argument '--name=' not found or empty."
  printError "You must provide a name for the project."
  exit $exitError
fi

#Check if the project already
# exists (Folder with the same name)
if [ -d "$project" ]; then
  printError "'$project': Project already exists."
  exit $exitError
fi;

# Create the project
printInfo "Creating the project..."
printInfo "Copiying files..."

if [[ $lang == "c" ]]; then 
  mkdir $project
  cp -r "$resources/example_c/"* $project
elif [[ $lang == "cpp" ]]; then
  mkdir $project
  cp -r "$resources/example_cpp/"* $project
elif [[ $lang == "rust" ]]; then
  cargo new $project
fi

printInfo "Finished."
exit $exitSuccess
