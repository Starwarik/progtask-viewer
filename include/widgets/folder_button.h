// good approach is to create a button in the container,
// not in the navigator, but second variant is more suitable,
// so i need to apologise in front of you, dear watcher :)

#include <gtk/gtk.h>

typedef struct AppData AppData;
typedef struct MainWindowStruct MainWindowStruct;

typedef struct FolderButtonStruct
{
	GtkWidget *button; // to remap on_folder_click
	GtkWidget *label; // to change folder's label
	GNode *folder; // to represent actual folder
	AppData *data;
} FolderButtonStruct;

FolderButtonStruct* folder_button_new(
	GNode *folder,
	AppData *data);

void folder_button_free(FolderButtonStruct *data);