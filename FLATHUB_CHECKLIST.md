# Flathub Submission Checklist

## Before Submitting

### Required Files
- [x] `net.bloupla.ummide.json` - Flatpak manifest
- [x] `data/net.bloupla.ummide.metainfo.xml` - AppData metadata
- [x] `data/net.bloupla.ummide.desktop` - Desktop entry
- [x] `data/net.bloupla.ummide.svg` - Application icon
- [x] `flathub.json` - Flathub configuration
- [ ] `screenshots/main-window.png` - Screenshot (MUST ADD)

### Validation Steps

```bash
# 1. Install linter
flatpak install flathub org.flatpak.Builder

# 2. Validate manifest
flatpak-builder-lint manifest net.bloupla.ummide.json

# 3. Validate AppData
flatpak-builder-lint appdata data/net.bloupla.ummide.metainfo.xml

# 4. Test build locally
flatpak-builder --force-clean --install --user build net.bloupla.ummide.json

# 5. Test run
flatpak run net.bloupla.ummide
```

### Pre-Submission Tasks

1. [ ] Take screenshots of the running application
2. [ ] Add screenshots to `/screenshots` directory
3. [ ] Update screenshot URL in metainfo.xml if needed
4. [ ] Run all validation commands above
5. [ ] Fix any errors or warnings
6. [ ] Test on both x86_64 and aarch64 (if possible)

### GitHub Repository Setup

1. [ ] Create repository at https://github.com/bloupla/umjunsik-lang-ide
2. [ ] Push all code including screenshots
3. [ ] Verify screenshot URLs are accessible

### Flathub Submission

1. [ ] Fork https://github.com/flathub/flathub
2. [ ] Create new directory: `net.bloupla.ummide`
3. [ ] Copy these files to the directory:
   - `net.bloupla.ummide.json`
   - `flathub.json`
4. [ ] Create Pull Request with title: "Add net.bloupla.ummide"
5. [ ] Respond to reviewer feedback promptly

### Common Issues to Avoid

- ✅ Removed excessive filesystem permissions
- ✅ Added developer information
- ✅ Included proper license (GPL-3.0-or-later)
- ✅ Added release notes
- ✅ Specified supported architectures
- ⚠️ Screenshot URLs must be accessible from GitHub
- ⚠️ All linter errors must be fixed

### After Approval

- Monitor build status on Flathub
- Update screenshots if reviewers request
- Keep manifest updated for future releases