#include "ui/main_window.h"

// init the main window
void ui_main_window_init(GtkApplication *app)
{
	GtkWidget *main = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(main), "Обозреватель заданий");
	gtk_window_present(GTK_WINDOW(main));
}