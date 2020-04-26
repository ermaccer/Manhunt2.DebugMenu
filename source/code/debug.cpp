#include "debug.h"
#include "..\framework.h"
#include "MemoryMgr.h"
#include <iostream>
#include "mh2.h"
#include "menu.h"

bool KeyHit(unsigned int keyCode)
{
	return (GetKeyState(keyCode) & 0x8000) != 0;
}


std::string GetTrueFalse(int val)
{
	std::string ret;

	if (val == 0)  ret = "false";
	if (val == 1)  ret = "true";

	return ret;
}

std::string GetCharTrueFalse(char val)
{
	std::string ret;

	if (val == 0)  ret = "false";
	if (val == 1)  ret = "true";

	return ret;
}



void GivePlayerWeapon(int item)
{

	CEntity* plr = FindPlayer();
	if (GetEntity(GetRecordName(item)))
	{
		CreateInventoryItem(plr, item, true);
		AddAmmoToInventoryWeapon(item, 150);

	}
}

void CameraTeleporting()
{

	CVector vec;
	// reverse coords
	vec.x = *(float *)0x77D770 * -1;
	vec.y = *(float *)0x77D774 * -1;
	vec.z = *(float *)0x77D778 * -1;
	//WriteDebug(22, "Press SPACE to teleport");

	if (KeyHit(TheMenu.KeyQuickCameraTeleport))
	{
		// MoveEntity
		(*(void(__thiscall **)(int, CVector *, signed int))(*(int *)*(int*)0x789490 + 60))(*(int*)0x789490, &vec, 1);
		*(int*)0x7894A4 = 0;
		*(int*)0x78949C = 0;
	}
}

void PrintCoords()
{
	WriteDebug(20, "Player: X %f | Y %f | Z %f", *(float *)0x704F68, *(float *)0x704F6C, *(float *)0x704F70);
}

void SetDifficultySane()
{
	Call<0x547CD0, int>(0);
}

void SetDifficultyInsane()
{
	Call<0x547CD0, int>(1);
}

void SetWeatherFree()
{
	Call<0x5F5AA0, int>(eWeatherTypes::FREE);
}

void SetWeatherCloudy()
{
	Call<0x5F5AA0, int>(eWeatherTypes::CLOUDY);
}

void SetWeatherWindy()
{
	Call<0x5F5AA0, int>(eWeatherTypes::WINDY);
}

void SetWeatherRainy()
{
	Call<0x5F5AA0, int>(eWeatherTypes::RAINY);
}

void SetWeatherThunder()
{
	Call<0x5F5AA0, int>(eWeatherTypes::THUNDER);
}

void SetWeatherFoggy()
{
	Call<0x5F5AA0, int>(eWeatherTypes::FOGGY);
}

void SetWeatherClear()
{
	Call<0x5F5AA0, int>(eWeatherTypes::CLEAR);
}

void KillPlayer()
{
	if (FindPlayer())
	{
		SetHunterHideHealth(FindPlayer(), -1.0f);
	}
}

void RestartLevel()
{
	Call<0x5C2EC0, int>(4);
}

void CompleteLevel()
{
	Call<0x5C2EC0, int>(1);
}

void FailLevel()
{
	Call<0x5C2EC0, int>(0);
}

void Hook5Stars()
{
	Memory::VP::InjectHook(0x56A8C2, Give5Stars, PATCH_JUMP);
}

void __declspec(naked) Give5Stars()
{
	static int jmpPoint = 0x56A8C7;
	_asm {
		mov edi, 5
		mov eax, [eax]
		add eax, edi
		pop edi
	    jmp jmpPoint
	}
}

void PlayAnim()
{
	//CallMethod<0x42F330, CEntity*, const char*, float>(FindPlayer(), "BAT_KKK_GANGLAND_KNEE_ANIM", 0.0);
}




void TimerReset()
{
	*(int*)0x75B72C = 0;
	*(int*)0x75B730 = 0;
}

void TimerAddMin()
{
	(*(int*)0x75B72C)++;
}
void TimerAddSec()
{
	(*(int*)0x75B730)++;
}








