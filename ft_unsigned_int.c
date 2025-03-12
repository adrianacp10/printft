#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>


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







int ft_unsigned_len(unsigned int nb)
{
    int len = 0;
    while (nb != 0)
    {
        len++;
        nb = nb / 10;
    }
    return len;
}

char *ft_uitoa(unsigned int nb)
{
    char *str;
    int len;

    len = ft_unsigned_len(nb);
    str = (char *)malloc(sizeof(char) * (len + 1));
    if (!str)
        return NULL;
    str[len] = '\0';

    while (nb != 0)
    {
        str[len - 1] = nb % 10 + '0';
        nb = nb / 10;
        len--;
    }
    return str;
}

int ft_putunsigned(unsigned int nb)
{
    int char_printed = 0;
    char *str;

    if (nb == 0)
        char_printed += write(1, "0", 1);  // Maneja el caso especial para 0
    else
    {
        str = ft_uitoa(nb);
        char_printed += ft_putstr(str); // Asumiendo que ft_putstr imprime la cadena correctamente
        free(str);  // Libera la memoria al final
    }

    return char_printed;
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
            else if (*format == '%')
            {
                count += ft_putchar('%');
            }
            else if (*format == 'u')
            {
                count += ft_putunsigned(va_arg(args, unsigned int));
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
    ft_printf("Caso 1 (cero): %u\n", 00000000);
    ft_printf("Caso 2 (número pequeño): %u\n", 42222222222222222);
    ft_printf("Caso 3 (número mediano): %u\n", 123456);
    ft_printf("Caso 4 (número grande): %u\n", 4294967295); // Máximo de unsigned int
    ft_printf("Caso 5 (mitad del rango): %u\n", 2147483647); // Máximo de un int con signo
    return (0);
}