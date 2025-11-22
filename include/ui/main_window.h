#include <gtk/gtk.h>

typedef struct AppData AppData;
typedef struct PanedStruct PanedStruct;

// struct to contain main window widgets
typedef struct MainWindowStruct
{
	GtkWidget *window;
	PanedStruct *paned; // paned with widgets (fuck no)
	gboolean opened;
	// etc
} MainWindowStruct;

MainWindowStruct *main_window_new(
	GtkWidget *window,
	PanedStruct *paned);

void main_window_set_opened(MainWindowStruct *main_window_data, gboolean opened);

void main_window_free(MainWindowStruct *main);

// window init
void main_window_init(GtkApplication *app, AppData *data);

void main_window_activate(AppData *data);