#ifndef GRAPHICS_H
#define GRApHICS_H

#include "array.h"

void g_init(int wsize_x, int wsize_y);
void g_cleanup(void);
void g_updateDelay(int d);
int g_getArrayLength(void);
void g_setArrayLength(int l);
int g_getWindowX(void);
int g_getWindowY(void);
void g_toggleFullscreen(void);
void g_menu();
int g_update(array_t* a, int selection);

#endif
