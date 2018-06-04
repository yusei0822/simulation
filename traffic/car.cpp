#include "car.h"

extern double deltaT;

// CAR()
// {
// }

void CAR::accelerate(){
  acceleration = 1;

}

void CAR::run(){

  velocity += acceleration * deltaT;


}
