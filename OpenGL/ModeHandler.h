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
    void SwitchMode(Mode newMode);
    
 private:
    Mode curMode = EDITOR;
};
