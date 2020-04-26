// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "code/calling.h"
#include "code/MemoryMgr.h"
#include "code/mh2.h"
#include "code/menu.h"

using namespace Memory::VP;

void __declspec(naked) HookResetTimer()
{
	ResetTimer();
	static int jmpPoint = 0x7D2A9B;
	_asm
	{
		mov ds : 0x6ECE6C, 0
		jmp jmpPoint;
	}

}

void Hook_Init()
{
	TheMenu.Initialize();
	Call<0x53E5C0>();
}

void  HookProcess()
{
	TheMenu.ProcessMenu();
	Call<0x544780>();
}


void Init()
{

	InjectHook(0x543738, Hook_Init, PATCH_CALL);
	InjectHook(0x5455FE, HookProcess, PATCH_CALL);
	InjectHook(0x7D2A96, HookResetTimer, PATCH_JUMP);
	InjectHook(0x4344BC, HookVisibility, PATCH_CALL);

}

extern "C"
{
	__declspec(dllexport) void InitializeASI()
	{
		if (*(int*)0x63BC93 != (unsigned int)'hnaM')
		{
			MessageBoxA(0, "Invalid executable!", 0, 0);
		}
		else Init();
	}
}
