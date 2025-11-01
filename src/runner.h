#pragma once

#include <gtk/gtk.h>

G_BEGIN_DECLS

void ummide_runner_execute(const char *code, GtkTextView *output_view);

G_END_DECLS