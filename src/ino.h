#ifndef INO_H
#define INO_H

#include <stdint.h>

// modes
#define IALLOC 0100000
#define IFMT 060000
#define IFDIR 040000
#define IFCHAR 020000
#define IFBLK 060000
#define ILARG 010000
#define ISUID 04000
#define ISGID 02000
#define ISVTX 01000
#define IREAD 04000
#define IWRITE 02000
#define IEXEC 0100

typedef struct inode {
    uint16_t i_mode; // 状態，制御情報．下位9bitはパーミッションを表す
    uint8_t i_nlink; // ディレクトリからの参照数
    uint8_t i_uid; // ユーザID
    uint8_t i_gid; // グループID
    uint8_t i_size0; // ファイルサイズの上位8bit
    uint16_t i_size1; // ファイルサイズの下位16bit
    uint16_t i_addr[8]; // 使用しているストレージ領域のブロック番号
    int16_t i_atime[2]; // 参照時刻
    int16_t i_mtime[2]; // 更新時刻
} inode_t;

#endif
