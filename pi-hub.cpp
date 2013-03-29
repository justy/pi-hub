// pi-hub Raspberry Pi GPIO actuator hub by @justy

// We define pin numbers for each actuator and listen out for commands from the Ninja Platform

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include <wiringPi.h>
#include <softPwm.h>

// Define our pin numbers

// This code uses the BCM GPIO numbering system  (R2)
// the two numbers that are commented are WiringPi and Header numbers
// I would like to formally register my opinion that the RPi pin numbering
// feels at first like a debarkle.  However, once one has printed and 
// laminated a diagram such as can be found at https://projects.drogon.net/raspberry-pi/wiringpi/pins/
// then the balance of the universe is restored.

// I've attached a pair of RGB LEDs to my hub:
// LED 1
#define PIN_Eye1_R 2//8,3
#define PIN_Eye1_G 3//9,5
#define PIN_Eye1_B 4//7,7
// LED 2
#define PIN_Eye2_R 14//15,8
#define PIN_Eye2_G 15//16,10
#define PIN_Eye2_B 17//0,11

// I hacked my kid's lightsabre toy to be activated by a pin:
#define PIN_Lightsabre 18//1,12

// Homer can shout 'Wahooo!' when one of our devs checks in some code
#define PIN_Homer 27//2,13

// Play a cheesy wedding tune
#define PIN_BridalMarch 22//3,15

// Lights and noises so far, but what about some motorised action?`
#define PIN_Motor 23//4,16


int main ()
{
  initRGBLEDs();
  
  // ?? I still don't know how this is done from the perspective of a RPi...
  
  // Listen for events from the block
  

}


/////////////////////////////////////
// LED control
// I've used common-anode LEDs and thus to turn an LED on I need to set its 
// various pin's levels to low values.  For sanity's sake I reverse this
// relationship in these functions


// The other bit of business here is some LED component level attenuation.
// My LEDs' green is rather overpowering and so there is provision here to
// set maximum levels per colour component.  We still call setRed, setGreen, etc with desired percentage values:

// Attenuations
#define RED_Max 100
#define GRN_Max 80
#define BLU_Max 100 

void initRGBLEDs() {
  softPwmCreate (PIN_Eye1_R, 100, 100);
  softPwmCreate (PIN_Eye1_G, 100, 100);
  softPwmCreate (PIN_Eye1_B, 100, 100);
  softPwmCreate (PIN_Eye2_R, 100, 100);
  softPwmCreate (PIN_Eye2_G, 100, 100);
  softPwmCreate (PIN_Eye2_B, 100, 100);  
}

// These setFoo functions set the colours of my LEDs two at a time- I'm using these LEDs for a custom Nina
void setRed(int percent) {
  // TODO attenuation
  // clamp the value (prolly redundant)
  if (percent < 0) percent = 0;
  if (percent > 100) percent = 100;
  softPWMWrite(PIN_Eye1_R,100-percent);
  softPWMWrite(PIN_Eye2_R,100-percent);
}

void setGrn(int percent) {
  // clamp the value (prolly redundant)
  //if (percent < 0) percent = 0;
  //if (percent > 100) percent = 100;
  softPWMWrite(PIN_Eye1_G,100-percent);
  softPWMWrite(PIN_Eye2_G,100-percent);
}

void setBlu(int percent) {
  // clamp the value (prolly redundant)
  if (percent < 0) percent = 0;
  if (percent > 100) percent = 100;
  softPWMWrite(PIN_Eye1_B,100-percent);
  softPWMWrite(PIN_Eye2_B,100-percent);
}

void setGrey(int percent) {
  setRed(percent);
  setGrn(percent);
  setBlu(percent);
}

/////////////////////////////////////
// Misc binary actuators
void initLightSabre() {
  pinMode(PIN_Lightsabre, OUTPUT);
}

void LightSabreOn() {
  digitalWrite(PIN_Lightsabre, 1);
}

void LightSabreOff() {
  digitalWrite(PIN_Lightsabre, 0);
}

void initHomer() {
  pinMode(PIN_Homer, OUTPUT);
}

void HomerOn() {
  digitalWrite(PIN_Homer, 1);
}

void HomerOff() {
  digitalWrite(PIN_Homer, 0);
}

void initBridalMarch() {
  pinMode(PIN_BridalMarch, OUTPUT);
}

void bridalMarchOn() {
  digitalWrite(PIN_BridalMarch, 1); 
}

void bridalMarchOff() {
  digitalWrite(PIN_BridalMarch, 0);  
}

void initMotor() {
  // DC Motors can handle a wee bit of PWM
  softPWMCreate(PIN_Motor, 0, 100);
}

void motorOn() {
  softPWMWrite(PIN_Motor, 100);
}

void motorOff() {
  softPWMWrite(PIN_Motor, 0);
}

void setMotor(int percentage) {
  softPWMWrite(PIN_Motor, percent);
}



