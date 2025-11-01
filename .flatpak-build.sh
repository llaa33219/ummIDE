#!/bin/bash

# Complete workaround: Build entirely in local directory, then sync back

set -e

PROJECT_NAME="umjunsik-lang-IDE"
LOCAL_BUILD="$HOME/.cache/flatpak-builds/$PROJECT_NAME"
CURRENT_DIR="$(pwd)"

echo "Setting up local build directory..."
mkdir -p "$LOCAL_BUILD"

# Sync source files to local directory
echo "Syncing files to local build directory..."
rsync -av --exclude='.git' --exclude='build' --exclude='.flatpak-builder' "$CURRENT_DIR/" "$LOCAL_BUILD/"

# Build in local directory
echo "Building in local filesystem..."
cd "$LOCAL_BUILD"
flatpak-builder --force-clean --ccache build net.bloupla.ummide.json

# Sync build output back
echo "Syncing build output back to Google Drive..."
rsync -av "$LOCAL_BUILD/build/" "$CURRENT_DIR/build/"

echo "Build complete! Output synced to $CURRENT_DIR/build"
