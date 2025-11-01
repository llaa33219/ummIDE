#!/bin/bash

echo "Fetching Deno SHA256 hashes..."
echo ""

echo "x86_64:"
curl -sL https://github.com/denoland/deno/releases/download/v2.4.5/deno-x86_64-unknown-linux-gnu.zip | sha256sum | cut -d' ' -f1

echo ""
echo "aarch64:"
curl -sL https://github.com/denoland/deno/releases/download/v2.4.5/deno-aarch64-unknown-linux-gnu.zip | sha256sum | cut -d' ' -f1

echo ""
echo "Update these values in net.bloupla.ummide.json"