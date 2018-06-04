#include "car.h"

extern deltaT;

Car::Car()
{
}

void Car::accelerate(){
  acceleration = 1;

}

void Car::run(){

  velocity += acceleration * deltaT;

  x =
}
