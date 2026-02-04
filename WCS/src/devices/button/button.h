#ifndef __BUTTON__
#define __BUTTON__
class Button
{
public:
  virtual bool wasPressed() = 0;
  virtual void update() = 0;
  virtual void resetPressed() = 0;
};


#endif
