#pragma once

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define UMMIDE_TYPE_WINDOW (ummide_window_get_type())
G_DECLARE_FINAL_TYPE(UmmideWindow, ummide_window, UMMIDE, WINDOW, GtkApplicationWindow)

UmmideWindow *ummide_window_new(GtkApplication *app);

G_END_DECLS