#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "src/read_bynary.h"
#include "src/analyzer.h"
#include "src/filsys.h"
#include "src/ino.h"
#include "src/command.h"

int main() {
    unsigned char *datas;
    int data_length;
    data_length = read_bynary("v6root", &datas);
    if(data_length < 0) {
        printf("Read error...\n");
    }
    filsys_t *filsys;
    inode_t *inodes;
    strage_t *strages;
    analyze(datas, data_length, &inodes, &filsys, &strages);

    char input[10];
    inode_t *inode = &inodes[0];
    while(1) {
        printf(">> ");
        scanf("%s", input);
        // ls
        if(strcmp(input, "ls") == 0) {
            ls(filsys, inode, strages);
        }
    }

    return 0;
}
