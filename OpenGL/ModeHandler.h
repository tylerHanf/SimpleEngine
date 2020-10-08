#pragma once

enum Mode {
    EDITOR,
    DEBUG
};

class ModeHandler {
 public:
    ModeHandler(const char** initMode);
    void SwitchMode(void);
    
 private:
    Mode curMode = EDITOR;
};
