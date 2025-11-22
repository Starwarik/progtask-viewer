#include "filework/filestruct.h"
#include "filework/fileutils.h"

// func to create dirtree node (filestruct)
// using filepath or GFile with GFileInfo
FileStruct *file_struct_new(GFile *file, GFileInfo *info, const char *filepath)
{
	FileStruct *data = g_new0(FileStruct, 1);

	if (!file && filepath) {
		file = g_file_new_for_path(filepath);
	}

	if (!info && file) {
		info = fileutils_get_file_info(file);
	}

	if (!file || !info) {
		g_free(data);
		if (file && !filepath) g_object_unref(file);
		return NULL;
	}

	// Store references - we take ownership of these objects
	data->file = file;
	data->info = info;
	data->filepath = g_file_get_path(file);
	
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