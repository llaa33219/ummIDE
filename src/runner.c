#include "runner.h"
#include <gio/gio.h>
#include <unistd.h>
#include <string.h>

void
ummide_runner_execute(const char *code, GtkTextView *output_view)
{
  g_autoptr(GError) error = NULL;
  g_autofree char *temp_file = NULL;
  int fd;
  
  // Create temporary file
  fd = g_file_open_tmp("ummide-XXXXXX.umm", &temp_file, &error);
  if (fd == -1) {
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(output_view);
    gtk_text_buffer_set_text(buffer, "Error creating temp file\n", -1);
    return;
  }
  
  // Write code to temp file
  write(fd, code, strlen(code));
  close(fd);
  
  // Build command
  const char *deno_path = "/app/bin/deno";
  const char *runtime_path = "/app/share/umjunsik-lang/main.ts";
  
  g_autofree char *command = g_strdup_printf("%s run --allow-read %s %s",
                                             deno_path, runtime_path, temp_file);
  
  // Execute command
  g_autofree char *stdout_output = NULL;
  g_autofree char *stderr_output = NULL;
  int exit_status;
  
  if (g_spawn_command_line_sync(command, &stdout_output, &stderr_output, &exit_status, &error)) {
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(output_view);
    
    if (stdout_output && strlen(stdout_output) > 0) {
      gtk_text_buffer_set_text(buffer, stdout_output, -1);
    } else if (stderr_output && strlen(stderr_output) > 0) {
      g_autofree char *error_msg = g_strdup_printf("오류 (Error):\n%s", stderr_output);
      gtk_text_buffer_set_text(buffer, error_msg, -1);
    } else {
      gtk_text_buffer_set_text(buffer, "실행 완료 (Execution completed)\n", -1);
    }
  } else {
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(output_view);
    g_autofree char *error_msg = g_strdup_printf("실행 실패 (Execution failed):\n%s", error->message);
    gtk_text_buffer_set_text(buffer, error_msg, -1);
  }
  
  // Clean up
  g_unlink(temp_file);
}