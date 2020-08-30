#include"../lib/jeeh-fork-master/jee.h"

//Definitions
// PIN 
#define PIN_LOC 0

//
#define OPEN 1
#define CLOSED 0

PinB<PIN_LOC> currentControl;

//

int main(){
    currentControl.mode(Pinmode::out);


}

void SET_ARMATURE(bool x){
    
}