#include "ui/root_chooser_window.h"
#include "widgets/root_chooser_warning.h"
#include "filework/dirtree.h"
#include "filework/fileutils.h"
#include "app_prefs.h"

// data structs for root chooser window

RootChooserStruct *root_chooser_new(
	GtkWidget *window,
	GtkWidget *grid,
	GtkWidget *label,
	GtkWidget *entry,
	GtkWidget *spin_button,
	GtkWidget *browse,
	GtkWidget *from_settings,
	GtkWidget *confirm)
{
	RootChooserStruct *root_chooser = g_new0(RootChooserStruct, 1);
	if (window)
		root_chooser->window = g_object_ref(window);
	else
		root_chooser->window = NULL;
	if (grid)
		root_chooser->grid = g_object_ref(grid);
	else
		root_chooser->grid = NULL;
	if (label)
		root_chooser->label = g_object_ref(label);
	else
		root_chooser->label = NULL;
	if (entry)
		root_chooser->entry = g_object_ref(entry);
	else
		root_chooser->entry = NULL;
	if (spin_button)
		root_chooser->spin_button = g_object_ref(spin_button);
	else
		root_chooser->spin_button = NULL;
	if (browse)
		root_chooser->browse = g_object_ref(browse);
	else
		root_chooser->browse = NULL;
	if (from_settings)
		root_chooser->from_settings = g_object_ref(from_settings);
	else
		root_chooser->from_settings = NULL;
	if (confirm)
		root_chooser->confirm = g_object_ref(confirm);
	else
		root_chooser->confirm = NULL;
	return root_chooser;
}

void root_chooser_free(RootChooserStruct *root_chooser)
{
	if (root_chooser->window)
		g_object_unref(root_chooser->window);
	if (root_chooser->grid)
		g_object_unref(root_chooser->grid);
	if (root_chooser->label)
		g_object_unref(root_chooser->label);
	if (root_chooser->entry)
		g_object_unref(root_chooser->entry);
	if (root_chooser->spin_button)
		g_object_unref(root_chooser->spin_button);
	if (root_chooser->browse)
		g_object_unref(root_chooser->browse);
	if (root_chooser->from_settings)
		g_object_unref(root_chooser->from_settings);
	if (root_chooser->confirm)
		g_object_unref(root_chooser->confirm);
	g_free(root_chooser);
}

// root folder settings dialog signals

// cb when folder is selected
static void on_root_dialog_folder_selected(GObject *src, GAsyncResult *res, gpointer user_data)
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
static void on_browse_click(GtkWidget *button, gpointer user_data)
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
static void on_root_setup_confirm(GtkWidget *button, gpointer user_data)
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
		ui_show_root_chooser_warning(data->root_chooser->window, dirpath, exists, is_dir);
	}
}

void ui_root_chooser_window_init(AppData *data)
{
	// root folder setup dialog
	GtkWidget *folder_setup = gtk_window_new();
	gtk_window_set_title(GTK_WINDOW(folder_setup), "Параметры сканирования");
	//gtk_window_set_default_size(folder_setup, 500, 250);
	
	// grid creation
	GtkWidget *grid = gtk_grid_new();
	gtk_window_set_child(GTK_WINDOW(folder_setup), grid);

	// label creation
	GtkWidget *description = gtk_label_new("Выберите корневую папку и уровень вложенности заданий");
	gtk_grid_attach(GTK_GRID(grid), description, 0, 0, 4, 1);
	
	GtkWidget *path_entry = gtk_entry_new();
	gtk_grid_attach(GTK_GRID(grid), path_entry, 0, 1, 3, 1);

	// spin button to choose depth
	GtkWidget *depth_chooser = gtk_spin_button_new_with_range(1, 15, 1);
	gtk_grid_attach(GTK_GRID(grid), depth_chooser, 3, 1, 1, 1);

	// data adapter for cb to get path and depth. Requiers settings, parent window, entry, spinbutton
	// (at least settings)
	// we will add spinbutton later
	data->settings = app_settings_new(NULL, 0);
	data->root_chooser = root_chooser_new(folder_setup,
																				grid,
																				description,
																				path_entry,
																				depth_chooser,
																				NULL,
																				NULL,
																				NULL);
	
	// browse button. Calls file dialog to choose folder
	GtkWidget *browse = gtk_button_new_with_label("Найти...");
	gtk_grid_attach(GTK_GRID(grid), browse, 0, 2, 1, 1);
	g_signal_connect(browse, "clicked", G_CALLBACK(on_browse_click), data);

	// confirm button to apply changes to settings
	GtkWidget *confirm = gtk_button_new_with_label("Сохранить");
	gtk_grid_attach(GTK_GRID(grid), confirm, 3, 2, 1, 1);
	g_signal_connect(confirm, "clicked", G_CALLBACK(on_root_setup_confirm), data);

	// styling root folder setup dialog
	gtk_window_present(GTK_WINDOW(folder_setup));
}