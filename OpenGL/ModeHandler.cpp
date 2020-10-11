#include "ModeHandler.h"
#include "Debug.h"
#include <string>

ModeHandler::ModeHandler(const char** initMode, int lenArgv) {
    if (lenArgv > 1 && !std::strcmp(initMode[1], "debug")) {
	Debug::Instance().PrintError(initMode[1]);
	curMode = DEBUG;
    }
}

Mode ModeHandler::CurMode() {
    return curMode;
}

void ModeHandler::SwitchMode(Mode newMode) {
    curMode = newMode;
}
