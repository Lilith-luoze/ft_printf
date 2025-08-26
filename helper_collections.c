# include "ft_printf.h"

int put_c_basic(int c)
{
    
    char ch;
    ch = (char)c; // to make the intent clear
    return write(1, &ch, 1);
}

/*when you don’t need a “real” C-string to keep around (like ft_itoa in libft), but just need to spit out digits, the reversed-buffer trick is the simplest:

loop % and / until number is 0 → naturally gives you digits backward,

count how many you wrote (len),

then print them back-to-front (or fill from the end if you prefer),

handle the '-' separately before printing digits.

👉 quick, easy, no malloc, and perfect for ft_printf.*/

int utoa_dec_rev(unsigned int u, char *buffer)
{
    int i;
    i = 0;
    
    while (u >= 10)
    {
        *buffer = u % 10 + '0';
        buffer ++;
        i++;
        u /= 10;
    }
    *buffer = u % 10 + '0';
    i++;
    return i;
}

// use a stack buffer (local array)
int put_d_basic(int d)
{
    //put decimal number -- 4 bytes -- do it directly


}


