/*****gpio.c*****/
#include "defines.h"

volatile unsigned int* gpio_reg;

typedef volatile struct gpio{
    int sel;
    int bit;
    int set;
    int clr;
    int gpio_bit;
} GPIO;

GPIO gpio[27];

void gpio_init(){
    gpio_reg = (unsigned int*) GPIO_BASE;
    int i;
    int tiental;
    GPIO *gp;
    for(i = 0; i<=27;i++){
        gp = &gpio[i];
        gp->bit = (i%10)*3;
        gp->set = GPIO_GPSET0;
        gp->clr = GPIO_GPCLR0;
        gp->gpio_bit = i;

        tiental = i/10;
        switch (tiental) {
            case 0:
                gp->sel = GPIO_GPFSEL0;
                break;
            case 1:
                gp->sel = GPIO_GPFSEL1;
                break;
            case 2:
                gp->sel = GPIO_GPFSEL2;
                break;
            default: break;
        }
    }

}

void shortDelay(){
  volatile unsigned int tim;
  for(tim = 0; tim < 150; tim++);
}

void set_falling_edge(GPIO *up){
  gpio_reg[GPIO_GPFEN0] |= (1 << up -> gpio_bit);
}

void set_gpio_pud(GPIO *up){
  gpio_reg[GPIO_GPPUD] = 2;
  shortDelay();
  gpio_reg[GPIO_GPPUDCLK0] = (1 << up->gpio_bit);
  shortDelay();
  gpio_reg[GPIO_GPPUD] = 0;
  gpio_reg[GPIO_GPPUDCLK0] = (0 << up->gpio_bit);
}



void set_GPIO_output(GPIO *up){
    gpio_reg[up->sel] |= (1 << up->bit);
}

void set_GPIO_output_fnct(GPIO *up, int function_val){
    gpio_reg[up->sel] |= (function_val << up->bit);    //E.g. alt0 fnct = 100
}

void set_GPIO_input(GPIO *up){
  gpio_reg[up->sel] |= (0<< up->bit);
}

void set_pin(GPIO *up){
    gpio_reg[up->set] = (1 << up->gpio_bit);
}

void clear_pin(GPIO *up){
    gpio_reg[up->clr] = (1 << up->gpio_bit);
}

int get_pin(GPIO *up){
  int status = (gpio_reg[GPIO_GPEDS0] >> up -> gpio_bit) & 1;
  gpio_reg[GPIO_GPEDS0] |= (1 << up -> gpio_bit);
  return status;
}
