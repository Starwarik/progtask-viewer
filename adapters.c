#include "adapters.h"

AppSettings *app_settings_new(gchar *dirpath, guint max_depth)
{
	AppSettings *settings = g_new0(AppSettings, 1);
	settings->dirpath = dirpath;
	settings->max_depth = max_depth;
	return settings;
}

void app_settings_free(AppSettings *settings)
{
	g_free(settings->dirpath);
	g_free(settings);
}

RootDialogAdapter *root_dialog_adapter_new(AppSettings *settings, GtkWidget *parent_window, GtkWidget *entry, GtkWidget *spin_button)
{
	RootDialogAdapter *adapter = g_new0(RootDialogAdapter, 1);
	/*if (!(parent_window || spin_button || entry))
	{
		g_print("you need to provide some widget (RootDialogAdapter)");
		return NULL;
	}*/
	if (parent_window)
		adapter->parent_window = g_object_ref(parent_window);
	else
		adapter->parent_window = NULL;
	if (entry)
		adapter->entry = g_object_ref(entry);
	else
		adapter->entry = NULL;
	if (spin_button)
		adapter->spin_button = g_object_ref(spin_button);
	else
		adapter->spin_button = NULL;
	if (!settings)
	{
		g_print("eeee blyaa (RootDialogAdapter)");
		return NULL;
	}
	adapter->settings = settings;
	return adapter;
}

void root_dialog_adapter_free(RootDialogAdapter *adapter)
{
	if (adapter->parent_window)
		g_object_unref(adapter->parent_window);
	if (adapter->entry)
		g_object_unref(adapter->entry);
	if (adapter->spin_button)
		g_object_unref(adapter->spin_button);
	adapter->settings = NULL;
	g_free(adapter);
}

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

// NEED TO WRITE DUMMY FUNCS FOR MAIN WINDOW

AppData *app_data_new(
	MainWindowStruct *main,
	RootChooserStruct *root_chooser,
	GNode *dirtree,
	AppSettings *settings)
{
	AppData *data = g_new0(AppData, 1);
	if (main)
		data->main = main;
	else
		data->main = NULL;
	if (root_chooser)
		data->root_chooser = root_chooser;
	else
		data->root_chooser = NULL;
	if (dirtree)
		data->dirtree = g_object_ref(dirtree);
	else
		data->dirtree = NULL;
	if (settings)
		data->settings = settings;
	else
		data->settings = NULL;
	return data;
}

void app_data_free(AppData *data)
{
	//if (data->main)
		//main_window_free(data->main);
	if (data->root_chooser)
		root_chooser_free(data->root_chooser);
	if (data->dirtree)
		g_object_unref(data->dirtree);
	if (data->settings)
		app_settings_free(data->settings);
	g_free(data);
}