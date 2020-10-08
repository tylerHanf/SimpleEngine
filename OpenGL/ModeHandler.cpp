#include "ModeHandler.h"
#include <string>

ModeHandler::ModeHandler(const char** initMode) {
    if (!std::strcmp(initMode[1], "debug"))
	curMode = DEBUG;
}

void ModeHandler::SwitchMode(void) {
}
