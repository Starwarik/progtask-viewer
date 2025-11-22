#include <gtk/gtk.h>

typedef struct FolderButtonStruct FolderButtonStruct;
typedef struct AppData AppData;

typedef struct FolderButtonContainerStruct
{
	GtkWidget *scroll;
	GtkWidget *container;
	GPtrArray *button_array;
} FolderButtonContainerStruct;

FolderButtonContainerStruct* folder_button_container_new();

void folder_button_container_free(
	FolderButtonContainerStruct *self
);

// initialise nodes, that are inside the array
void folder_button_container_arrinit(
	FolderButtonContainerStruct *self
);

void folder_button_container_pop(
	FolderButtonContainerStruct *self
);

void folder_button_container_append(
	FolderButtonContainerStruct *self,
	FolderButtonStruct *button_data
);

void folder_button_container_refresh(
	FolderButtonContainerStruct *self,
	FolderButtonStruct *button_data,
	guint index_
);

void folder_button_container_render(
	AppData *data,
	FolderButtonContainerStruct *container);