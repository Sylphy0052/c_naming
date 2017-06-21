#include <stdio.h>
#include <stdlib.h>

void hexdump(char *desc, unsigned char *bytes, size_t len) {
    int i;
    unsigned char buff[17];
    if(desc != NULL)
        printf("%s:\n", desc);
        if(len == 0) {
    printf("  ZERO LENGTH\n");
    return;
    }

    for (i = 0; i < len; i++) {
        if ((i % 16) == 0) {
            if (i != 0) {
                printf("  %s\n", buff);
            }
            printf("  %04x ", i);
        }
        printf(" %02x", bytes[i]);
        if((bytes[i] < 0x20) || (bytes[i] > 0x7e)) {
            buff[i % 16] = '.';
        } else {
            buff[i % 16] = bytes[i];
        }
        buff[(i % 16) + 1] = '\0';
    }
    while((i % 16) != 0) {
        printf("   ");
        i++;
    }
    printf ("  %s\n", buff);
}


int main() {
    printf("ls\n");
    FILE *fp;
    char *fname = "v6root";
    unsigned char *buf = malloc(sizeof(char) * 0x200000);
    int i, size;

    fp = fopen("v6root", "rb");
    if(fp == NULL) {
        printf( "Can't open this file...\n");
        return -1;
    }

    size = fread(buf, sizeof(unsigned char), 0x200000, fp);
    printf("size : %d\n", size);
    hexdump("hexdump", buf, size);
    printf("\n");


    // while((fread(buf, 0x1fb400, fp) != NULL)) {
    //     hexdump("hexdump", buf, strlen(buf));
    // }

    // size = fread(buf, sizeof(unsigned char), 10000, fp);
    // printf("size : %d\n", size);
    // for(i = 0; i < size; i++) {
    //     if(i % 16 == 0) {
    //         printf("\n");
    //     }
    //     printf("%02X ", buf[i]);
    // }
    // printf("\n");

    fclose(fp);
    return 0;
}
