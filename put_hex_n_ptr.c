// it's just base conversion
# include "local_printf.h"

int utoa_hex_rev(unsigned long u, char *buffer, int upper)
{
    int slen;
    char *hex;
    if (upper)
        hex = "0123456789ABCDEF";
    else 
        hex = "0123456789abcdef";
    slen = 0;
    while(u >= 16)
    {
        *buffer = hex[u % 16]; // a more standard way to index into a lookup string
        buffer ++;
        slen++;
        u /= 16;
    }
    *buffer = hex[u % 16];
    slen++;

    return slen;
}

int put_p_basic(void *p)
{
    unsigned long addr; 
    int count;
    char buffer[16];
    int slen;

    if (p == NULL)
        return(write(1, NULL_PTR , sizeof(NULL_PTR) - 1));
    count = 0;
    addr = (unsigned long) p;
    slen = utoa_hex_rev(addr, buffer, 0);
    count += write(1, "0x", 2);
    count += put_buffer_rev(buffer, slen);
    return (count);
}

int put_hex_basic(unsigned int h, int upper)
{
	int slen;        // string length in buffer
	char buffer[8]; // max 32 bit for numbers (2^32). binary to hex : 32 / 4 = 8. 8 pos is needed.
	slen = utoa_hex_rev(h, buffer, upper);
	return (put_buffer_rev(buffer, slen));
}