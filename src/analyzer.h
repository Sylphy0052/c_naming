#ifndef ANALYZER_H
#define ANALYZER_H

#include <stdint.h>

#include "ino.h"
#include "filsys.h"

#define BLOCK_SIZE 512
#define INODE_SIZE 32
#define BYTE_SIZE 8

typedef struct dir {
  uint16_t ino;
  char name[14];
} dir_t;

typedef struct strage {
    unsigned char *contents;
} strage_t;

void print_inode(inode_t *inodes);
void print_filsys(filsys_t *filsys);
void analyze(unsigned char *datas, int data_length, inode_t **inodes, filsys_t **filsys, strage_t **strages);

#endif
