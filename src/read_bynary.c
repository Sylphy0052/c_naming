#include <stdio.h>
#include <stdlib.h>

#include <hexdump.h>

int read_bynary(char *fname, unsigned char **datas_) {
    FILE *fp;
    unsigned char *buf = *datas_ = malloc(sizeof(char) * 0x200000);
    int i, size;

    fp = fopen("v6root", "rb");
    if(fp == NULL) {
        printf( "Can't open this file...\n");
        return -1;
    }

    size = fread(buf, sizeof(unsigned char), 0x200000, fp);
    // hexdump("hexdump", buf, size);
    fclose(fp);
    return size;
}
