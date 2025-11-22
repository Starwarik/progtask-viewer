#include "widgets/folder_button_container.h"
#include "widgets/folder_button.h"
#include "app_prefs.h"
#include "ui/main_window.h"
#include "filework/navigator.h"

FolderButtonContainerStruct* folder_button_container_new()
{
	FolderButtonContainerStruct *self = g_new0(FolderButtonContainerStruct, 1);

	self->scroll = g_object_ref(gtk_scrolled_window_new());
	self->container = gtk_flow_box_new();
	gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(self->scroll), self->container);

	self->button_array = g_ptr_array_new();
	
	return self;
}

void folder_button_container_free(
	FolderButtonContainerStruct *self
)
{
	if (self)
	{
		g_object_unref(self->scroll);
		for (guint i = 0; i < self->button_array->len; i++)
		{
			folder_button_free((FolderButtonStruct*)g_ptr_array_index(self->button_array, i));
		}
		g_ptr_array_unref(self->button_array);
		g_free(self);
	}
}

void folder_button_container_render(
	AppData *data,
	FolderButtonContainerStruct *container)
{
	GPtrArray *child_nodes = navigator_discover(data->nav);
	g_print("render: nodes discovered\n");
	// populate the container
	for (guint i = 0; i < child_nodes->len; i++)
	{
		// create i-th button
		g_print("render: entered %u iteration\n", i);
		FolderButtonStruct *button_data = folder_button_new(
			(GNode*)(child_nodes->pdata[i]),
			data
		);
		g_print("render: %u button was created\n", i);
		// append button to the container
		folder_button_container_append(
			container,
			button_data
		);
		g_print("render: %u button was appended to the container\n", i);
	}
	g_ptr_array_unref(child_nodes);
}

void folder_button_container_append(
	FolderButtonContainerStruct *self,
	FolderButtonStruct *button_data
)
{
	g_ptr_array_add(self->button_array, (gpointer)button_data);
	gtk_flow_box_append(GTK_FLOW_BOX(self->container), button_data->button);
}

// FUTURE FEATURES FOR OPTIMIZATION

/*void folder_button_container_pop(
	FolderButtonContainerStruct *self
)
{
	if (self->button_array->len > 0)
	{
		FolderButtonStruct *button_data = g_array_index(
																			self->button_array,
																			FolderButtonStruct*,
																			self->button_array->len-1);
		self->button_array = g_array_remove_index_fast(
												self->button_array,
												self->button_array->len-1);
	}
}*/

/*void folder_button_container_refresh(
	FolderButtonContainerStruct *self,
	FolderButtonStruct *button_data,
	guint index_
)
{
	g_print("\nentered refresh function\n");
	FolderButtonStruct *old_button_data = g_array_index(
																			self->button_array,
																			FolderButtonStruct*,
																			index_);
	self->button_array = g_array_remove_index(
											self->button_array,
											index_);
	g_print("removed old button from array\n");
	self->button_array = g_array_insert_vals(
											self->button_array,
											index_,
											button_data,
											1);
	g_print("added new button in array\n");
	gtk_flow_box_append(GTK_FLOW_BOX(self->container), button_data->button);
}*/