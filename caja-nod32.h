#ifndef CAJA_NOD32_H
#define CAJA_NOD32_H

#include <glib-object.h>

G_BEGIN_DECLS

#define CAJA_TYPE_NOD32  (caja_nod32_get_type ())
#define CAJA_NOD32(o)    (G_TYPE_CHECK_INSTANCE_CAST ((o), CAJA_TYPE_NOD32, CajaNod32))
#define CAJA_IS_NOD32(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), CAJA_TYPE_NOD32))

typedef struct
{
    GObject __parent;
} CajaNod32;

typedef struct
{
	GObjectClass __parent;
} CajaNod32Class;

GType caja_nod32_get_type      (void);
void  caja_nod32_register_type (GTypeModule *module);

G_END_DECLS

#endif /* CAJA_NOD32_H */
