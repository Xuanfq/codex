from bcc import BPF


"""
本例程通过 sys_clone() 跟踪新进程的创建

- prog = " xxx "此处通过变量声明了一个 C 程序源码，其中xxx是可以换行的 C 程序。
- int hello() { xxx } 声明了一个 C 语言函数，未使用上个例子中 kprobe__ 开头的快捷方式。BPF 程序中的任何 C 函数都需要在一个探针上执行，
    因此我们必须将 pt_reg* ctx 这样的 ctx 变量放在第一个参数。如果需要声明一些不在探针上执行的辅助函数，则需要定义成 static inline 以便编译器内联编译。
    有时候可能需要添加 _always_inline 函数属性。
- b.attach_kprobe(event=b.get_syscall_fnname("clone"), fn_name="hello") 这里建立了一个内核探针，内核系统出现 clone 操作时执行 hello() 这个函数。
    可以多次调用 attch_kprobe() ，这样就可以用 C 语言函数跟踪多个内核函数。
- b.trace_fields() 这里从 trace_pipe 返回一个混合数据，这对于黑客测试很方便，但是实际工具开发中需要使用 BPF_PERF_OUTPUT() 。
"""

# define BPF program
prog = """
int hello(void *ctx) {
    bpf_trace_printk("my bcc program\\n");
    return 0;
}
"""

# load BPF program
bpf = BPF(text=prog)
bpf.attach_kprobe(event=bpf.get_syscall_fnname("clone"), fn_name="hello")

# header
print("%-18s %-16s %-6s %s" % ("TIME(s)", "COMM", "PID", "MESSAGE"))

# format output
while True:
    try:
        (task, pid, cpu, flags, ts, msg) = bpf.trace_fields()
    except ValueError:
        continue
    print("%-18.9f %-16s %-6d %s" % (ts, task, pid, msg))
    
