#include "widgets/paned.h"
#include "widgets/folder_button_container.h"

// clear function for child
static void paned_remove_child(
	PanedStruct *self,
	guint pos)
{
	// remove child depends on pos
	if (pos == 0)
	{
		gtk_paned_set_start_child(GTK_PANED(self->paned), NULL);
		switch (self->child1_type)
		{
			case PANED_CHILD_NULL:
				break;
			case PANED_CHILD_BACK_BUTTON:
				break;
			case PANED_CHILD_FOLDER_CONTAINER:
				FolderButtonContainerStruct *container = (FolderButtonContainerStruct*)self->child1;
				folder_button_container_free(container);
				break;
			// NOT DONE NEED TO DO THESE WIDGETS
			case PANED_CHILD_WORK_PANEL:
				break;
			case PANED_CHILD_TERMINAL:
				break;
			case PANED_CHILD_NOTEBOOK:
				break;
		}
		self->child1 = NULL;
	} else // pos != 0
	{
		gtk_paned_set_end_child(GTK_PANED(self->paned), NULL);
		switch (self->child2_type)
		{
			case PANED_CHILD_NULL:
				break;
			case PANED_CHILD_BACK_BUTTON:
				break;
			case PANED_CHILD_FOLDER_CONTAINER:
				FolderButtonContainerStruct *container = (FolderButtonContainerStruct*)self->child2;
				folder_button_container_free(container);
				break;
			// NOT DONE NEED TO DO THESE WIDGETS
			case PANED_CHILD_WORK_PANEL:
				break;
			case PANED_CHILD_TERMINAL:
				break;
			case PANED_CHILD_NOTEBOOK:
				break;
		}
		self->child2 = NULL;
	}
}

static void paned_add_child(
	PanedStruct *self,
	gpointer new_child,
	PanedChildType new_child_type,
	guint pos)
{
	// add child data and type
	if (pos == 0)
	{
		self->child1 = new_child;
		self->child1_type = new_child_type;
	} else
	{
		self->child2 = new_child;
		self->child2_type = new_child_type;
	}
	
	// render child in paned depends from pos and type
	switch (new_child_type)
	{
		case PANED_CHILD_NULL:
				break;
		case PANED_CHILD_BACK_BUTTON:
			if (pos == 0)
				gtk_paned_set_start_child(GTK_PANED(self->paned), GTK_WIDGET(new_child));
			else
				gtk_paned_set_end_child(GTK_PANED(self->paned), GTK_WIDGET(new_child));
			break;
		case PANED_CHILD_FOLDER_CONTAINER:
			if (pos == 0)
			{
				FolderButtonContainerStruct *container = (FolderButtonContainerStruct*)self->child1;
				folder_button_container_render(self->data, container);
				gtk_paned_set_start_child(GTK_PANED(self->paned), container->scroll);
			} else
			{
				FolderButtonContainerStruct *container = (FolderButtonContainerStruct*)self->child2;
				folder_button_container_render(self->data, container);
				gtk_paned_set_end_child(GTK_PANED(self->paned), container->scroll);
			}
			break;
		// NOT DONE NEED TO DO THESE WIDGETS
		case PANED_CHILD_WORK_PANEL:
			break;
		case PANED_CHILD_TERMINAL:
			break;
		case PANED_CHILD_NOTEBOOK:
			break;
	}
}

void paned_change_child(
	PanedStruct *self,
	gpointer new_child,
	PanedChildType new_child_type,
	guint pos)
{
	paned_remove_child(self, pos);
	paned_add_child(self,
									new_child,
									new_child_type,
									pos);
}

PanedStruct* paned_new(
	AppData *data,
	GtkOrientation orientation)
{
	PanedStruct *self = g_new0(PanedStruct, 1);
	self->child1_type = PANED_CHILD_NULL;
	self->child2_type = PANED_CHILD_NULL;
	self->paned = gtk_paned_new(orientation);
	self->data = data;
	return self;
}

void paned_free(PanedStruct *self)
{
	paned_remove_child(self, 0);
	paned_remove_child(self, 1);
	g_free(self);
}