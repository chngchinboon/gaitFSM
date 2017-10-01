//FSM for gait tracking
//state machine library
#include <Fsm.h>
//library for haptic motor. remove if not needed.
/*
#include <Wire.h>
#include "Adafruit_DRV2605.h"

Adafruit_DRV2605 drv;
*/

//setup states
#define left_up 1
#define left_down 2
#define right_up 3
#define right_down 4


//setup state callback functions
void on_leftfoot_up(){
  Serial.println("Left foot up");
  //motor right go  
}
void on_leftfoot_down(){
  Serial.println("Left foot down");
  //motor right stop  
}

void on_rightfoot_up(){
  Serial.println("Right foot up");
  //motor left go  
}

void on_rightfoot_down(){
  Serial.println("Right foot down");
  //motor right stop  
}

void on_bothfoot_down(){
  Serial.println("Both foot down");
  //all motor stop  
}
//transition callbacks
void on_trans_start_to_leftstep()
{
  Serial.println("Transitioning start to left step");
}
void on_trans_start_to_rightstep()
{
  Serial.println("Transitioning start to right step");
}
void on_trans_leftstep_to_right()
{
  Serial.println("Transitioning left step to right");
}
void on_trans_rightstep_to_left()
{
  Serial.println("Transitioning right step to left");
}
void on_trans_leftstep_to_start()
{
  Serial.println("Transitioning left step to start");
}
void on_trans_rightstep_to_start()
{
  Serial.println("Transitioning right step to start");
}

State state_bothfooton(on_bothfoot_down,NULL);
State state_leftstep(on_leftfoot_up, &on_leftfoot_down);
//State state_left_on(on_light_on_enter, &on_light_on_exit);
State state_rightstep(on_rightfoot_up, &on_rightfoot_down);
//State state_right_on(on_light_off_enter, &on_light_off_exit);
Fsm fsm(&state_bothfooton);
//Fsm fsm(&state_right_on);


void setup() {
  Serial.begin(9600);
  /*  
  Serial.println("DRV test");
  drv.begin();
    
  // I2C trigger by sending 'go' command 
  drv.setMode(DRV2605_MODE_INTTRIG); // default, internal trigger when sending GO command

  drv.selectLibrary(1);
  drv.setWaveform(0, 84);  // ramp up medium 1, see datasheet part 11.2
  drv.setWaveform(1, 1);  // strong click 100%, see datasheet part 11.2
  drv.setWaveform(2, 0);  // end of waveforms
  */
  fsm.add_transition(&state_bothfooton, &state_leftstep,
                     left_up,
                     &on_trans_start_to_leftstep);
  fsm.add_transition(&state_leftstep, &state_bothfooton,
                     left_down,
                     &on_trans_leftstep_to_start);
  fsm.add_transition(&state_bothfooton, &state_rightstep,
                     right_up,
                     &on_trans_start_to_rightstep);
  fsm.add_transition(&state_rightstep, &state_bothfooton,
                     right_down,
                     &on_trans_rightstep_to_start);
  
}

void loop() {  
  /*
  // play the effect!
  drv.go();
  //wait abit
  delay(500);
  */
  delay(2000);
  fsm.trigger(left_up);
  delay(2000);
  fsm.trigger(left_down);
  delay(2000);
  fsm.trigger(right_up);
  delay(2000);
  fsm.trigger(right_down);

  
}
