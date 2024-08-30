#!/bin/bash

#(cd /degallo_os/ ; sh DeGallo_Build.sh)
#(cd /degallo_app/ ; sh DeGallo_APP_Build.sh)
#(cd /degallo_app/ ; sh APP_to_BIN.sh)

# Ensure we start from the directory where the script is located
cd "$(degallo "$0")"

# Build the DeGallo OS
if [ -d "degallo_os" ]; then
    echo "Building DeGallo OS..."
    (cd degallo_os && sh DeGallo_Build.sh)
    if [ $? -ne 0 ]; then
        echo "Failed to build DeGallo OS"
        # exit 1
    fi
    echo "DeGallo OS build completed successfully"
else
    echo "Directory 'degallo_os' not found"
    # exit 1
fi

# Build the DeGallo App
if [ -d "degallo_app" ]; then
    echo "Building DeGallo App..."
    (cd degallo_app && sh DeGallo_APP_Build.sh)
    if [ $? -ne 0 ]; then
        echo "Failed to build DeGallo App"
        # exit 1
    fi
    echo "DeGallo App build completed successfully"

    echo "Converting App to BIN..."
    (cd degallo_app && sh APP_to_BIN.sh)
    if [ $? -ne 0 ]; then
        echo "Failed to convert App to BIN"
        # exit 1
    fi
    echo "App conversion to BIN completed successfully"
else
    echo "Directory 'degallo_app' not found"
    # exit 1
fi

# Pause at the end to allow user to read output
# Prompt user to press Enter before exiting
# read -p "Press Enter to exit..."

echo "Build process completed. Press Enter to exit..."
read