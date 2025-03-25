#include "user.h"
extern int __stack_top[];
int syscall(int sysno, int arg0, int arg1, int arg2);

void putchar(char ch) { syscall(SYS_PUTCHAR, ch, 0, 0); }

__attribute__((section(".text.start"))) __attribute__((naked)) void start() {
  __asm__ __volatile__(
      "mv sp, %[stack_top]\n"
      "call main\n"
      "call exit\n" ::[stack_top] "r"(__stack_top));
}

// ecall -> ecall trap -> handle_trap -> sbi_call
int syscall(int sysno, int arg0, int arg1, int arg2) {
  register int a0 __asm__("a0") = arg0;
  register int a1 __asm__("a1") = arg1;
  register int a2 __asm__("a2") = arg2;
  register int a3 __asm__("a3") = sysno;

  __asm__ __volatile__("ecall\n"
                       : "=r"(a0)
                       : "r"(a0), "r"(a1), "r"(a2), "r"(a3)
                       : "memory");

  return a0;
}

int getchar() { return syscall(SYS_GETCHAR, 0, 0, 0); }

__attribute__((noreturn)) void exit() {
  syscall(SYS_EXIT, 0, 0, 0);
  for (;;) {
  }
}