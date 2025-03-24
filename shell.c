#include "user.h"

extern char _binary_shell_bin_start[];
extern char _binary_shell_bin_size[];

void main() {
    *((volatile int *) 0x80200000) = 0x1234; // 新增!
    for (;;);
}