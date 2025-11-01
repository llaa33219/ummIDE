# Contributing to 엄랭 IDE

## Development

### Building

```bash
# Install development dependencies (only needed for building, not for end users)
flatpak install flathub org.gnome.Platform//48 org.gnome.Sdk//48

# Build and install
flatpak-builder --force-clean --install --user build net.bloupla.ummide.json

# Run
flatpak run net.bloupla.ummide
```

### Testing

```bash
# Validate manifest
flatpak-builder-lint manifest net.bloupla.ummide.json

# Validate AppData
flatpak-builder-lint appdata data/net.bloupla.ummide.metainfo.xml

# Build test
flatpak-builder --force-clean build net.bloupla.ummide.json
```

## Flathub Submission

Before submitting to Flathub:

1. Ensure all linter checks pass
2. Add screenshots to `/screenshots` directory
3. Update screenshot URLs in metainfo.xml
4. Test on both x86_64 and aarch64 if possible
5. Verify sandbox permissions are minimal

## License

Apache-2.0