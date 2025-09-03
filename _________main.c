
#include "local_printf.h"
#include <stdio.h>   // system printf for reference

int	main(void)
{
	printf("=== START TEST ===\n");

	// Plain text
	printf("[REF] plain text\n");
	ft_printf("[FT ] plain text\n");


	// // %c
	// printf("[REF] char: %c\n", 'A');
	// ft_printf("[FT ] char: %c\n", 'A');

	// // %s
	// printf("[REF] string: %s\n", "abc");
	// ft_printf("[FT ] string: %s\n", "abc");

	// // %d
	// printf("[REF] decimal: %d\n", -42);
	// ft_printf("[FT ] decimal: %d\n", -42);

	// // %u
	// printf("[REF] unsigned: %u\n", 42u);
	// ft_printf("[FT ] unsigned: %u\n", 42u);

	// // %x / %X
	// printf("[REF] hex lower: %x\n", 255);
	// ft_printf("[FT ] hex lower: %x\n", 255);
	// printf("[REF] hex upper: %X\n", 255);
	// ft_printf("[FT ] hex upper: %X\n", 255);

	// // %p
	// printf("[REF] pointer: %p\n", (void *)0x1234);
	// ft_printf("[FT ] pointer: %p\n", (void *)0x1234);

	// // %%
	// printf("[REF] percent: %%\n");
	// ft_printf("[FT ] percent: %%\n");

	// printf("=== END TEST ===\n");
	return (0);
}
