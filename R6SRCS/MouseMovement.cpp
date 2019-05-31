#include <iostream>
#include <Windows.h>
#include <WinUser.h>
#include <thread>
#include "MouseMovement.h"


#define MOVE_UP false
#define MOVE_DOWN true

static volatile bool enableRCS = false;
static bool runningRCS = true;

static void moveMouse(bool direction) {
	POINT cursorPosition;
	int cursorX, cursorY;
	GetCursorPos(&cursorPosition);
	if (direction == MOVE_DOWN) {
		cursorX = cursorPosition.x + DELTA_X;
		cursorY = cursorPosition.y + DELTA_Y;
	}else {
		cursorX = cursorPosition.x - DELTA_X;
		cursorY = cursorPosition.y - DELTA_Y;
	}
	SetCursorPos(cursorX, cursorY);
}

static void whenLHeldDown() {
	do {
		mouse_event(1, DELTA_X, DELTA_Y, 0, 0);
		/*moveMouse(MOVE_DOWN);*/
		Sleep(DELAY);
		mouse_event(1, -DELTA_X, -DELTA_Y, 0, 0);
		/*moveMouse(MOVE_UP);*/
		Sleep(DELAY);
	} while ((GetKeyState(VK_LBUTTON) & 0x80) != 0 && enableRCS);
}

static void checkMouseEvent() {
	while (runningRCS) {
		while (enableRCS) {
			if ((GetKeyState(VK_LBUTTON) & 0x80) != 0) {
				whenLHeldDown();
			}
		}
	}
}

void toggleRCS() {
	enableRCS = !enableRCS;
	
}

void initRCS() {
	std::thread* checkMouseEventInBG = new std::thread(checkMouseEvent);
}

void stopRCS() {
	runningRCS = false;
}

bool isEnabledRCS() {
	return enableRCS;
}