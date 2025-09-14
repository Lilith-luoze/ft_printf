// #define TEST_PRINTF(format, ...) \
//     do { \
//         fflush(stdout); fflush(stderr); \
//         int my = ft_printf(format, ##__VA_ARGS__); \
//         fflush(stdout); fflush(stderr); \
//         int pf = printf(format, ##__VA_ARGS__); \
//         fflush(stdout); fflush(stderr); \
//         if (my != pf) { \
//             printf("\033[31m[RET MISMATCH] My: %d, pf: %d  at %s:%d\033[0m\n\n", \
//                    my, pf, __FILE__, __LINE__); \
//         } else { \
//             printf("\033[32m[RET OK] My: %d, pf: %d\033[0m\n\n", my, pf); \
//         } \
//     } while (0)

// #include <stdio.h>
// #include "ft_printf.h"
// #include <unistd.h>
// #include <fcntl.h>

// #include <stdio.h>
// #include "ft_printf.h"
// # include <limits.h>


// int main(void)
// {
//     TEST_PRINTF("%.4u\n", 42);
//     TEST_PRINTF("%.4u\n", 424242);
//     TEST_PRINTF("%15.4u\n", 42);
//     TEST_PRINTF("%15.4u\n", 424242);
//     TEST_PRINTF("%8.4u\n", 424242424);
//     TEST_PRINTF("%4.15u\n", 42);
//     TEST_PRINTF("%4.15u\n", 424242);
//     TEST_PRINTF("%4.8u\n", 424242424);
//     TEST_PRINTF("%.u, %.0u\n", 0, 0);
//     TEST_PRINTF("%u\n", -42);
//     TEST_PRINTF("%u\n", UINT_MAX + 1u);
//     TEST_PRINTF("%-52c%---163c%0%%050.35u\n", -60, -30, 3953001178u);
//     // precision = 0, value = 0 → prints ""
//     TEST_PRINTF("%.0u\n", 0);

//     // precision = 0, value = 0, width = 5 → prints "     "
//     TEST_PRINTF("%5.0u\n", 0);

//     // precision = .u is also treated like .0u → prints ""
//     TEST_PRINTF("%.u\n", 0);

//     // combination with other specifiers
//     TEST_PRINTF("[%10.u]\n", 0);   // should be "[          ]"
//     TEST_PRINTF("[%.0u, %.0u]\n", 0, 42); // "[, 42]"

//     int a = ft_printf("%\n");
//     TEST_PRINTF("a-------%d\n", a);
//     int b = printf("%\n");
//     TEST_PRINTF("b-------%d\n", b);
//     TEST_PRINTF("%%%%%\n", 0);
//     TEST_PRINTF("%5.0d\n", 0);
//     TEST_PRINTF("%.5d\n", -42);
//     TEST_PRINTF("%+.5d\n", 42);
//     TEST_PRINTF("%08-10d", 42);
//     printf("=== Additional Edge Case Tests ===\n\n");

//     TEST_PRINTF("X%.sY\n", "hello");
//     TEST_PRINTF("X%.1sY\n", "hello");
//     TEST_PRINTF("X%.dY\n", 42);




//     printf("=== Basic Tests for '%%' and 'p' Specifiers ===\n\n");
//     int ret1, ret2;

//     TEST_PRINTF("%15p\n", (void*)NULL);
//     TEST_PRINTF("%-15p\n", (void*)NULL);

//     TEST_PRINTF("%%\n");
//     TEST_PRINTF("%%c\n");

//     void* p = NULL;
//     TEST_PRINTF("ft: [%p]\n", p);

//     int x = 42;
//     TEST_PRINTF("ft: [%p]\n", &x);

//     printf("=== NULL string tests ===\n\n");
//     TEST_PRINTF("%-s\n", (char*)NULL);
//     TEST_PRINTF("%23s\n", (char*)NULL);
//     TEST_PRINTF("%s\n", (char*)NULL);

//     TEST_PRINTF("%\n");
//     TEST_PRINTF("abc%\n");
//     TEST_PRINTF("%05d\n", 1);
//     TEST_PRINTF("%-05d\n", 1);
//     TEST_PRINTF("%5-8d\n", 1);
//     TEST_PRINTF("%.s\n", "hello");
//     TEST_PRINTF("%10.0d\n", 0);
//     TEST_PRINTF("%s\n", NULL);
//     TEST_PRINTF("%15s\n", NULL);
//     TEST_PRINTF("%p\n", NULL);
//     TEST_PRINTF("%15p\n", NULL);
//     TEST_PRINTF("%#x\n", 0);
//     TEST_PRINTF("%#x\n", 1);
//     TEST_PRINTF("%-+10d\n", 42);
//     TEST_PRINTF("%+08d\n", 42);



//     return 0;

// }