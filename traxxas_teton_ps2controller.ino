#include <Servo.h>
#include <Wire.h>
#include <PS2X_lib.h>

// define pins for ps2 controller
#define PS2_DAT        13   // ps2 controller or receiver pin 1 (data)
#define PS2_CMD        12   // ps2 controller or receiver pin 2 (command)
#define PS2_SEL        11   // ps2 controller or receiver pin 6 (attention/select)
#define PS2_CLK        10   // ps2 controller or receiver pin 7 (clock)

PS2X ps2x; // create PS2 Controller Object

int stickLX = 0; // read in values for left stick x-axis
int stickLY = 0; // read in values for left stick y-axis
int stickRX = 0; // read in values for right stick x-axis
int stickRY = 0; // read in values for right stick y-axis
int error = 0; // check message from ps2 gamepad
Servo traxxasESC;
Servo traxxasServo;
float servo;
float esc;



void setup() {
  
  traxxasESC.attach(9);
  traxxasServo.attach(3);
  Serial.begin(57600); // make sure serial monitor is also set to 57600

  delay(300);  //added delay to give wireless ps2 module some time to startup, before configuring it

  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, false, false);

  if(error == 0){
    Serial.print("DualShock Controller Found - Configured Successfully");
  }  
  else if(error == 1)
    Serial.println("No controller found - check wiring");
   
  else if(error == 2)
    Serial.println("Controller found but not accepting commands");

  else if(error == 3)
    Serial.println("Controller refusing to enter Pressures mode - may not support it. ");
  
}

void loop() {

  traxxasESC.writeMicroseconds(1500);
  traxxasServo.write(90);
  
  ps2x.read_gamepad(false, 0); //read controller and set large motor to spin at 'vibrate' speed
  

  stickLX = ps2x.Analog(PSS_LX);
  stickLY = ps2x.Analog(PSS_LY);
  stickRX = ps2x.Analog(PSS_RX);
  stickRY = ps2x.Analog(PSS_RY);



  if (stickLY < 127) {
      Serial.print("Speeding up: ");
      Serial.println(stickLY);
      esc = map(stickLY, 126, 0, 1500, 1000);
      traxxasESC.writeMicroseconds(esc);
      Serial.println(esc);
    }

//    if (stickLX < 127) {
//      Serial.print("Turning left values for left stick: ");
//      Serial.println(stickLX);
//    }

    if (stickLY > 127) {
      Serial.print("Slowing down: ");
      Serial.println(stickLY);
      esc = map(stickLY, 0, 126, 1500, 2000);
      traxxasESC.writeMicroseconds(esc);
      Serial.println(esc);
    }

//    if (stickLX > 128) {
//      Serial.print("Turning right values for left stick: ");
//      Serial.println(stickLX);
//    }

    if (stickRX < 127) {
      Serial.print("Turning left: ");
      Serial.println(stickRX);
      servo = map(stickRX, 0, 126, 135, 89);
      traxxasServo.write(servo);
      delay(15);
    }

//    if (stickRY < 127) {
//      Serial.print("Right stick pushed up: ");
//      Serial.println(stickRY);
//    }

    if (stickRX > 128) {
      Serial.print("Turning right: ");
      Serial.println(stickRX);
      servo = map(stickRX, 129, 255, 89, 45);
      traxxasServo.write(servo);
      delay(15);
    }

//    if (stickRY > 127) {
//      Serial.print("Right stick pushed down: ");
//      Serial.println(stickRY);
//    }
    
    
    if(ps2x.ButtonPressed(PSB_START)) {       
      Serial.println("Start Button");
    }
    
    if(ps2x.ButtonPressed(PSB_SELECT)) {
      Serial.println("Select Button");
    }    

    if(ps2x.ButtonPressed(PSB_PAD_UP)) {      
      Serial.println("Up on D-Pad");
    }
    
    if(ps2x.ButtonPressed(PSB_PAD_RIGHT)){
      Serial.println("Right on D-Pad");
    }
    
    if(ps2x.ButtonPressed(PSB_PAD_LEFT)){
      Serial.println("Left on D-Pad");
    }
    
    if(ps2x.ButtonPressed(PSB_PAD_DOWN)){
      Serial.println("Down on D-Pad");
    } 

    if(ps2x.ButtonPressed(PSB_CROSS)) {
      Serial.println("X has been pressed");
    }

    if(ps2x.ButtonPressed(PSB_SQUARE)) {
      Serial.println("Square has been pressed");
    }

    if(ps2x.ButtonPressed(PSB_TRIANGLE)) {
      Serial.println("Triangle has been pressed");
    }

    if(ps2x.ButtonPressed(PSB_CIRCLE)) {
      Serial.println("Circle has been pressed");
    }

    if(ps2x.ButtonPressed(PSB_L1)) {
      Serial.println("L1 has been pressed");
    }

    if(ps2x.ButtonPressed(PSB_L2)) {
      Serial.println("L2 has been pressed");
    }

    if(ps2x.ButtonPressed(PSB_L3)) {
      Serial.println("L3 has been pressed");
    }

    if(ps2x.ButtonPressed(PSB_R1)) {
      Serial.println("R1 has been pressed");
    }

    if(ps2x.ButtonPressed(PSB_R2)) {
      Serial.println("R2 has been pressed");
    }

    if(ps2x.ButtonPressed(PSB_R3)) {
      Serial.println("R3 has been pressed");
    }


  delay(50);
}
