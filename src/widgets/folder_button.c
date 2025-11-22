// good approach is to create a button in the container,
// not in the navigator, but second variant is more suitable,
// so i need to apologise in front of you, dear watcher :)

#include "widgets/folder_button.h"
#include "filework/filestruct.h"
#include "filework/navigator.h"
#include "app_prefs.h"
#include "ui/main_window.h"
#include "widgets/folder_button_container.h"
#include "widgets/paned.h"

void on_folder_click(GtkWidget *button, gpointer user_data)
{
	FolderButtonStruct *button_data = (FolderButtonStruct*)user_data;
	navigator_to_subdir(button_data->data->nav, button_data->folder);
	// if taskdir, then render notebook and terminal
	if (navigator_is_taskdir(button_data->data->nav))
	{
		
	} else // if not, render folder container
	{
		paned_change_child(
			button_data->data->main->paned,
			(gpointer)folder_button_container_new(),
			PANED_CHILD_FOLDER_CONTAINER,
			1);
	}
}

FolderButtonStruct *folder_button_new(
	GNode *folder,
	AppData *data)
{
	FolderButtonStruct *button_data = g_new0(FolderButtonStruct, 1);

	FileStruct *folder_data = (FileStruct*)(folder->data);
	char *name = g_strdup(g_file_get_basename(folder_data->file));
	/*if (G_IS_FILE(folder_data))
		g_print("OMG ITS NOT A FILE\n");*/
	GtkWidget *button = gtk_button_new();

	GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);

	GtkWidget *picture = gtk_picture_new_for_filename("resources\\foldericon.png");
	gtk_widget_set_hexpand(picture, false);
	gtk_widget_set_vexpand(picture, false);
	gtk_widget_set_halign(picture, GTK_ALIGN_CENTER);
	gtk_widget_set_valign(picture, GTK_ALIGN_CENTER);
	gtk_widget_set_size_request(picture, 70, 70);
	gtk_box_append(GTK_BOX(box), picture);

	GtkWidget *label = gtk_label_new(name);
	gtk_widget_set_hexpand(label, false);
	gtk_widget_set_vexpand(label, false);
	gtk_widget_set_halign(label, GTK_ALIGN_CENTER);
	gtk_widget_set_valign(label, GTK_ALIGN_CENTER);
	gtk_box_append(GTK_BOX(box), label);

	gtk_button_set_child(GTK_BUTTON(button), box);

	button_data->button = button;
	button_data->label = label;
	button_data->folder = folder;
	button_data->data = data;
	g_free(name);
	g_signal_connect(button, "clicked", G_CALLBACK(on_folder_click), button_data);
	return button_data;
}

void folder_button_free(FolderButtonStruct *data)
{
	if (data)
	{
		g_free(data);
	}
}