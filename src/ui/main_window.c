#include "ui/main_window.h"
#include "app_prefs.h"

MainWindowStruct *main_window_new(GtkWidget *window)
{
	MainWindowStruct *data = g_new0(MainWindowStruct, 1);
	if (window)
		data->window = g_object_ref(window);
	else
		data->window = NULL;
	data->opened = FALSE;
	return data;
}

void main_window_set_opened(MainWindowStruct *main_window_data, gboolean opened)
{
	main_window_data->opened = opened;
}

void main_window_free(MainWindowStruct *main)
{
	if (main)
	{
		if (main->window)
			g_object_unref(main->window);
		g_free(main);
	}
}

// init the main window
void main_window_init(GtkApplication *app, AppData *data)
{
	GtkWidget *main = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(main), "Обозреватель заданий");
	// add window to app data
	data->main = main_window_new(main);
}