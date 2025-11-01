#!/bin/bash

# Flatpak build script for Google Drive mounted directories
# This script uses local cache to avoid 'Operation not permitted' errors

set -e

# Create local cache directory
LOCAL_CACHE="$HOME/.cache/flatpak-builder-umjunsik"
mkdir -p "$LOCAL_CACHE"

# Build with local state directory
flatpak-builder \
  --force-clean \
  --state-dir="$LOCAL_CACHE/flatpak-builder" \
  --ccache \
  build \
  net.bloupla.ummide.json

echo "Build complete! Output in ./build directory"
