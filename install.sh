#!/bin/bash

# Define the Pyro directory and binary location
PYRO_DIR=$(pwd) # Get the current directory (should be ~/R/Pyro)
PYRO_BIN="$PYRO_DIR/pyro"
TARGET_DIR="/usr/local/bin"

# Ensure we are inside the Pyro project directory
if [ ! -d "$PYRO_DIR" ] || [ ! -f "$PYRO_BIN" ]; then
  echo "Error: This script should be run from the Pyro directory. Exiting."
  exit 1
fi

# Check if the `pyro` binary exists
if [ ! -f "$PYRO_BIN" ]; then
  echo "Error: Pyro binary not found at $PYRO_BIN after update."
  exit 1
fi

# Check if we have root permissions to write to /usr/local/bin
if [ "$(id -u)" -ne 0 ]; then
  echo "You must have root (sudo) permissions to install Pyro globally."
  exit 1
fi

# Move the Pyro binary to /usr/local/bin
echo "Moving $PYRO_BIN to $TARGET_DIR"
sudo mv "$PYRO_BIN" "$TARGET_DIR/"

# Verify if the move was successful
if [ $? -eq 0 ]; then
  echo "Pyro binary successfully moved to $TARGET_DIR"
else
  echo "Failed to move Pyro binary to $TARGET_DIR"
  exit 1
fi

# Check if /usr/local/bin is in the PATH
if ! echo $PATH | grep -q "/usr/local/bin"; then
  echo "/usr/local/bin is not in your PATH. Adding it to ~/.bashrc"
  echo 'export PATH="/usr/local/bin:$PATH"' >>~/.bashrc
  source ~/.bashrc
  echo "/usr/local/bin added to PATH in ~/.bashrc"
else
  echo "/usr/local/bin is already in your PATH."
fi

# Verify that the `pyro` command is globally accessible
echo "Verifying if Pyro is accessible globally..."
pyro --version

# Final message
echo "Installation/Update complete. Pyro should now be available globally."
