#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hexdump.h"
#include "ino.h"
#include "filsys.h"
#include "analyzer.h"

size_t pc;

char get_char(unsigned char *datas) {
    char ret;
    ret = datas[0];
    pc ++;
    return ret;
}

uint8_t get_uint8(unsigned char *datas) {
    uint8_t ret;
    ret = (uint8_t)datas[0];
    pc += 1;
    return ret;
}

uint16_t get_uint16(unsigned char *datas) {
    uint16_t ret;
    ret = (uint16_t)datas[1];
    for(int i = 0; i >= 0; i--) {
        ret <<= BYTE_SIZE;
        ret += (uint16_t)datas[i];
    }
    pc += 2;
    return ret;
}

unsigned char *get_block(unsigned char *datas) {
    unsigned char *ret;
    ret = malloc(sizeof(unsigned char) * BLOCK_SIZE);
    // for(int i = 0; i >= 0; i--) {
    //     ret <<= BYTE_SIZE;
    //     ret += (uint16_t)datas[i];
    // }
    memcpy(ret, datas, BLOCK_SIZE);
    pc += BLOCK_SIZE;
    return ret;
}

int get_int(unsigned char *datas) {
    int ret;
    ret = (int)datas[3];
    for(int i = 2; i >= 0; i--) {
        ret <<= BYTE_SIZE;
        ret += (int)datas[i];
    }
    pc += 4;
    return ret;
}

// unsigned char *get_strage_by_block() {
//     printf("get_strage_by_block\n");
// }

void analyze_strage(unsigned char *datas, strage_t **strages_, size_t strage_size) {
    strage_t *strages = *strages_;
    for(int i = 0; i < strage_size; i++) {
        strages[i].contents = get_block(&datas[pc]);
        // hexdump("analyze_strage", &strages[i].contents[0], BLOCK_SIZE);
        // printf("%d : %s\n", i, strages[i].contents);
    }
}

void print_inode(inode_t *inode) {
    printf("i_mode : %o\n", inode->i_mode);
    printf("i_nlink : %c\n", inode->i_nlink);
    printf("i_uid : %c\n", inode->i_uid);
    printf("i_gid : %c\n", inode->i_gid);
    printf("i_size0 : %02x\n", inode->i_size0);
    printf("i_size1 : %04x\n", inode->i_size1);
    for(int i = 0; i < 8; i++) {
        printf("i_addr[%d] : %04x\n", i, inode->i_addr[i]);
    }
    for(int i = 0; i < 2; i++) {
        printf("i_atime[%d] : %04x\n", i, inode->i_atime[i]);
    }
    for(int i = 0; i < 2; i++) {
        printf("i_mtime[%d] : %04x\n", i, inode->i_mtime[i]);
    }
}

void analyze_inode(int ino, unsigned char *datas, inode_t *inode) {
    size_t pointer = pc;
    inode->i_mode = get_uint16(&datas[pc - pointer]);
    inode->i_nlink = get_uint8(&datas[pc - pointer]);
    inode->i_uid = get_uint8(&datas[pc - pointer]);
    inode->i_gid = get_uint8(&datas[pc - pointer]);
    inode->i_size0 = get_uint8(&datas[pc - pointer]);
    inode->i_size1 = get_uint16(&datas[pc - pointer]);
    for(int i = 0; i < 8; i++) {
        inode->i_addr[i] = get_uint16(&datas[pc - pointer]);
    }
    for(int i = 0; i < 2; i++) {
        inode->i_atime[i] = get_uint16(&datas[pc - pointer]);
    }
    for(int i = 0; i < 2; i++) {
        inode->i_mtime[i] = get_uint16(&datas[pc - pointer]);
    }
    if(inode->i_mode != 0) {
        // hexdump_inode("inode", ino, &datas[0], INODE_SIZE);
        // print_inode(inode);
        // printf("len : %lu\n", pc - pointer);
    }
}

