#include "filework/fileutils.h"
#include <string.h>

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
gboolean fileutils_is_directory_by_fileinfo(GFileInfo *info)
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
	return false;
}

gboolean fileutils_is_cfile_by_fileinfo(GFileInfo *info)
{
	const gchar *name = g_file_info_get_name(info);
	gchar *extension = NULL;
	const gchar *dot = strrchr(name, '.');
	if (dot)
	{
		if ((dot != name) && (*(dot+1) != '\0'))
		{
			extension = g_ascii_strdown(dot+1, -1);
			return !strcmp(extension, "c");
		}
	}
	g_free(extension);
	return false;
}

/*char *get_file_extension(GFileInfo *info, const gchar *ext)
{
	GFileType type = g_file_info_get_file_type(info);
	if (type != G_FILE_TYPE_REGULAR) return g_strdup("");
	const gchar *fixed_name = g_file_info_get_name(info);
	return name;
}*/