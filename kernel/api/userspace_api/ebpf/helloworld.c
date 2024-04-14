
// sudo apt-get install bpfcc-tools linux-headers-$(uname -r)

int hello_world(void *ctx)
{
    bpf_trace_printk("Hello, World!");
    return 0;
}

