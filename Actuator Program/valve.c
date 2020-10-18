#include"../lib/jeeh-fork-master/jee.h"
#include"GPIO.h"

//Definitions
// PIN 
#define PIN_LOC 0

int main(){
    //Call component driver function 
    //Set valve to valve state (OUT)
    valveState(PIN_LOC,OUT);
    return 0;
}

//Component driver for solenoid valve (Open, close)
uint8_t (valveState)(uint8_t valvePin, uint8_t state){
    //PinMode
    //Digitial Write To PIN
    //HIGH or LOW
    switch(state){
        case OUT:
            SET_ECU_GPIO_HIGH(valvePin,CLOCK_A); //<- Assume CLOCK PORT A - CHANGE
        case IN:
            SET_ECU_GPIO_LOW(valvePin,CLOCK_A); //<- Assume CLOCK PORT A - CHANGE
    }
    return 0;
}
