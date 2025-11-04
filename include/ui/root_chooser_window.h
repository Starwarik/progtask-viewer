#include <gtk/gtk.h>

// forward declaration of app data
// it is used as func parameter type
typedef struct AppData AppData;

// struct to contain root chooser window widgets
// maybe useless, idk
typedef struct RootChooserStruct
{
	GtkWidget *window; // root chooser window
	GtkWidget *grid; // grid to layout elements
	GtkWidget *label; // label to describe purpose
	GtkWidget *entry; // dirpath entry
	GtkWidget *spin_button; // spin for max_depth
	GtkWidget *browse; // browse to open file dialog
	GtkWidget *from_settings; // button to load settings
	GtkWidget *confirm; // button to confirm settings
} RootChooserStruct;

void root_chooser_free(RootChooserStruct *root_chooser);

// init of window
void root_chooser_window_init(AppData *data);