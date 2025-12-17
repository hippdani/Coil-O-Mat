/*Button management and debouncing 
 * call of Button.refresh() has to be called continously, at least in smaller intervalls than DEBOUNCE_TIME
 * the code refers to voltage states (up and down) NOT button states.
 * State changes are immediate, events are set after debouncing is clear (voltage is settled for at least DEBOUNCE_TIME)
 */

#define DEBOUNCE_TIME 50 //in ms

class Button {
private:
  int pin;
  unsigned long down_at; //timing based on events (after debouncing)
  unsigned long pre_down_at; //timing fromlast registered switching action
  unsigned long up_at; //timing based on events (after debouncing)
  unsigned long pre_up_at; //timing fromlast registered switching action
  bool state;
  bool risingEvent;
  bool fallingEvent;
  bool preRisingEvent;
  bool preFallingEvent;
  int debounce_time;
  
public:
  Button(int, int);
  void refresh();
  long downFor();
  long upFor();
  bool getRisingEvent();
  bool getFallingEvent();
  bool getState();
};

Button::Button(int PIN, int debounce_time_in = DEBOUNCE_TIME)
{
  //TODO: make that no events are triggered on powerup, mind the debouncer time constant
  this->pin = PIN;
  this->debounce_time = debounce_time_in;
  this->down_at = 0;
  this->up_at = 0;
  this->state = 0;
  this->risingEvent = 0;
  this->fallingEvent = 0;
  this->preRisingEvent = 0;
  this->preFallingEvent = 0;
  pinMode(pin, INPUT_PULLUP);
  getRisingEvent();
  getFallingEvent();
}

void Button::refresh()
{
  if(digitalRead(pin) != state) //register a change of state
  {
    state = !state;
    if(state == 0)
    {
      pre_down_at = millis();
      preFallingEvent = 1;
    }
    if(state == 1)
    {
      pre_up_at = millis();
      preRisingEvent = 1;
    }
  }
  else //set an event according to debouncing rules
  {
    if(state == 0)
    {
      if(preFallingEvent && ((pre_down_at + debounce_time) < millis()))
      {
        down_at = millis();
        preFallingEvent = 0;
        fallingEvent = 1;
      }
    }
    if(state == 1)
    {
      if(preRisingEvent && ((pre_up_at + debounce_time) < millis()))
      {
        up_at = millis();
        preRisingEvent = 0;
        risingEvent = 1;
      }
    }
  }
}

bool Button::getRisingEvent()
{
  if(risingEvent)
  {
    risingEvent = 0;
    return(1);
  }
  return(0);
}

bool Button::getFallingEvent()
{
  if(fallingEvent)
  {
    fallingEvent = 0;
    return(1);
  }
  return(0);
}

long Button::downFor()
{
  return millis() - down_at;
}

long Button::upFor()
{
  return millis() - up_at;
}

bool Button::getState()
{
  return(state);
}


class Encoder {
/*
 * Two switch encoder. Increments only once per full cycles. Relies on class Button
 * Set Buttons' debouncing time appopriately for the encoder speed
 */
private:
  Button sw1;
  Button sw2;
  long num;
  bool event;
public:
  Encoder(int pin_sw1, int pin_sw2, int debounce_time_in);
  void refresh();
  void reset();
  long getNum();
  bool getEvent();
};

Encoder::Encoder(int pin_sw1, int pin_sw2, int debounce_time_in = DEBOUNCE_TIME)
  : sw1(pin_sw1, debounce_time_in), sw2(pin_sw2, debounce_time_in), num(0), event(false)
{
  //contents moved to initializer list
}

void Encoder::refresh()
{
  sw1.refresh();
  sw2.refresh();
  if(sw1.getFallingEvent() && (sw2.getState() == 1))
  {
    num++;
    event = 1;
  }
  if(sw1.getRisingEvent() && (sw2.getState() == 1))
  {
    num--;
    event = 1;
  }
}

void Encoder::reset()
{
  num = 0;
  event = 0;
}

long Encoder::getNum()
{
  return num;
}

bool Encoder::getEvent()
{
  if(event)
  {
    event = 0;
    return 1;
  }
  return 0;
}
