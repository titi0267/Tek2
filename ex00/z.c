#include <stdio.h>

int error_handling(int ac, char **av)
{
    if (ac == 0)
        return (time(NULL));
}

int main(int ac, char **av)
{
    return (error_handling(ac,av));
    return (0);
}