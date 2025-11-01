project('ummide', 'c',
  version: '0.1.0',
  license: 'Apache-2.0',
  meson_version: '>= 0.59.0'
)

gnome = import('gnome')

# Dependencies
gtk4_dep = dependency('gtk4', version: '>= 4.16')
gtksourceview5_dep = dependency('gtksourceview-5', version: '>= 5.0')

# Source files
sources = files(
  'src/main.c',
  'src/window.c',
  'src/editor.c',
  'src/runner.c'
)

# Resources
resources = gnome.compile_resources(
  'ummide-resources',
  'data/ummide.gresource.xml',
  source_dir: 'data',
  c_name: 'ummide'
)

# Executable
executable('ummide',
  sources + resources,
  dependencies: [gtk4_dep, gtksourceview5_dep],
  install: true
)

# Desktop file
install_data(
  'data/net.bloupla.ummide.desktop',
  install_dir: get_option('datadir') / 'applications'
)

# Icon
install_data(
  'data/net.bloupla.ummide.svg',
  install_dir: get_option('datadir') / 'icons/hicolor/scalable/apps'
)

# AppStream metadata
install_data(
  'data/net.bloupla.ummide.metainfo.xml',
  install_dir: get_option('datadir') / 'metainfo'
)

# GtkSourceView language definition
install_data(
  'data/umjunsik.lang',
  install_dir: get_option('datadir') / 'gtksourceview-5/language-specs'
)