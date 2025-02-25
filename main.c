#include <stdio.h>
#include "ft_printf.h" // Asegúrate de incluir tu header

int main()
{
    int num = 255;
    void *ptr = &num;

    printf("Número en hexadecimal usando ft_puthex: ");
    ft_puthex(num, "0123456789abcdef");
    printf("\n");

    printf("Número en hexadecimal usando printf: %x\n", num);

    printf("Puntero usando ft_putptr: ");
    ft_putptr(ptr);
    printf("\n");

    printf("Puntero usando printf: %p\n", ptr);

    return 0;
}