void print_filsys(filsys_t *filsys) {
    printf("s_isize : %04x\n", filsys->s_isize);
    printf("s_fsize : %04x\n", filsys->s_fsize);
    printf("s_nfree : %04x\n", filsys->s_nfree);
    for(int i = 0; i < 100; i++) {
        printf("s_free[%d] : %04x\n", i, filsys->s_free[i]);
    }
    printf("s_ninode : %04x\n", filsys->s_ninode);
    for(int i = 0; i < 100; i++) {
        printf("s_inode[%d] : %04x\n", i, filsys->s_inode[i]);
    }
    printf("s_flock : %c\n", filsys->s_flock);
    printf("s_ilock : %c\n", filsys->s_ilock);
    printf("s_fmod : %c\n", filsys->s_fmod);
    printf("s_ronly : %c\n", filsys->s_ronly);
    for(int i = 0; i < 2; i++) {
        printf("s_time[%x] : %04x\n", i, filsys->s_time[i]);
    }
    for(int i = 0; i < 48; i++) {
        printf("pad[%d] : %04x\n", i, filsys->pad[i]);
    }
}

filsys_t *analyze_super_block(unsigned char *datas, filsys_t **filsys_) {
    filsys_t *filsys = *filsys_ ;
    size_t pointer = pc;
    // hexdump("---Super block---", &datas[0], BLOCK_SIZE);
    filsys->s_isize = get_uint16(&datas[pc - pointer]);
    filsys->s_fsize = get_uint16(&datas[pc - pointer]);
    filsys->s_nfree = get_uint16(&datas[pc - pointer]);
    for(int i = 0; i < 100; i++) {
        filsys->s_free[i] = get_uint16(&datas[pc - pointer]);
    }
    filsys->s_ninode = get_uint16(&datas[pc - pointer]);
    for(int i = 0; i < 100; i++) {
        filsys->s_inode[i] = get_uint16(&datas[pc - pointer]);
    }
    filsys->s_flock = get_uint8(&datas[pc - pointer]);
    filsys->s_ilock = get_uint8(&datas[pc - pointer]);
    filsys->s_fmod = get_uint8(&datas[pc - pointer]);
    filsys->s_ronly = get_uint8(&datas[pc - pointer]);
    for(int i = 0; i < 2; i++) {
        filsys->s_time[i] = get_uint16(&datas[pc - pointer]);
    }
    for(int i = 0; i < 48; i++) { //50にすると516byteになる.大雑把に定義されているらしい
        filsys->pad[i] = get_uint16(&datas[pc - pointer]);
    }
    // print_filsys(filsys);
    // printf("len : %lu\n", pc - pointer);
    return filsys;
}

void analyze_startup_area(unsigned char *datas) {
    // hexdump("Start-up area", &datas[0], BLOCK_SIZE);
    pc += BLOCK_SIZE;
}

void analyze(unsigned char *datas, int data_length, inode_t **inodes_, filsys_t **filsys_, strage_t **strages_) {
    pc = 0;
    // printf("Start analyze...\nsize : %d\n", data_length);
    // hexdump("hexdump", datas, data_length);
    analyze_startup_area(&datas[pc]);
    filsys_t *filsys = *filsys_ = malloc(sizeof(filsys_t));
    analyze_super_block(&datas[pc], &filsys);
    size_t max = filsys->s_isize * 16;
    // printf("inode max size : %zu\n", max);
    inode_t *inodes = *inodes_ = malloc(sizeof(inode_t) * max);
    for(size_t i = 0; i < max; i++) {
        analyze_inode(i, &datas[pc], &inodes[i]);
    }
    // hexdump("strage", &datas[pc], filsys->s_fsize);
    size_t strage_size;
    if((filsys->s_fsize % BLOCK_SIZE) == 0) {
        strage_size = filsys->s_fsize / BLOCK_SIZE;
    } else {
        strage_size = filsys->s_fsize / BLOCK_SIZE + 1;
    }
    // printf("%d / %d = strage_size : %zu\n", filsys->s_fsize, BLOCK_SIZE, strage_size);
    strage_t *strages = *strages_ = malloc(sizeof(strage_t) * strage_size);
    analyze_strage(&datas[pc], &strages, strage_size);

}
