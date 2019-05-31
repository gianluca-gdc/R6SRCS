#include <iostream>
#include <Windows.h>
#include <WinUser.h>
#include "MouseMovement.h"
#include "Sounds.h"


int main() {
	std::cout << "Recoil Control by Himbring \nPress F8 to Toggle RCS, Press END to Exit Program" << std::endl;
	initRCS();
	bool isPressedDownOnce = false;
	while (true) {
		if ((GetKeyState(VK_F8) & 0x80) != 0){
			if (!isPressedDownOnce){
				toggleRCS();
				if (isEnabledRCS()) {
					playLoadedSound();
				}
				else if (!isEnabledRCS()) {
					playOutOfAmmoSound();
				}
				isPressedDownOnce = true;
			}
		}
		else {
			isPressedDownOnce = false;
		}
		 if ((GetKeyState(VK_END) & 0x80) != 0) {
			stopRCS();
			break;
		}
	}
}
