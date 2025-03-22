#pragma once
#define PANIC(fmt, ...)                                                   \
  do {                                                                    \
    printf("PANIC: %s:%d: " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__); \
    while (1) {                                                           \
    }                                                                     \
  } while (0)

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef uint32_t size_t;

struct sbiret {
  long error;
  long value;
};

#include "common.h"

struct trap_frame {
  uint32_t ra;
  uint32_t gp;
  uint32_t tp;
  uint32_t t0;
  uint32_t t1;
  uint32_t t2;
  uint32_t t3;
  uint32_t t4;
  uint32_t t5;
  uint32_t t6;
  uint32_t a0;
  uint32_t a1;
  uint32_t a2;
  uint32_t a3;
  uint32_t a4;
  uint32_t a5;
  uint32_t a6;
  uint32_t a7;
  uint32_t s0;
  uint32_t s1;
  uint32_t s2;
  uint32_t s3;
  uint32_t s4;
  uint32_t s5;
  uint32_t s6;
  uint32_t s7;
  uint32_t s8;
  uint32_t s9;
  uint32_t s10;
  uint32_t s11;
  uint32_t sp;
} __attribute__((packed));

#define READ_CSR(reg)                                     \
  ({                                                      \
    unsigned long __tmp;                                  \
    __asm__ __volatile__("csrr %0, " #reg : "=r"(__tmp)); \
    __tmp;                                                \
  })

#define WRITE_CSR(reg, value)                               \
  do {                                                      \
    uint32_t __tmp = (value);                               \
    __asm__ __volatile__("csrw " #reg ", %0" ::"r"(__tmp)); \
  } while (0)

#define SATP_SV32 (1u << 31)  // 100....
#define PAGE_V (1 << 0)       // "Valid" 位（表项已启用）
#define PAGE_R (1 << 1)       // 可读
#define PAGE_W (1 << 2)       // 可写
#define PAGE_X (1 << 3)       // 可执行
#define PAGE_U (1 << 4)       // 用户（用户模式可访问）

#define PROCS_MAX 8  // 最大进程数量

#define PROC_UNUSED 0    // 未使用的进程控制结构
#define PROC_RUNNABLE 1  // 可运行的进程

struct process {
  int pid;               // 进程 ID
  int state;             // 进程状态: PROC_UNUSED 或 PROC_RUNNABLE
  vaddr_t sp;            // 栈指针
  uint32_t *page_table;  // 页表
  uint8_t stack[8192];   // 内核栈
};