#ifndef GRAPHICS_H
#define GRApHICS_H

#include "array.h"

void g_init(int wsize_x, int wsize_y, int d);
void g_cleanup(void);
void g_update(array_t* a, int selection);

#endif
