#ifndef FILSYS_H
#define FILSYS_H

typedef struct filsys {
    uint16_t s_isize; // inode領域のブロック数
    uint16_t s_fsize; // ストレージ領域のブロック数
    uint16_t s_nfree; // ストレージフリーリスト中のブロック番号数
    uint16_t s_free[100]; // ストレージフリーリスト
    uint16_t s_ninode; // inodeフリーリスト中のinode番号数
    uint16_t s_inode[100]; // inodeフリーリスト
    uint8_t s_flock; // ストレージフリーリストのロック
    uint8_t s_ilock; // inodeフリーリストのロック
    uint8_t s_fmod; // 更新フラグ
    uint8_t s_ronly; // このブロックデバイスは読み取り専用
    uint16_t s_time[2]; // 現在時刻，もしくは，最後に更新された時刻
    uint16_t pad[48]; // パディング 50にすると516byteになる．大雑把に定義されているらしい？
} filsys_t;

#endif
