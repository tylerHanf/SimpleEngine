#pragma once

enum Mode {
    EDITOR,
    DEBUG,
    PROD
};

class ModeHandler {
 public:
    ModeHandler(const char** initMode, int lenArgv);
    Mode CurMode(void);
    bool CanSwitch(double currentTime);
  void SwitchMode(Mode newMode, double currentTime);
    
/*
TO HANDLE SWITCHING MODES:
   will make a timer that will modify canSwitch
   and set it to true when available
*/
  
 private:
    Mode curMode = EDITOR;
    double holdTime = 0;
  
};
