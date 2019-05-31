#include <Windows.h>
#include <string>
#include <mmsystem.h>
#include "resource3.h"
#pragma comment(lib, "winmm.lib")

void playLoadedSound() {
	PlaySound(MAKEINTRESOURCE(IDR_WAVE1),
		GetModuleHandle(0)/* MFC AfxGetInstanceHandle()*/,
		SND_ASYNC | SND_RESOURCE);
}

void playOutOfAmmoSound(){
	PlaySound(MAKEINTRESOURCE(IDR_WAVE2),
		GetModuleHandle(0)/* MFC AfxGetInstanceHandle()*/,
		SND_ASYNC | SND_RESOURCE);
}