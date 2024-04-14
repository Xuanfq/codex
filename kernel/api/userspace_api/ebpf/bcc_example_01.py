from bcc import BPF

"""
程序功能为探测 sys_sync ，检测到 sync 时打印出“sys_sync() called”。
sys_sync系统调用被用户空间函数调用，用来将内核文件系统缓冲区的所有数据写入存储介质，
sys_sync系统调用将buffer、inode和super在缓存中的数据写入设备。

此程序作用是检测到 sync 时打印出“sys_sync() called”，运行此程序，打开另一终端，输入sync 回车后`sync-9498    [011] ...21  3644.749783: bpf_trace_printk: sys_sync() called`
"""

prog="""
int kprobe__sys_sync(void *ctx) { 
    bpf_trace_printk("sys_sync() called\\n"); 
    return 0; 
}
"""

print("Tracing sys_sync()... Ctrl-C to end.")

BPF(text=prog).trace_print()

