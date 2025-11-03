#include "filestruct.h"
#include "fileutils.h"

// func to create dirtree node (filestruct)
// using filepath or GFile with GFileInfo
FileStruct *file_struct_new(GFile *file, GFileInfo *info, const char *filepath)
{
	// Create dirtree node
	FileStruct *data = g_new0(FileStruct, 1);
	gboolean file_created = false;
	gboolean info_created = false;
	// if file or info are NULL, first create them
	if (!file && filepath)
	{
		file = g_file_new_for_path(filepath);
		file_created = true;
	}
	if (!info && file)
	{
		// My function :)
		info = fileutils_get_file_info(file);
		info_created = true;
	}
	if (!file || !info)
	{
		g_free(data);
		if (file_created && file) g_object_unref(file);
		if (info_created && info) g_object_unref(info);
		return NULL;
	}
	// initialise node file obj
	data->file = g_object_ref(file);
	// initialise node info
	data->info = g_object_ref(info);
	data->filepath = g_file_get_path(file);

	if (file_created)
		g_object_unref(file);
	if (info_created)
		g_object_unref(info);
	return data;
}

// free node
void file_struct_free(FileStruct *data)
{
	if (data)
	{
		if (data->file) g_object_unref(data->file);
		if (data->info) g_object_unref(data->info);
		g_free(data->filepath);
		g_free(data);
	}
}