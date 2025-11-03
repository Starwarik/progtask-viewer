#include <gtk/gtk.h>

void ui_show_root_chooser_warning(
	GtkWidget *parent,
	const char *dirpath,
	gboolean exists,
	gboolean is_dir);