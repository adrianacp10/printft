#include <unistd.h>

int ft_putchar(char c)
{
    return write(1, &c, 1);
}

int ft_putstr(char *str)
{
    int i;
    i = 0;

    if(str == NULL)
    {
        write(1, "(null)", 6);
        return(6);
    }
    while(str[i])
        write(1, &str[i++], 1);
    return(i);
}

int ft_conversion(va_list vl, const char format)
{
    int char_printed;

    char_printed = 0;

    if(format == 'c')
    {
        char_printed += ft_putchar(va_arg(vl, int));
    }
    else if (format == 's')
    {
        char_printed += ft_putstr(va_arg(vl, char*));
    }
    else if(format == 'p')
    {

    }
    else if(format == 'd')
    {

    }
    else if(format == 'u')
    {

    }
    else if(format == 'x')
    {

    }
    else if(format)
}

int ft_printf(char const *, ...)
{

}
