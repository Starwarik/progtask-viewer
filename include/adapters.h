// this module requiers refactoring
// propably, it is possible to return things from the function
// but maybe it's not, because we pass one pointer,
// that's why we need adapter

#include <gtk/gtk.h>

// struct for app settings
// describes data that need to be stored in the file
typedef struct AppSettings
{
	gchar *dirpath; // path to working dir
	guint max_depth; // max depth of scanning
} AppSettings;

AppSettings *app_settings_new(gchar *dirpath, guint max_depth);
void app_settings_free(AppSettings *settings);

// ---------------------------------

// adapter for callbacks
// to return app settings from ui
typedef struct RootDialogAdapter
{
	AppSettings *settings; // settings object
	GtkWidget *parent_window; // parent window for dialog modality
	GtkWidget *entry; // dirpath entry
	GtkWidget *spin_button; // spin to choose max depth
} RootDialogAdapter;

RootDialogAdapter *root_dialog_adapter_new(AppSettings *settings, GtkWidget *parent_window, GtkWidget *entry, GtkWidget *spin_button);
void root_dialog_adapter_free(RootDialogAdapter *adapter);

// ---------------------------------

// struct to contain root chooser window widgets
// maybe useless, idk

typedef struct RootChooserStruct
{
	GtkWidget *window; // root chooser window
	GtkWidget *grid; // grid to layout elements
	GtkWidget *label; // label to describe purpose
	GtkWidget *entry; // dirpath entry
	GtkWidget *spin_button; // spin for max_depth
	GtkWidget *browse; // browse to open file dialog
	GtkWidget *from_settings; // button to load settings
	GtkWidget *confirm; // button to confirm settings
} RootChooserStruct;

RootChooserStruct *root_chooser_new(
	GtkWidget *window,
	GtkWidget *grid,
	GtkWidget *label,
	GtkWidget *entry,
	GtkWidget *spin_button,
	GtkWidget *browse,
	GtkWidget *from_settings,
	GtkWidget *confirm);

void root_chooser_free(RootChooserStruct *root_chooser);

// ---------------------------------

// struct to contain main window widgets

typedef struct MainWindowStruct
{
	GtkWidget *window;
	// etc
} MainWindowStruct;

MainWindowStruct *main_window_new(
	GtkWidget *window);

void main_window_free(MainWindowStruct *main);

// ---------------------------------

// struct to contain app data
// (window structs, dirtree root node, ...)

typedef struct AppData
{
	MainWindowStruct *main;
	RootChooserStruct *root_chooser;
	GNode *dirtree;
	AppSettings *settings;
} AppData;

AppData *app_data_new(
	MainWindowStruct *main,
	RootChooserStruct *root_chooser,
	GNode *dirtree,
	AppSettings *settings);

void app_data_free(AppData *data);