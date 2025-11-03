#include <stdbool.h>
#include <gio/gio.h>

GNode *dirtree_create(const gchar *filepath, guint max_depth);
void dirtree_free(GNode *dirtree);