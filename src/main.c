#include <gtk/gtk.h>
#include "filework/dirtree.h"
#include "app_prefs.h"
#include "ui/root_chooser_window.h"
#include "ui/main_window.h"

// app signals
// this callback is called on startup signal
void app_init(GtkApplication *app, gpointer user_data)
{
  AppData *data = (AppData*)user_data;
  main_window_init(app, data);
  root_chooser_window_init(data);
}

void app_activate(GtkApplication *app, gpointer user_data)
{
  // just to remove noisy warning message :)
}

// this is called on shutdown signal
void app_cleanup(gpointer *user_data)
{
  AppData *data = (AppData*)user_data;
  
	dirtree_free(data->dirtree);
}

int main(int argc, char **argv)
{
  GtkApplication *app;
  int status;
  app = gtk_application_new("ru.starcomp.viewer", G_APPLICATION_DEFAULT_FLAGS);
  AppData *data = app_data_new(NULL, NULL, NULL, NULL);
  g_signal_connect(app, "startup", G_CALLBACK(app_init), data);
  g_signal_connect(app, "activate", G_CALLBACK(app_activate), NULL);
  g_signal_connect(app, "shutdown", G_CALLBACK(app_cleanup), data);
  status = g_application_run(G_APPLICATION (app), argc, argv);
  g_object_unref(app);

  return status;
}