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

//implementar %u manejar numeros sin signos 
int ft_put_unsigned(unsigned int n)
{
    int count;
    count = 0;

    if (n == 0) // Caso especial: si n es 0, imprime '0' directamente.
    {    
        return ft_putchar('0');
    }
    if (n > 9)
    {
        count += ft_put_unsigned(n / 10);
    }
    count += ft_putchar(n % 10 + '0');
    return count;
}


// Función para calcular la longitud de un número en hexadecimal
int hex_len(unsigned int num)
{
    int len = 0;
    while (num != 0)
    {
        len++;
        num = num / 16;
    }
    return len;
}
// Función para calcular la longitud de un número en hexadecimal
int hex_len(unsigned int num)
{
    int len = 0;
    while (num != 0)
    {
        len++;
        num = num / 16;
    }
    return len;
}

// Función auxiliar para imprimir en hexadecimal (minúsculas o mayúsculas)
void ft_put_hex(unsigned int num, const char format)
{
    if (num >= 16)
    {
        ft_put_hex(num / 16, format);
        ft_put_hex(num % 16, format);
    }
    else
    {
        if (num <= 9)
            ft_putchar(num + '0');
        else
        {
            if (format == 'x')
                ft_putchar(num - 10 + 'a');
            if (format == 'X')
                ft_putchar(num - 10 + 'A');
        }
    }
}

// Función para imprimir un número en hexadecimal (para %x o %X)
int ft_puthex(unsigned int num, const char format)
{
    if (num == 0)
        return write(1, "0", 1);  // Si el número es 0, imprimimos "0" directamente
    else
        ft_put_hex(num, format);    // Llamamos a la función para imprimir en hexadecimal
    
    return hex_len(num);  // Retornamos la longitud del número en hexadecimal
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
            else if (*format == 'u')
            {
                count += ft_put_unsigned(va_arg(args, unsigned int));
            }
            else if (*format == 'x' || *format == 'X')
            {
                count += ft_puthex_unsigned(va_arg(args, unsigned int), *format);  // Pasamos el formato ('x' o 'X')
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




// int main()
// {
//     ft_printf("Hola %s tengo %i y mi dirección es %p %% %% %%" , "Juan", 22, &main);
//     return (0);
// }

int main()
{
    ft_printf("Caso 1 (cero): %u\n", 00000000);
    ft_printf("Caso 2 (número pequeño): %u\n", 42);
    ft_printf("Caso 3 (número mediano): %u\n", 123456);
    ft_printf("Caso 4 (número grande): %u\n", 4294967295); // Máximo de unsigned int
    ft_printf("Caso 5 (mitad del rango): %u\n", 2147483647); // Máximo de un int con signo
    ft_printf("Hexadecimal minúsculas: %x\n", 255);
    ft_printf("Hexadecimal mayúsculas: %X\n", 255);
    return 0;
}