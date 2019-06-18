#include <iostream>
#include <Windows.h>
#include <WinUser.h>
#include <winnt.h>
#include <thread>
#include "MouseClick.h"
#include "MouseMovement.h"
#include "Sounds.h"


int main() {
	std::cout << "Recoil Control by Himbring \nPress F8 to Toggle RCS \nPress F3 to Toggle RFS \nPress END to Exit Program" << std::endl;
	initRCS();
	initRFS();
	bool isRCSPressedDownOnce = false;
	bool isRFSPressedDownOnce = false;
	while (true) {
		if ((GetKeyState(VK_F8) & 0x80) != 0){
			if (!isRCSPressedDownOnce){
				toggleRCS();
				if (isEnabledRCS()) {
					playLoadedSound();
				}
				else if (!isEnabledRCS()) {
					playOutOfAmmoSound();
				}
				isRCSPressedDownOnce = true;
			}
		}
		else {
			isRCSPressedDownOnce = false;
		}
		 if ((GetKeyState(VK_END) & 0x80) != 0) {
			stopRCS();
			break;
		}
		 if ((GetKeyState(VK_F3) & 0x80) != 0) {
			 if (!isRFSPressedDownOnce) {
				 toggleMouseClick();
				 if (isRFSEnabled()) {
					 playLoadedSound();
				 }
				 else if (!isRFSEnabled()) {
					 playOutOfAmmoSound();
					}
				 isRFSPressedDownOnce = true;
			 }
			 
		 }
		 else {
			 isRFSPressedDownOnce = false;
		 }
	}
}
