#include <stdio.h>
#include <sys/prctl.h>
#include <linux/seccomp.h>
#include <linux/filter.h>
#include <stdlib.h>
#include <unistd.h>

// 禁止execve系统调用

int main()
{
    struct sock_filter filter[] = {
        BPF_STMT(BPF_LD + BPF_W + BPF_ABS, 0),        // 将帧的偏移0处，取4个字节数据，也就是系统调用号的值载入累加器
        BPF_JUMP(BPF_JMP + BPF_JEQ, 59, 0, 1),        // 判断系统调用号是否为59，是则顺序执行，否则跳过下一条
        BPF_STMT(BPF_RET + BPF_K, SECCOMP_RET_KILL),  // 返回KILL
        BPF_STMT(BPF_RET + BPF_K, SECCOMP_RET_ALLOW), // 返回ALLOW
    };
    struct sock_fprog prog = {
        .len = (unsigned short)(sizeof(filter) / sizeof(filter[0])), // 规则条数
        .filter = filter,                                            // 结构体数组指针
    };
    prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0); // 设置NO_NEW_PRIVS
    prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &prog);
    write(0, "test\n", 5);
    system("/bin/sh");
    return 0;
}
