#include "signals.h"
#include "adapters.h"
#include "dirtree.h"
#include "filestruct.h"
#include "ui.h"
#include "fileutils.h"

// root folder settings dialog signals

// cb when folder is selected
void on_root_dialog_folder_selected(GObject *src, GAsyncResult *res, gpointer user_data)
{
	AppData *data = (AppData*)user_data;
	GFile *folder = gtk_file_dialog_select_folder_finish(GTK_FILE_DIALOG(src),
																											res,
																											NULL);
	const gchar *dirpath = g_file_get_path(folder);
	gtk_editable_set_text(GTK_EDITABLE(data->root_chooser->entry), dirpath);

	g_free((gpointer)dirpath);
	g_object_unref(folder);
}

// browse button cb, calls file dialog
void on_browse_click(GtkWidget *button, gpointer user_data)
{
	// app data (settings, windows, etc...)
	AppData *data = (AppData*)user_data;

	GtkFileDialog *browse_dialog = gtk_file_dialog_new();
	gtk_file_dialog_set_title(browse_dialog, "Выберите корневую папку");

	// propably no callback, because no operation requiered
	// only put in entry, but this could be done inside this func
	gtk_file_dialog_select_folder(browse_dialog,
																GTK_WINDOW(data->root_chooser->window), // need to pass parent window
																NULL,
																on_root_dialog_folder_selected,
																data);
}

// confirm button in setup window
void on_root_setup_confirm(GtkWidget *button, gpointer user_data)
{
	AppData *data = (AppData*)user_data;
	// owned by gtk - must not be freed
	const char *dirpath = gtk_editable_get_text(GTK_EDITABLE(data->root_chooser->entry));
	// get folder and check it's existence and folderness
	GFile *folder = g_file_new_for_path(dirpath);
	gboolean exists = g_file_query_exists(folder, NULL);
	gboolean is_dir = fileutils_is_directory_by_fileinfo(fileutils_get_file_info(folder));
	if (exists && is_dir)
	{
		data->settings->dirpath = g_strdup(dirpath);
		data->settings->max_depth = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(data->root_chooser->spin_button));
		data->dirtree = dirtree_create(data->settings->dirpath, data->settings->max_depth);
		gtk_window_close(GTK_WINDOW(data->root_chooser->window));
	} else
	{
		ui_show_root_folder_warning(data->root_chooser->window, dirpath, exists, is_dir);
	}
}