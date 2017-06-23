#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "ino.h"
#include "filsys.h"
#include "analyzer.h"

void ls(filsys_t *filsys, inode_t *inode, strage_t *strages) {
    printf("ls\n");
    size_t inode_size = (inode->i_size0 << 8) + inode->i_size1;
    unsigned char *bytes = malloc(sizeof(unsigned char) * inode_size);
    for(size_t i = 0; i < inode_size; i += BLOCK_SIZE) {
        size_t len = (size_t)fmin(inode_size - i, i + BLOCK_SIZE);
        size_t addr = (inode->i_addr[i / BLOCK_SIZE] -2 - filsys->s_isize) * BLOCK_SIZE;
        memcpy(&bytes[i], &strages->contents[addr], len);
    }
    dir_t *dirs = (dir_t *)bytes;
    size_t dir_num = inode_size / sizeof(dir_t);

    printf("print\n");
    for (dir_t *dir = &dirs[0]; dir < &dirs[dir_num]; dir++) {
        printf("%s\n", dir->name);
    }
}
