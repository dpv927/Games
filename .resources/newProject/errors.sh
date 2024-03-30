# !/bin/bash 

# Text Colors
red='\033[0;31m'
green='\033[0;32m'
yellow='\033[0;33m'
blue='\033[0;34m'
purple='\033[0;35m'
cyan='\033[0;36m'
white='\033[0;37m'

# Text format
bold='\033[1m'
underline='\033[4m'
blink='\033[5m'
reset='\033[0m'

printError() {
  # Print a Error message
  echo -e "${red}${bold}Error: ${reset}${1}" 
}

printInfo() {
  # Print a Info message
  echo -e "${green}${bold}Info: ${reset}${1}" 
}

printWarning() {
  # Print a Warning message
  echo -e "${yellow}${bold}Warning: ${reset}${1}" 
}

exitError=1
exitSuccess=0
