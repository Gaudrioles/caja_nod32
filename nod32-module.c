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

#include "caja-nod32.h"

void caja_module_initialize (GTypeModule*module)
{
	caja_nod32_register_type (module);
}


void caja_module_shutdown (void)
{

}


void caja_module_list_types (const GType **types, int *num_types)
{
        static GType type_list[1];

	type_list[0] = CAJA_TYPE_NOD32;
	*types = type_list;
	*num_types = 1;
}