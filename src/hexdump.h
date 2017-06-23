#ifndef HEXDUMP_H
#define HEXDUMP_H

void hexdump(char *desc, unsigned char *bytes, size_t len);
void hexdump_inode(char *desc, int ino, unsigned char *bytes, size_t len);

#endif
