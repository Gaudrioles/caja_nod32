#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <glib-2.0/glib.h>

#include <string.h>
#include <gio/gio.h>
#include <libcaja-extension/caja-column.h>
#include <libcaja-extension/caja-column-provider.h>
#include <libcaja-extension/caja-configurable.h>
#include <libcaja-extension/caja-extension-types.h>
#include <libcaja-extension/caja-file-info.h>
#include <libcaja-extension/caja-info-provider.h>
#include <libcaja-extension/caja-location-widget-provider.h>
#include <libcaja-extension/caja-menu.h>
#include <libcaja-extension/caja-menu-item.h>
#include <libcaja-extension/caja-menu-provider.h>
#include <libcaja-extension/caja-property-page.h>
#include <libcaja-extension/caja-property-page-provider.h>
#include <libcaja-extension/caja-widget-view-provider.h>
#include <locale.h>
#include "caja-nod32.h"


static GObjectClass *parent_class;


static void scan_to_callback (CajaMenuItem *item, gpointer user_data)
{
	GList *files, *scan;
	CajaFileInfo *file;
	GString *cmd;
	
	files = g_object_get_data (G_OBJECT (item), "files");
	file = files->data;

	for (scan = files; scan; scan = scan->next)
	{
		CajaFileInfo *file = scan->data;
		char *uri;

		uri = g_file_get_path(caja_file_info_get_location(file));

		cmd = g_string_new ("sh");
		g_string_append_printf (cmd, " /opt/eset/esets/lib/esets_scan.sh %s", g_shell_quote (uri));
		g_free (uri);
	}
	
	g_spawn_command_line_async (cmd->str, NULL);

	g_string_free (cmd, TRUE);
	
	return;
}

static GList *caja_nod32_get_file_items (CajaMenuProvider *provider, GtkWidget *window, GList *files)
{
	GList    *items = NULL;
	GList    *scan;

    CajaMenuItem *item;

	if (files == NULL)
		return NULL;

	for (scan = files; scan; scan = scan->next) 
    {
		CajaFileInfo *file = CAJA_FILE_INFO (scan->data);
		gchar *name;

		name = caja_file_info_get_name (file);
		
		g_free (name);
	}
    
    item = caja_menu_item_new ("Eset NOD32", "Analyser avec ESET NOD32 Antivirus", "ESET NOD32", "nod32");

	g_signal_connect (item, "activate", G_CALLBACK (scan_to_callback), provider);

	g_object_set_data_full (G_OBJECT (item), "files", caja_file_info_list_copy (files), (GDestroyNotify) caja_file_info_list_free);

	items = g_list_append (items, item);

	return items;
}


static void caja_nod32_menu_provider_iface_init (CajaMenuProviderIface *iface)
{
	iface->get_file_items = caja_nod32_get_file_items;
}


static void caja_nod32_instance_init (CajaNod32 *nod32)
{
}


static void caja_nod32_class_init (CajaNod32Class *class)
{
	parent_class = g_type_class_peek_parent (class);
}


static GType nod32_type = 0;


GType caja_nod32_get_type (void)
{
	return nod32_type;
}


void caja_nod32_register_type (GTypeModule *module)
{
	static const GTypeInfo info = {
		sizeof (CajaNod32Class),
		(GBaseInitFunc) NULL,
		(GBaseFinalizeFunc) NULL,
		(GClassInitFunc) caja_nod32_class_init,
		NULL,
		NULL,
		sizeof (CajaNod32),
		0,
		(GInstanceInitFunc) caja_nod32_instance_init,
	};

	static const GInterfaceInfo menu_provider_iface_info = {
		(GInterfaceInitFunc) caja_nod32_menu_provider_iface_init,
		NULL,
		NULL
	};

	nod32_type = g_type_module_register_type (module,
					       G_TYPE_OBJECT,
					       "CajaNod32",
					       &info, 0);

	g_type_module_add_interface (module,
				     nod32_type,
				     CAJA_TYPE_MENU_PROVIDER,
				     &menu_provider_iface_info);
}
