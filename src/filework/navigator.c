#include "filework/navigator.h"
#include "filework/dirtree.h"
#include "filework/filestruct.h"
#include "filework/fileutils.h"
#include "widgets/folder_button_container.h"
#include "widgets/folder_button.h"
#include "app_prefs.h"
// #include "ui/main_window.h"

NavigatorStruct* navigator_new(
	const gchar *root_path,
	guint max_depth,
	AppData *data)
{
	NavigatorStruct *self = g_new0(NavigatorStruct, 1);

	self->root = dirtree_create(root_path, max_depth);
	self->current = self->root;
	self->data = data;
	return self;
}

void navigator_free(NavigatorStruct *self)
{
	if (self)
	{
		dirtree_free(self->root);
		g_free(self);
	}
}

// if at least one is a .c file, then taskdir
gboolean navigator_is_taskdir(NavigatorStruct *self)
{
	guint n_children = g_node_n_children(self->current);
	GNode *child = NULL;
	for (guint i = 0; i < n_children; i++)
	{
		child = g_node_nth_child(self->current, i);
		FileStruct *file_data = (FileStruct*)child->data;
		if (fileutils_is_cfile_by_fileinfo(file_data->info))
			return true;
	}
	return false;
}

// discover children of current and return them as GArray
GPtrArray* navigator_discover(NavigatorStruct *self)
{
	GPtrArray *children = g_ptr_array_new();
	guint n_children = g_node_n_children(self->current);
	GNode *child = NULL;
	FileStruct *child_data = NULL;
	for (guint i = 0; i < n_children; i++)
	{
		child = g_node_nth_child(self->current, i);
		child_data = (FileStruct*)child->data;
		if (fileutils_is_directory_by_fileinfo(child_data->info))
		{
			g_print("before appending %u GNode\n", i);
			g_print("Child %u: GNode* = %p, data = %p\n", i, child, child ? child->data : NULL);
			g_ptr_array_add(children, (gpointer)child);
			g_print("after appending %u GNode\n", i);
		}
	}
	return children;
}

// change current to a given subdir
void navigator_to_subdir(NavigatorStruct *self, GNode *subdir)
{
	self->current = subdir;
}

// change current to its parent
void navigator_to_parent(NavigatorStruct *self)
{
	if (self->current != self->root)
		self->current = self->current->parent;
}