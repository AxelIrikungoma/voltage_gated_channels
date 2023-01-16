#include <Servo.h>

Servo my_slow_servo;
Servo my_fast_servo;

const int offset_slow = 60;
const int offset_fast = 110;

int pos_slow = 0 + offset_slow;
int pos_fast = 0 + offset_fast;

const int slow_period = 30;
const int fast_period = 5;

const int action_button = 5;
const int reset_button = 6;

void setup() {
  my_slow_servo.attach(9);
  my_fast_servo.attach(10);

  my_slow_servo.write(offset_slow);
  my_fast_servo.write(offset_fast);
}

void loop() {
  if (digitalRead(action_button) == HIGH){
    fast_open_slow_close();
  }
  
  if (digitalRead(reset_button) == HIGH){
    fast_close_slow_open();
  }
}

void fast_open_slow_close(){
  unsigned long start_fast_timer = millis();
  unsigned long start_slow_timer = millis();

  boolean fast_done = false;
  boolean slow_done = false;
  
  while (!fast_done or !slow_done){
    if (pos_fast > offset_fast - 100){
      unsigned long current_fast_timer = millis();
      if (current_fast_timer - start_fast_timer >= fast_period){
        my_fast_servo.write(pos_fast);
        start_fast_timer = current_fast_timer;
        --pos_fast;
      }
    } else{
      fast_done = true;
    }

    if (pos_slow < 100 + offset_slow){
      unsigned long current_slow_timer = millis();
      if (current_slow_timer - start_slow_timer >= slow_period){
        my_slow_servo.write(pos_slow);
        start_slow_timer = current_slow_timer;
        ++pos_slow;
      }
    } else{
      slow_done = true;
    }
  }
}

void fast_close_slow_open(){
  unsigned long start_fast_timer = millis();
  unsigned long start_slow_timer = millis();

  boolean fast_done = false;
  boolean slow_done = false;
  
  while (!fast_done or !slow_done){
    if (pos_fast < offset_fast){
      unsigned long current_fast_timer = millis();
      if (current_fast_timer - start_fast_timer >= fast_period){
        my_fast_servo.write(pos_fast);
        start_fast_timer = current_fast_timer;
        ++pos_fast;
      }
  } else{
    fast_done = true;
  }

  if (pos_slow > offset_slow){
      unsigned long current_slow_timer = millis();
      if (current_slow_timer - start_slow_timer >= slow_period){
        my_slow_servo.write(pos_slow);
        start_slow_timer = current_slow_timer;
        --pos_slow;
      }
    } else{
      slow_done = true;
    }
  }
}
