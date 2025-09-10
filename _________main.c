#include <stdio.h>
#include <unistd.h>
#include "ft_printf.h"

int main(void)
{
    int ret;
    int saved_stdout;

    // Normal case
    ret = ft_printf("hello");
    printf("\nft_printf returned %d (expected 5)\n", ret);

    // Save and close stdout
    saved_stdout = dup(1);
    close(1);

    // This should fail -> ft_printf returns -1
    ret = ft_printf("%%c");

    // Restore stdout *before* using printf again
    dup2(saved_stdout, 1);
    close(saved_stdout);

    printf("ft_printf with closed stdout returned %d (expected -1)\n", ret);

    return 0;
}
