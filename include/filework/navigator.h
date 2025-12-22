#include <gtk/gtk.h>

typedef struct AppData AppData;
typedef struct FolderButtonContainerStruct FolderButtonContainerStruct;
typedef struct MainWindowStruct MainWindowStruct;

// navigator needs to keep appdata
// because it costs less memory than on buttons
// we are able to use renderer from appdata
// or our own renderer, as it was specified in
// the function declaration
typedef struct NavigatorStruct
{
	GNode *root;
	GNode *current;
	AppData *data;
} NavigatorStruct;

// create navigator and initialise it to root path
NavigatorStruct *navigator_new(
	const gchar *root_path,
	guint max_depth,
	AppData *data
);

// free navigator object
void navigator_free(NavigatorStruct *self);

// is current dir a taskdir? (i.e. contains .c file)
gboolean navigator_is_taskdir(NavigatorStruct *self);

// reads dirignores from the file
gchar* navigator_read_dirignore(gchar *filepath, gsize length);

// discover children of current and return them as GArray
GPtrArray* navigator_discover(NavigatorStruct *self);

// change current to a given subdir
void navigator_to_subdir(NavigatorStruct *self, GNode *subdir);

// change current to its parent
void navigator_to_parent(NavigatorStruct *self);