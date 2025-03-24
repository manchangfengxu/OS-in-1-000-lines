#include "user.h"

extern int __stack_top[];

__attribute__((noreturn)) void exit() {
  for (;;) {
  }
}

void putchar(char ch) {
    
}

__attribute__((section(".text.start"))) __attribute__((naked)) void start() {
  __asm__ __volatile__(
      "mv sp, %[stack_top]\n"
      "call main\n"
      "call exit\n" ::[stack_top] "r"(__stack_top));
}

