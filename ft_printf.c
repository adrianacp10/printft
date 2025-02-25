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

#include <stdint.h> //esta libreria proporciona tipos de datos con tamaños especificos como uint32_t o uint64_t

// Función auxiliar para imprimir en hexadecimal, base es una cadena que contiene 16 caracteres hexadecimales 0123456789abcdef
int ft_puthex(unsigned long n, char *base)
{
    int count;
    count = 0;

    if(n >= 16)
    {
        count += ft_puthex(n / 16, base);
    }
    count += ft_putchar(base[n % 16]);
    return count;
}

// Función para imprimir un puntero hexadecimal
int ft_putptr(void *ptr)
{
    int count;
    count = 0;

    unsigned long address = (unsigned long)ptr;

    count += ft_putstr("0x");
    count += ft_puthex(address, "0123456789abcdef");
    return count;
}

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
            }
            else if (*format == 'p')
            {
                count += ft_putptr(va_arg(args, void *));
            }
            else if (*format == '%')
            {
                count += ft_putchar('%');
            }
            // se agregan más conversiones 
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
    ft_printf("Hola %s tengo %i y mi dirección es %p %% %% %%" , "Juan", 22, &main);
    return (0);
}