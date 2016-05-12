#ifndef FILE_H
#define FILE_H
#include "kernel/threads.h"


typedef struct file {
	char *path;
	unsigned int id;
} file;

#endif
