/******** uart.c file of C2.5 : UART Driver Code ********/

#define uart_base 0x20201000 // UART peripheral base address

#define UDR 0x00        // address offset for data register
#define UFR 0x18        // address offset for flag register

#define TXFF 0x20       // TXFF = Transmit FIFO full
#define RXFE 0x10       // RXFE = Receive FIFO empty

volatile char* PL011_uart = (char *) uart_base;

int ugetc()                     // input a char from UART pointed by up
{
    while (*(PL011_uart+UFR) & RXFE);     // loop if UFR is REFE
    return *(PL011_uart+UDR);             // return a char in UDR
}

int uputc(char c)             // output a char to UART pointed by up
{
    while (*(PL011_uart+UFR) & TXFF);     // loop if UFR is TXFF
    *(PL011_uart+UDR) = c;                // write char to data register
}

int ugets(char *s)            // input a string of chars
{
    while ((*s = ugetc()) != '\r') {
        uputc(*s);
        s++;
    }
    *s = 0;
}

int uprints(char *s)          // output a string of chars
{
    while(*s) uputc(*s++);
}
