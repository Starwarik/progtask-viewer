#include "widgets/root_chooser_warning.h"

void ui_show_root_chooser_warning(
	GtkWidget *parent,
	const char *dirpath,
	gboolean exists,
	gboolean is_dir)
{
	if (!strcmp(dirpath, ""))
	{
		GtkAlertDialog *dialog = gtk_alert_dialog_new("Вам нужно выбрать корневую папку!\nЗакройте меня и сделайте это!");
		gtk_alert_dialog_show(dialog, GTK_WINDOW(parent));
		g_object_unref(dialog);
	} else if (!exists)
	{
		GtkAlertDialog *dialog = gtk_alert_dialog_new("Указанный файл не существует!\nЗакройте меня и выберите папку!");
		gtk_alert_dialog_show(dialog, GTK_WINDOW(parent));
		g_object_unref(dialog);
	} else if (!is_dir)
	{
		GtkAlertDialog *dialog = gtk_alert_dialog_new("Указанный файл не является папкой!\nЗакройте меня и выберите папку!");
		gtk_alert_dialog_show(dialog, GTK_WINDOW(parent));
		g_object_unref(dialog);
	}
}