#include "editor.h"
#include "runner.h"
#include <gtksourceview/gtksource.h>

struct _UmmideEditor
{
  GtkBox parent_instance;
  
  GtkScrolledWindow *scrolled_window;
  GtkSourceView *source_view;
  GtkSourceBuffer *buffer;
  GFile *current_file;
};

G_DEFINE_FINAL_TYPE(UmmideEditor, ummide_editor, GTK_TYPE_BOX)

static void
on_open_finish(GObject *source, GAsyncResult *result, gpointer data)
{
  UmmideEditor *editor = UMMIDE_EDITOR(data);
  g_autoptr(GError) error = NULL;
  GFile *file = gtk_file_dialog_open_finish(GTK_FILE_DIALOG(source), result, &error);
  
  if (file) {
    g_autofree char *contents = NULL;
    gsize length;
    
    if (g_file_load_contents(file, NULL, &contents, &length, NULL, &error)) {
      gtk_text_buffer_set_text(GTK_TEXT_BUFFER(editor->buffer), contents, length);
      if (editor->current_file)
        g_object_unref(editor->current_file);
      editor->current_file = g_object_ref(file);
    }
  }
}

static void
on_save_finish(GObject *source, GAsyncResult *result, gpointer data)
{
  UmmideEditor *editor = UMMIDE_EDITOR(data);
  g_autoptr(GError) error = NULL;
  GFile *file = gtk_file_dialog_save_finish(GTK_FILE_DIALOG(source), result, &error);
  
  if (file) {
    GtkTextIter start, end;
    gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(editor->buffer), &start, &end);
    g_autofree char *text = gtk_text_buffer_get_text(GTK_TEXT_BUFFER(editor->buffer), &start, &end, FALSE);
    g_file_replace_contents(file, text, strlen(text), NULL, FALSE,
                           G_FILE_CREATE_NONE, NULL, NULL, NULL);
    editor->current_file = g_object_ref(file);
  }
}

static void
ummide_editor_init(UmmideEditor *self)
{
  // Create source buffer and view
  self->buffer = gtk_source_buffer_new(NULL);
  self->source_view = GTK_SOURCE_VIEW(gtk_source_view_new_with_buffer(self->buffer));
  
  // Configure source view
  gtk_source_view_set_show_line_numbers(self->source_view, TRUE);
  gtk_source_view_set_highlight_current_line(self->source_view, TRUE);
  gtk_source_view_set_tab_width(self->source_view, 2);
  gtk_source_view_set_auto_indent(self->source_view, TRUE);
  gtk_text_view_set_monospace(GTK_TEXT_VIEW(self->source_view), TRUE);
  
  // Set default text
  const char *default_text = 
    "어떻게\n"
    "엄.엄.엄.준.식.\n"
    "이 사람이름이냐ㅋㅋ\n";
  gtk_text_buffer_set_text(GTK_TEXT_BUFFER(self->buffer), default_text, -1);
  
  // Create scrolled window and add source view
  self->scrolled_window = GTK_SCROLLED_WINDOW(gtk_scrolled_window_new());
  gtk_scrolled_window_set_child(self->scrolled_window, GTK_WIDGET(self->source_view));
  gtk_scrolled_window_set_has_frame(self->scrolled_window, TRUE);
  
  // Add scrolled window to box
  gtk_box_append(GTK_BOX(self), GTK_WIDGET(self->scrolled_window));
  gtk_widget_set_vexpand(GTK_WIDGET(self->scrolled_window), TRUE);
  gtk_widget_set_hexpand(GTK_WIDGET(self->scrolled_window), TRUE);
  
  self->current_file = NULL;
}

static void
ummide_editor_finalize(GObject *object)
{
  UmmideEditor *self = UMMIDE_EDITOR(object);
  
  if (self->current_file)
    g_object_unref(self->current_file);
  
  G_OBJECT_CLASS(ummide_editor_parent_class)->finalize(object);
}

static void
ummide_editor_class_init(UmmideEditorClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS(klass);
  object_class->finalize = ummide_editor_finalize;
}

GtkWidget *
ummide_editor_new(void)
{
  return g_object_new(UMMIDE_TYPE_EDITOR, NULL);
}

void
ummide_editor_open_file(UmmideEditor *self, GtkWindow *parent)
{
  GtkFileDialog *dialog = gtk_file_dialog_new();
  GtkFileFilter *filter = gtk_file_filter_new();
  
  gtk_file_filter_set_name(filter, "엄랭 파일 (.umm)");
  gtk_file_filter_add_pattern(filter, "*.umm");
  gtk_file_dialog_set_default_filter(dialog, filter);
  
  gtk_file_dialog_open(dialog, parent, NULL, on_open_finish, self);
}

void
ummide_editor_save_file(UmmideEditor *self, GtkWindow *parent)
{
  if (self->current_file) {
    // Save to existing file
    GtkTextIter start, end;
    gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(self->buffer), &start, &end);
    g_autofree char *text = gtk_text_buffer_get_text(GTK_TEXT_BUFFER(self->buffer), &start, &end, FALSE);
    g_file_replace_contents(self->current_file, text, strlen(text), NULL, FALSE,
                           G_FILE_CREATE_NONE, NULL, NULL, NULL);
  } else {
    // Show save dialog
    GtkFileDialog *dialog = gtk_file_dialog_new();
    gtk_file_dialog_set_initial_name(dialog, "untitled.umm");
    
    gtk_file_dialog_save(dialog, parent, NULL, on_save_finish, self);
  }
}

void
ummide_editor_run_code(UmmideEditor *self, GtkTextView *output_view)
{
  GtkTextIter start, end;
  gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(self->buffer), &start, &end);
  g_autofree char *code = gtk_text_buffer_get_text(GTK_TEXT_BUFFER(self->buffer), &start, &end, FALSE);
  
  ummide_runner_execute(code, output_view);
}