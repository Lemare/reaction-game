/************* t.c file of C2.5 **************/
#include "uart.c" // UART driver code file
#include "gpio.c"



int lampIsAan = 0;

void delay(){
  volatile unsigned int tim;
  for(tim = 0; tim < 10000000; tim++);
}

void turnOn(){
  uprints("turning lamp on\n");
  set_pin(&gpio[4]);
  lampIsAan = 1;
}

int main()
{

    gpio_init();
    set_gpio_pud(&gpio[2]);
    set_gpio_pud(&gpio[3]);
    set_GPIO_output(&gpio[4]);
    set_GPIO_output_fnct(&gpio[14], 0b100);  //GPIO 14 -> alt0 = TX
    set_GPIO_output_fnct(&gpio[15], 0b100);  //GPIO 15 -> alt0 = RX
    set_falling_edge(&gpio[2]);
    set_falling_edge(&gpio[3]);
    uprints("starting\n");
    turnOn();



    while(1){
      if(lampIsAan == 1) {
        delay();
        clear_pin(&gpio[4]);
        lampIsAan = 0;
      }
      if(lampIsAan == 0){

        if(get_pin(&gpio[2]) == 0b1) {
          uprints("Links wint\n");
          delay();
          turnOn();

        }


        else if(get_pin(&gpio[3]) == 0b1) {
          uprints("Rechts wint\n");
          delay();
          turnOn();

        }
      }
    }

}
