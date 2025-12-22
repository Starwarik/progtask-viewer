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

// reads dirignores from the file
gchar* navigator_read_dirignore(gchar *filepath, gsize length)
{
	gchar *dirignore;
	g_file_get_contents(filepath, &dirignore, &length, NULL);
	return dirignore;
}

// applies dirignore to GNode child using its Filestruct data. If matches, returns FALSE
static gboolean navigator_is_in_dirignore(gchar *dirignore, FileStruct *child_data)
{
	gchar **patterns = g_strsplit(dirignore, "\n", -1);
	const gchar *name = g_file_info_get_name(child_data->info);
	g_print("current filename %s\n", name);
	for (gint i = 0; patterns[i] != NULL; i++)
	{
		g_strstrip(patterns[i]);
		g_print("patterns %d is %s\n", i, patterns[i]);
		if (patterns[i][0] == '\0')
		{
			continue;
		}
		g_print("result of g_strcmp0: %d\n", g_strcmp0(patterns[i], name));
		if (g_strcmp0(patterns[i], name) == 0)
		{
			g_print("HERE WE ARE BABY\n");
			g_print("  -> MATCH! Ignoring directory '%s'\n", name);
			g_strfreev(patterns);
			return true;
		}
	}
	g_strfreev(patterns);
	return false;
}

// discover children of current and return them as GPtrArray
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
			if (!navigator_is_in_dirignore(self->data->settings->dirignore, child_data))
			{
				g_ptr_array_add(children, (gpointer)child);
				g_print("after appending %u GNode\n", i);
			}
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