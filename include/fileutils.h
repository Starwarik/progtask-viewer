#include <gio/gio.h>

GFileInfo *fileutils_get_file_info(GFile *file);
bool fileutils_is_directory_by_fileinfo(GFileInfo *info);
//char *get_file_extension(GFileInfo *info);