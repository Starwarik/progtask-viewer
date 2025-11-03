#include <gio/gio.h>

// struct to keep information about file
// actually i'm not sure, but i hope it will work
// is file object really required?
typedef struct FileStruct
{
	GFile *file;
	GFileInfo *info;
	gchar *filepath;
} FileStruct;

FileStruct *file_struct_new(GFile *file, GFileInfo *info, const char *filepath);
void file_struct_free(FileStruct *data);