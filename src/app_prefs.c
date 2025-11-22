#include "app_prefs.h"
#include "ui/root_chooser_window.h"
#include "ui/main_window.h"
#include "filework/navigator.h"

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

AppData *app_data_new(
	MainWindowStruct *main,
	RootChooserStruct *root_chooser,
	NavigatorStruct *nav,
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
	if (nav)
		data->nav = nav;
	else
		data->nav = NULL;
	if (settings)
		data->settings = settings;
	else
		data->settings = NULL;
	return data;
}

void app_data_free(AppData *data)
{
	if (data->main)
		main_window_free(data->main);
	if (data->root_chooser)
		root_chooser_free(data->root_chooser);
	if (data->nav)
		navigator_free(data->nav);
	if (data->settings)
		app_settings_free(data->settings);
	g_free(data);
}