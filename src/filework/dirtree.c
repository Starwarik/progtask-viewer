// this module represents directory tree
// it is stateful (e.g. no API to create tree)

#include <stdbool.h>
#include "filework/dirtree.h"
#include "filework/filestruct.h"
#include "filework/fileutils.h"

static void build_tree_recursive(GNode *parent, GFile *parent_file, guint depth, guint max_depth)
{
	if ((max_depth > 0) && (depth >= max_depth)) return;
	GError *error = NULL;
	GFileEnumerator *enumerator = g_file_enumerate_children(parent_file,
																													"standard::type,standard::name,standard::display-name,access::*",
																													G_FILE_QUERY_INFO_NONE,
																													NULL,
																													&error);
	if (error)
	{
		g_warning("ENUM ERROR: %s", error->message);
		g_error_free(error);
		return;
	}
	GFileInfo *info;
	while ((info = g_file_enumerator_next_file(enumerator, NULL, &error)) != NULL)
	{
		//g_print(get_file_extension(info));
		GFile *child_file = g_file_enumerator_get_child(enumerator, info);
		FileStruct *child_data = file_struct_new(child_file, info, "");

		GNode *child_node = g_node_new(child_data);
		// REMOVE LATER BLYAT YOU IDIOT DUMB MORON
		FileStruct *shitmazafaka = (FileStruct*)child_node->data;
		g_print(g_file_get_basename(shitmazafaka->file));
		g_print("\n");
		// lalalalalallalalalalalalalalallal end
		g_node_insert(parent, -1, child_node);

		GFileType file_type = g_file_info_get_file_type(child_data->info);
		if (file_type == G_FILE_TYPE_DIRECTORY)
		{
			build_tree_recursive(child_node, child_data->file, depth+1, max_depth);
		}
	}
	g_file_enumerator_close(enumerator, NULL, NULL);
	g_object_unref(enumerator);
}

// creates filetree e.g. snapshot of subtree
// representing the tasks folder
// filepath - path to root dir (must be dir)
// n - level of nesting
GNode *dirtree_create(const gchar *filepath, guint max_depth)
{
	// Create root node
	FileStruct *root = file_struct_new(NULL, NULL, filepath);
	if (!fileutils_is_directory_by_fileinfo(root->info))
	{
		file_struct_free(root);
		g_print("ROOT IS NOT DIRECTORY");
		return NULL;
	}
	// create dirtree
	GNode *dirtree = g_node_new(root);
	// recursively enumerate children e.g. populate dirtree
	build_tree_recursive(dirtree, root->file, 0, max_depth);
	return dirtree;
}

void dirtree_free(GNode *dirtree)
{
	if (!dirtree) return;

	g_node_traverse(dirtree, G_PRE_ORDER, G_TRAVERSE_ALL, -1,
									(GNodeTraverseFunc)file_struct_free, NULL);
	g_node_destroy(dirtree);
}

// tree utility functions

// change active node
void dirtree_change_directory(gint shift);

// find headers in all ancensor dirs
// (to later include them in output)
// out data is GArray, which has auto realloc
GArray dirtree_find_headers(GNode current_node);

// find source files in taskdir
GArray dirtree_find_sources(GNode current_node);

// find exe in taskdir
GFile dirtree_find_exe(GNode current_node);