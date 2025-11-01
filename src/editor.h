#pragma once

#include <gtk/gtk.h>
#include <gtksourceview/gtksource.h>

G_BEGIN_DECLS

#define UMMIDE_TYPE_EDITOR (ummide_editor_get_type())
G_DECLARE_FINAL_TYPE(UmmideEditor, ummide_editor, UMMIDE, EDITOR, GtkScrolledWindow)

GtkWidget *ummide_editor_new(void);
void ummide_editor_open_file(UmmideEditor *self, GtkWindow *parent);
void ummide_editor_save_file(UmmideEditor *self, GtkWindow *parent);
void ummide_editor_run_code(UmmideEditor *self, GtkTextView *output_view);

G_END_DECLS