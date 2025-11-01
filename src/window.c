#include "window.h"
#include "editor.h"
#include <gtksourceview/gtksource.h>

struct _UmmideWindow
{
  GtkApplicationWindow parent_instance;
  
  GtkWidget *header_bar;
  GtkWidget *run_button;
  GtkWidget *open_button;
  GtkWidget *save_button;
  GtkWidget *editor;
  GtkWidget *output_view;
  GtkWidget *paned;
};

G_DEFINE_FINAL_TYPE(UmmideWindow, ummide_window, GTK_TYPE_APPLICATION_WINDOW)

static void
on_run_clicked(GtkButton *button, UmmideWindow *self)
{
  ummide_editor_run_code(UMMIDE_EDITOR(self->editor), GTK_TEXT_VIEW(self->output_view));
}

static void
on_open_clicked(GtkButton *button, UmmideWindow *self)
{
  ummide_editor_open_file(UMMIDE_EDITOR(self->editor), GTK_WINDOW(self));
}

static void
on_save_clicked(GtkButton *button, UmmideWindow *self)
{
  ummide_editor_save_file(UMMIDE_EDITOR(self->editor), GTK_WINDOW(self));
}

static void
ummide_window_init(UmmideWindow *self)
{
  // Header bar
  self->header_bar = gtk_header_bar_new();
  gtk_window_set_titlebar(GTK_WINDOW(self), self->header_bar);
  
  // Buttons
  self->open_button = gtk_button_new_from_icon_name("document-open-symbolic");
  self->save_button = gtk_button_new_from_icon_name("document-save-symbolic");
  self->run_button = gtk_button_new_with_label("실행 (Run)");
  gtk_widget_add_css_class(self->run_button, "suggested-action");
  
  gtk_header_bar_pack_start(GTK_HEADER_BAR(self->header_bar), self->open_button);
  gtk_header_bar_pack_start(GTK_HEADER_BAR(self->header_bar), self->save_button);
  gtk_header_bar_pack_end(GTK_HEADER_BAR(self->header_bar), self->run_button);
  
  // Connect signals
  g_signal_connect(self->open_button, "clicked", G_CALLBACK(on_open_clicked), self);
  g_signal_connect(self->save_button, "clicked", G_CALLBACK(on_save_clicked), self);
  g_signal_connect(self->run_button, "clicked", G_CALLBACK(on_run_clicked), self);
  
  // Paned container
  self->paned = gtk_paned_new(GTK_ORIENTATION_VERTICAL);
  
  // Editor
  self->editor = ummide_editor_new();
  gtk_paned_set_start_child(GTK_PANED(self->paned), self->editor);
  gtk_paned_set_resize_start_child(GTK_PANED(self->paned), TRUE);
  gtk_paned_set_shrink_start_child(GTK_PANED(self->paned), FALSE);
  
  // Output view
  GtkWidget *output_scroll = gtk_scrolled_window_new();
  self->output_view = gtk_text_view_new();
  gtk_text_view_set_editable(GTK_TEXT_VIEW(self->output_view), FALSE);
  gtk_text_view_set_monospace(GTK_TEXT_VIEW(self->output_view), TRUE);
  gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(output_scroll), self->output_view);
  gtk_paned_set_end_child(GTK_PANED(self->paned), output_scroll);
  gtk_paned_set_resize_end_child(GTK_PANED(self->paned), TRUE);
  gtk_paned_set_shrink_end_child(GTK_PANED(self->paned), FALSE);
  
  gtk_window_set_child(GTK_WINDOW(self), self->paned);
  gtk_window_set_default_size(GTK_WINDOW(self), 900, 700);
}

static void
ummide_window_class_init(UmmideWindowClass *klass)
{
}

UmmideWindow *
ummide_window_new(GtkApplication *app)
{
  return g_object_new(UMMIDE_TYPE_WINDOW,
                      "application", app,
                      "title", "엄랭 IDE (Umjunsik-Lang IDE)",
                      NULL);
}