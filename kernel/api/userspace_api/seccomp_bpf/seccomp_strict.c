#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/prctl.h>
#include <linux/seccomp.h>

/**
 * 在严格模式下，进程可用的系统调用只有4个，因为open()也被禁用，所有在进入严格模式前，需要先打开文件
 */

void configure_seccomp()
{
    printf("Configuring seccomp\n");
    prctl(PR_SET_SECCOMP, SECCOMP_MODE_STRICT);
}

int main(int argc, char *argv[])
{
    int infd, outfd;
    ssize_t read_bytes;
    char buffer[1024];

    if (argc < 3)
    {
        printf("Usage:\n\tdup_file <input path> <output_path>\n");
        return -1;
    }

    printf("Opening '%s' for reading\n", argv[1]);
    if ((infd = open(argv[1], O_RDONLY)) > 0)
    {
        configure_seccomp(); /* 配置seccomp */

        /* open() 被禁用，进程会在此终止*/
        printf("Opening '%s' for writing\n", argv[2]);
        if ((outfd = open(argv[2], O_WRONLY | O_CREAT, 0644)) > 0)
        {
            while ((read_bytes = read(infd, &buffer, 1024)) > 0)
                write(outfd, &buffer, (ssize_t)read_bytes);
        }
    }
    close(infd);
    close(outfd);
    return 0;
}