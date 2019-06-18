#include <Windows.h>
#include <WinUser.h>
#include <thread>
#include <iostream>
#include <mutex>
#include <winnt.h>
#include "MouseClick.h"

static volatile bool isClickEnabled = false;

static void checkMouseDown();

static void clickOnce() {
	INPUT input;
	WORD vkey = MOUSE_CLICK_SHORTCUT; // see link below
	input.type = INPUT_KEYBOARD;
	input.ki.wScan = MapVirtualKey(vkey, MAPVK_VK_TO_VSC);
	input.ki.time = 0;
	input.ki.dwExtraInfo = 0;
	input.ki.wVk = vkey;
	input.ki.dwFlags = 0; // there is no KEYEVENTF_KEYDOWN
	SendInput(1, &input, sizeof(INPUT));
	Sleep(15);
	input.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &input, sizeof(INPUT));
	Sleep(15);
}

void toggleMouseClick() {
	isClickEnabled = !isClickEnabled;
}

static void multipleMouseClick() {
	do {
		clickOnce();
	} while (isClickEnabled&& GetKeyState(VK_LBUTTON) < 0);
}

void initRFS() {
	std::thread* mouseThread = new std::thread (&checkMouseDown);
}

static void checkMouseDown() {
	while (true) {
		if (isClickEnabled) {
			if (GetKeyState(VK_LBUTTON) < 0) {
				multipleMouseClick();
			}
		}
		else if (GetKeyState(VK_LBUTTON) < 0) {
			clickOnce();
			while (GetKeyState(VK_LBUTTON) < 0) {
				Sleep(10);
			}
		}
	}
}

bool isRFSEnabled() {
	return isClickEnabled;
}