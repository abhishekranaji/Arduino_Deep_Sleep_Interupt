#include <avr/sleep.h>//this AVR library contains the methods that controls the sleep modes
#define interruptPin 3 //Pin we are going to use to wake up the Arduino


void setup() {
  Serial.begin(115200);//Start Serial Comunication
  digitalWrite(3, LOW);
  Serial.println(digitalRead(3));
  digitalWrite(13, LOW);
  pinMode(7,OUTPUT);//We use the led on pin 13 to indecate when Arduino is A sleep
  pinMode(interruptPin,INPUT_PULLUP);//Set pin d2 to input using the buildin pullup resistor
  digitalWrite(7,HIGH);//turning LED on
}

void loop() {
 delay(5000);//wait 5 seconds before going to sleep
 Going_To_Sleep();
}

void Going_To_Sleep(){
    sleep_enable();//Enabling sleep mode
    attachInterrupt(digitalPinToInterrupt(3), wakeUp, CHANGE);//attaching a interrupt to pin d2
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);//Setting the sleep mode, in our case full sleep
    digitalWrite(7,LOW);//turning LED off
    delay(1000); //wait a second to allow the led to be turned off before going to sleep
    sleep_cpu();//activating sleep mode
    Serial.println("just woke up!");//next line of code executed after the interrupt 
    digitalWrite(7,HIGH);//turning LED on
  }

void wakeUp(){
  Serial.println("Interrrupt Fired");//Print message to serial monitor
   sleep_disable();//Disable sleep mode
//  detachInterrupt(0); //Removes the interrupt from pin 2;
}
