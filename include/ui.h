#include <gtk/gtk.h>
#include "adapters.h"
#include "signals.h"

void ui_main_window_init(GtkApplication *app);
void ui_root_folder_dialog_init(AppData *data);
void ui_show_root_folder_warning(
	GtkWidget *parent,
	const char *dirpath,
	gboolean exists,
	gboolean is_dir);