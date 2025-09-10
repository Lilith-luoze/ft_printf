// #include "ft_printf.h"
// #include <stdio.h>

// int	main(void)
// {
// 	printf("=== START TEST ===\n");

// 	// Test NULL string only with ft_printf
// 	ft_printf("[FT ] NULL str: %s\n\n", (char *)NULL);

// 	// Precision smaller than length
// 	printf("[REF] prec=3 str: %.3s\n", "abcdef");
// 	ft_printf("[FT ] prec=3 str: %.3s\n\n", "abcdef");

// 	// Width smaller than length
// 	printf("[REF] width=3 str: %3s\n", "abcdef");
// 	ft_printf("[FT ] width=3 str: %3s\n\n", "abcdef");

// 	// Width larger than length
// 	printf("[REF] width=10 str: %10s\n", "abc");
// 	ft_printf("[FT ] width=10 str: %10s\n\n", "abc");

// 	// Left align
// 	printf("[REF] minus flag: %-10s!\n", "abc");
// 	ft_printf("[FT ] minus flag: %-10s!\n\n", "abc");

// 	printf("=== END TEST ===\n");
// 	return (0);
// }
