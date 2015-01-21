#ifndef ARRAY_H
#define ARRAY_H

typedef struct array {
	int* ptr;
	int length;
	int acount;
} array_t;

void a_init(int l);
array_t* a_get_copy(void);
void a_cleanup(void);

#endif
