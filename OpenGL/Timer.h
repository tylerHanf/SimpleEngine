#pragma once
#include <thread>

class Timer {
 public:
  Timer(float timeLength);
  void startTimer(void);
  bool is_done(void);
  
 private:
  float timeLength;
  
};
