#include <unistd.h>
#include <stdarg.h>
// Función para imprimir un solo character
int ft_putchar(char c)
{
    return write(1, &c, 1);
}

// Función para imprimir una string
int ft_putstr(char *str)
{
    int count = 0;
    if (!str)
        str = "(null)";
    while (*str)
    {
        count += ft_putchar(*str);
        str++;
    }
    return count;
}

// Función para imprimir un número en base 10
int ft_putnbr(int n)
{
    int count = 0;
    if (n == -2147483648)
        return ft_putstr("-2147483648");
    if (n < 0)
    {
        count += ft_putchar('-');
        n = -n;
    }
    if (n > 9)
        count += ft_putnbr(n / 10);
    count += ft_putchar(n % 10 + '0');
    return count;
}

// int ft_conversion(va_list vl, const char format)
// {
//     int char_printed;

//     char_printed = 0;

//     if(format == 'c')
//     {
//         char_printed += ft_putchar(va_arg(vl, int));
//     }
//     else if (format == 's')
//     {
//         char_printed += ft_putstr(va_arg(vl, char*));
//     }
//     else if(format == 'p')
//     {

//     }
//     else if(format == 'd')
//     {

//     }
//     else if(format == 'u')
//     {

//     }
//     else if(format == 'x')
//     {

//     }
//     else if(format)
// }

int ft_printf(const char *format, ...)
{
    va_list args;
    int count;

    count = 0;

    va_start(args, format); //inicializa args permitiendo extraer los valores pasados después de format
    while(*format)
    {
        if(*format == '%')
        {
            format++;
            if(*format == 'c')
            {
                count+= ft_putchar(va_arg(args, int)); //extrae los argumentos
            }
            else if (*format == 's')
            {
                count += ft_putstr(va_arg(args, char *));
            }
            else if (*format == 'i' || *format == 'd')
            {
                count += ft_putnbr(va_arg(args, int)); 
                //se agregan más conversiones
            }
        }
        else
        {
            count += ft_putchar(*format);
        }
        format++;
    }
    va_end(args); //finaliza el uso de arg variádicos; limpia la lista de argumentos
    return count; //devuelve el numero total de caracteres impresos
}

int main()
{
    ft_printf("Hola %s tengo %i", "Juan", 22);
    return (0);
}