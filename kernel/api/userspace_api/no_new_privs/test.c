#include <errno.h>
#include <sys/prctl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{

    for (int i = 0; i < argc; i++)
    {
        printf("%d\t: %s \n", i, argv[i]);
    }

    if (argc < 2)
    {
        printf("%s argument\n", argv[0]);
        exit(-1);
    }

    if (argc == 3)
    {
        if (prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0))
        {
            perror("Error\t: prctl(NO_NEW_PRIVS)\n");
            return 1;
        }else{
            printf("Success\t: prctl(NO_NEW_PRIVS)\n");
        }
    }

    return system(argv[1]);
}
