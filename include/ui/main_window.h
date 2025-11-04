#include <gtk/gtk.h>

typedef struct AppData AppData;

// struct to contain main window widgets
typedef struct MainWindowStruct
{
	GtkWidget *window;
	gboolean opened;
	// etc
} MainWindowStruct;

MainWindowStruct *main_window_new(
	GtkWidget *window);

void main_window_set_opened(MainWindowStruct *main_window_data, gboolean opened);

void main_window_free(MainWindowStruct *main);

// window init
void main_window_init(GtkApplication *app, AppData *data);