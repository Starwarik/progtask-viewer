#include "fileutils.h"

// safely get file info by a given file
GFileInfo *fileutils_get_file_info(GFile *file)
{
	GFileInfo *info;
	GError *error = NULL;

	info = g_file_query_info(file,
															"standard::type,standard::name,standard::display-name,access::*",
															G_FILE_QUERY_INFO_NONE,
															NULL,
															&error);
	if (error) {
		g_print("Ошибка: %s\n", error->message);
		g_error_free(error);
		return NULL;
	}

	if (info) return info;
	else
	{
		g_print("Почему-то не получилась информация о файле...");
		return NULL;
	}
}

// directoriness by fileinfo
bool fileutils_is_directory_by_fileinfo(GFileInfo *info)
{
	GFileType type = g_file_info_get_file_type(info);
	if (!type)
	{
		g_print("Ошибка: не получен тип файла");
		return false;
	}
	if (type == G_FILE_TYPE_DIRECTORY)
	{
		return true;
	}
	g_print("Почему то не получилось определить папковость файла...");
	return false;
}

/*char *get_file_extension(GFileInfo *info, const gchar *ext)
{
	GFileType type = g_file_info_get_file_type(info);
	if (type != G_FILE_TYPE_REGULAR) return g_strdup("");
	const gchar *fixed_name = g_file_info_get_name(info);
	return name;
}*/