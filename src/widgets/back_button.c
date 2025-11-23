#include "widgets/back_button.h"
#include "filework/navigator.h"
#include "app_prefs.h"
#include "widgets/paned.h"
#include "ui/main_window.h"
#include "widgets/folder_button_container.h"

static void on_click_go_parent(GtkWidget *button, gpointer user_data)
{
	AppData *data = (AppData*)user_data;
	navigator_to_parent(data->nav);
	paned_change_child(
			data->main->paned,
			(gpointer)folder_button_container_new(),
			PANED_CHILD_FOLDER_CONTAINER,
			1);
}

GtkWidget* back_button_new(AppData *data)
{
	GtkWidget *button = gtk_button_new();
	
	GtkWidget *picture = gtk_picture_new_for_filename("resources\\back_arrow.png");
	gtk_widget_set_hexpand(picture, false);
	gtk_widget_set_vexpand(picture, false);
	gtk_widget_set_halign(picture, GTK_ALIGN_CENTER);
	gtk_widget_set_valign(picture, GTK_ALIGN_CENTER);
	gtk_widget_set_size_request(picture, 70, 70);

	gtk_button_set_child(GTK_BUTTON(button), picture);

	g_signal_connect(button, "clicked", G_CALLBACK(on_click_go_parent), data);
	return button;
}