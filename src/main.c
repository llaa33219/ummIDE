#include <gtk/gtk.h>
#include "window.h"

static void
on_activate(GtkApplication *app)
{
  UmmideWindow *window = ummide_window_new(app);
  gtk_window_present(GTK_WINDOW(window));
}

int
main(int argc, char *argv[])
{
  g_autoptr(GtkApplication) app = NULL;
  int status;

  app = gtk_application_new("net.bloupla.ummide", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);

  return status;
}