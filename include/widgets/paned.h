#include <gtk/gtk.h>

typedef struct AppData AppData;

typedef enum PanedChildType
{
	PANED_CHILD_NULL,
	PANED_CHILD_BACK_BUTTON,
	PANED_CHILD_FOLDER_CONTAINER,
	PANED_CHILD_WORK_PANEL,
	PANED_CHILD_TERMINAL,
	PANED_CHILD_NOTEBOOK
} PanedChildType;

typedef struct PanedStruct
{
	GtkWidget *paned;
	gpointer child1;
	PanedChildType child1_type;
	gpointer child2;
	PanedChildType child2_type;
	AppData *data;
} PanedStruct;

PanedStruct* paned_new(
	AppData *data,
	GtkOrientation orientation);

void paned_free(PanedStruct *self);

void paned_change_child(
	PanedStruct *self,
	gpointer new_child,
	PanedChildType new_child_type,
	guint pos);