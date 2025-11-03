#include <gtk/gtk.h>

// struct to contain main window widgets
typedef struct MainWindowStruct
{
	GtkWidget *window;
	// etc
} MainWindowStruct;

MainWindowStruct *main_window_new(
	GtkWidget *window);

void main_window_free(MainWindowStruct *main);

// window init
void ui_main_window_init(GtkApplication *app);