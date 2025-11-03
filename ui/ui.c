#include "ui.h"
#include <string.h>

void ui_show_root_folder_warning(
	GtkWidget *parent,
	const char *dirpath,
	gboolean exists,
	gboolean is_dir)
{
	if (!strcmp(dirpath, ""))
	{
		GtkAlertDialog *dialog = gtk_alert_dialog_new("Вам нужно выбрать корневую папку!\nЗакройте меня и сделайте это!");
		gtk_alert_dialog_show(dialog, GTK_WINDOW(parent));
		g_object_unref(dialog);
	} else if (!exists)
	{
		GtkAlertDialog *dialog = gtk_alert_dialog_new("Указанный файл не существует!\nЗакройте меня и выберите папку!");
		gtk_alert_dialog_show(dialog, GTK_WINDOW(parent));
		g_object_unref(dialog);
	} else if (!is_dir)
	{
		GtkAlertDialog *dialog = gtk_alert_dialog_new("Указанный файл не является папкой!\nЗакройте меня и выберите папку!");
		gtk_alert_dialog_show(dialog, GTK_WINDOW(parent));
		g_object_unref(dialog);
	}
}

void ui_root_folder_dialog_init(AppData *data)
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

void ui_tree_view_paned_init()
{

}

void ui_tree_view_paned_change()
{
	
}

// init the ui
void ui_main_window_init(GtkApplication *app)
{
	// main window
	GtkWidget *main = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(main), "Обозреватель заданий");
	gtk_window_present(GTK_WINDOW(main));
}