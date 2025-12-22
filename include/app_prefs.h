#include <gtk/gtk.h>

// forward declarations for window structs
// as pointers on them are part of AppData definition
typedef struct MainWindowStruct MainWindowStruct;
typedef struct RootChooserStruct RootChooserStruct;
typedef struct NavigatorStruct NavigatorStruct;

// struct for app settings
// describes data that need to be stored in the file
typedef struct AppSettings
{
	gchar *dirpath; // path to working dir
	guint max_depth; // max depth of scanning
	gchar *dirignore; // string containing folder names to be ignored
} AppSettings;

AppSettings *app_settings_new(gchar *dirpath, guint max_depth, gchar *dirignore);
void app_settings_free(AppSettings *settings);

// struct to contain app data
// (window structs, dirtree root node, ...)

typedef struct AppData
{
	MainWindowStruct *main;
	RootChooserStruct *root_chooser;
	NavigatorStruct *nav;
	AppSettings *settings;
} AppData;

AppData *app_data_new(
	MainWindowStruct *main,
	RootChooserStruct *root_chooser,
	NavigatorStruct *nav,
	AppSettings *settings);

void app_data_free(AppData *data);