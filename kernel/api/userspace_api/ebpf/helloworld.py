from bcc import BPF

# sudo apt-get install bpfcc-tools linux-headers-$(uname -r)

"""
这段代码是在 python 中内嵌 C 语言程序的，请注意六点：

- text='...' 这里定义了一个内联的、C 语言写的 BPF 程序。
- kprobe__sys_clone() 这是一个通过内核探针(kprobe)进行内核动态跟踪的快捷方式。如果一个 C 函数名开头为 kprobe__ ，则后面的部分实际为设备的内核函数名，这里是 sys_clone() 。
- void *ctx 这里的 ctx 实际上有一些参数，不过这里我们用不到，暂时转为 void * 。
- bpf_trace_printk()这是一个简单的内核工具，用于 printf() 到 trace_pipe(译者注：可以理解为 BPF C 代码中的 printf())。它一般来快速调试一些东西，不过有一些限制：最多有三个参数，一个%s ，
  并且 trace_pipe 是全局共享的，所以会导致并发程序的输出冲突，因而 BPF_PERF_OUTPUT() 是一个更棒的方案，我们后面会提到。
- return 0 这是一个必须的部分。
- trace_print() 一个 bcc 实例会通过这个读取 trace_pipe 并打印出来。
"""

prog="""
int kprobe__sys_clone(void *ctx) { 
    bpf_trace_printk("Hello, World!\\n"); 
    return 0; 
}
"""

BPF(text=prog).trace_print()

