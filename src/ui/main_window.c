#include "ui/main_window.h"
#include "app_prefs.h"
#include "widgets/folder_button.h"
#include "widgets/folder_button_container.h"
#include "widgets/paned.h"
#include "filework/navigator.h"

MainWindowStruct *main_window_new(
	GtkWidget *window,
	PanedStruct *paned)
{
	MainWindowStruct *data = g_new0(MainWindowStruct, 1);
	if (window)
		data->window = g_object_ref(window);
	else
		data->window = NULL;
	if (paned)
		data->paned = paned;
	else
		data->paned = NULL;
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
		if (main->paned)
			paned_free(main->paned);
		g_free(main);
	}
}

// BECAUSE WE INTERACT WITH ROOT CHOOSER FIRST,
// THEN ONLY IN CONFIRM ROOT CHOOSER SIGNAL WE CAN
// RENDER THE WIDGETS OF MAIN WINDOW, BECAUSE WE GET DIRROOT
// I'M STUPID, IDK HOW TO DELAY MAIN WINDOW INIT. I WOULD DO THAT
// init the main window
void main_window_init(GtkApplication *app, AppData *data)
{
	GtkWidget *main = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(main), "Обозреватель заданий");

	// add window to app data
	data->main = main_window_new(main, paned_new(data, GTK_ORIENTATION_HORIZONTAL));
	gtk_window_set_child(GTK_WINDOW(data->main->window), data->main->paned->paned);
}

// to choose on startup between notebook and folder container
void main_window_activate(AppData *data)
{
	// if taskdir, then render notebook and terminal
	if (navigator_is_taskdir(data->nav))
	{
		
	} else // if not, render folder container
	{
		paned_change_child(
			data->main->paned,
			(gpointer)folder_button_container_new(),
			PANED_CHILD_FOLDER_CONTAINER,
			1);
	}
}