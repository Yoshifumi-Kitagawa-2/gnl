#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int main(void)
{
    char *s;
    int fd;

    fd = open("test.txt", O_RDONLY);
    while(1)
    {
        s = get_next_line(fd);
        if (s == NULL)
                break;
        printf("%s", s);
        free(s);
    }
    system("leaks a.out");
    return(0);
}