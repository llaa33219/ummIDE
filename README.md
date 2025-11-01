# 엄랭 IDE (Umjunsik-Lang IDE)

A GTK4-based IDE for the [umjunsik-lang](https://github.com/rycont/umjunsik-lang) esoteric programming language.

## Features

- Syntax-aware text editor with line numbers
- Run umjunsik-lang programs directly in the IDE
- Save and load `.umm` files
- Korean-friendly interface
- Sandboxed Flatpak environment with embedded Deno runtime

## Building

### Prerequisites

- Flatpak
- flatpak-builder
- GNOME 46 runtime and SDK

### Install runtime

```bash
flatpak install flathub org.gnome.Platform//48 org.gnome.Sdk//48
```

### Build the Flatpak

```bash
flatpak-builder --force-clean --install --user build net.bloupla.ummide.json
```

### Run

```bash
flatpak run net.bloupla.ummide
```

## Development

For local development without Flatpak:

```bash
meson setup builddir
meson compile -C builddir
./builddir/ummide
```

Note: You'll need Deno and umjunsik-lang installed locally for the runner to work.

## Flathub Submission

Before submitting to Flathub:

1. Add screenshots to the repository
2. Update screenshot URLs in `data/net.bloupla.ummide.metainfo.xml`
3. Run validation:
   ```bash
   flatpak-builder-lint manifest net.bloupla.ummide.json
   flatpak-builder-lint appdata data/net.bloupla.ummide.metainfo.xml
   ```

## License

Apache-2.0