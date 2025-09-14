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


//     /* ========================================================= */
//     printf("\n================ MANDATORY PART ================\n");

//     printf("\n=== Percent Literal (%%) ===\n");
//     TEST_PRINTF("%%\n");
//     TEST_PRINTF("abc%%def\n");

//     printf("\n=== Character (%c) ===\n");
//     TEST_PRINTF("%c\n", 'A');
//     TEST_PRINTF("%c%c%c\n", '4', '2', '!');

//     printf("\n=== String (%s) ===\n");
//     TEST_PRINTF("%s\n", "hello");
//     TEST_PRINTF("%s\n", "");
//     TEST_PRINTF("%s\n", NULL);

//     printf("\n=== Pointer (%p) ===\n");
//     x = 42;
//     TEST_PRINTF("%p\n", (void*)0);
//     TEST_PRINTF("%p\n", &x);

//     printf("\n=== Signed decimal (%d / %i) ===\n");
//     TEST_PRINTF("%d\n", 42);
//     TEST_PRINTF("%i\n", -42);
//     TEST_PRINTF("%d\n", 0);
//     TEST_PRINTF("%d\n", -2147483648);

//     printf("\n=== Unsigned (%u) ===\n");
//     TEST_PRINTF("%u\n", 42u);
//     TEST_PRINTF("%u\n", 3000000000u);
//     TEST_PRINTF("%u\n", 0u);

//     printf("\n=== Hexadecimal (%x / %X) ===\n");
//     TEST_PRINTF("%x\n", 255);
//     TEST_PRINTF("%X\n", 255);
//     TEST_PRINTF("%x\n", 0);
//     TEST_PRINTF("%X\n", 0);
//     /* ========================================================= */
//     printf("\n================ BONUS PART ================\n");

//     printf("\n=== Width and Left Align (-) ===\n");
//     TEST_PRINTF("%5d|\n", 42);
//     TEST_PRINTF("%-5d|\n", 42);
//     TEST_PRINTF("%10s|\n", "hi");
//     TEST_PRINTF("%-10s|\n", "hi");

//     printf("\n=== Zero Padding (0) ===\n");
//     TEST_PRINTF("%05d\n", 42);
//     TEST_PRINTF("%05i\n", -42);
//     TEST_PRINTF("%010u\n", 1234u);
//     TEST_PRINTF("%08x\n", 255);

//     printf("\n=== Precision (.) ===\n");
//     TEST_PRINTF("%.5d\n", 42);
//     TEST_PRINTF("%.0d\n", 0);   // suppresses 0
//     TEST_PRINTF("%.3s\n", "truncate");
//     TEST_PRINTF("%.0s\n", "hello"); // empty string
//     TEST_PRINTF("%10.5d\n", 123);

//     printf("\n=== Plus (+) and Space ( ) ===\n");
//     TEST_PRINTF("%+d\n", 42);
//     TEST_PRINTF("%+d\n", -42);
//     TEST_PRINTF("% d\n", 42);
//     TEST_PRINTF("% d\n", -42);
//     TEST_PRINTF("%+ d\n", 42);  // plus overrides space

//     printf("\n=== Alternate Form (#) ===\n");
//     TEST_PRINTF("%#x\n", 255);
//     TEST_PRINTF("%#X\n", 255);
//     TEST_PRINTF("%#x\n", 0);   // no prefix for zero
//     TEST_PRINTF("%#X\n", 0);

//     printf("\n=== Combined Flags ===\n");
//     TEST_PRINTF("%-05d\n", 42);    // minus cancels zero
//     TEST_PRINTF("%+010d\n", 42);   // plus + zero
//     TEST_PRINTF("%-#10x\n", 255);  // left align + alt form
//     TEST_PRINTF("%#08x\n", 0);     // alt form suppressed on zero
//     TEST_PRINTF("%- 10d\n", 42);   // minus + space



//     // printf("\n=== 8. Odd / Undefined Sequences (glibc defined behavior) ===\n");
//     // TEST_PRINTF("%0. 12.6s\n", "hell");     // NO NEED to debug
//     // TEST_PRINTF("%q\n", 42); // unknown specifier    // NO NEED to debug
//     // TEST_PRINTF("%hd\n", (short)30000);
//     // TEST_PRINTF("%q\n", 42);
//     // TEST_PRINTF("%qd\n", 42);
//     // TEST_PRINTF("%qad\n", 42);
//     // TEST_PRINTF("%. 12.6s\n", "hell");
//     // TEST_PRINTF("%. d\n", 42);




//     // Test for failed cases 
//     printf("=== cases that failures on write ===\n\n");

//     // --- Test 1: '%' specifier ---

//     int saved_stdout;

//     // Disable buffering for libc printf
//     setvbuf(stdout, NULL, _IONBF, 0);

//     // --- Test 1: '%' specifier ---
//     saved_stdout = dup(1);
//     close(1);

//     ret1 = ft_printf("%%");
//     ret2 = printf("%%");

//     dup2(saved_stdout, 1);
//     close(saved_stdout);

//     printf("My: %d\n", ret1);
//     printf("pf: %d\n", ret2);

//     // --- Test 2: '%p' with NULL ---
//     saved_stdout = dup(1);
//     close(1);

//     ret1 = ft_printf("%p", NULL);
//     ret2 = printf("%p", NULL);

//     dup2(saved_stdout, 1);
//     close(saved_stdout);

//     printf("My: %d\n", ret1);
//     printf("pf: %d\n", ret2);

//     return 0;

// }