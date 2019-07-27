#include "debug.h"
#include "..\stdafx.h"
#include "MemoryMgr.h"
#include "mh2.h"

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



void GivePlayerWeapon(int item, const char* record, bool firearm)
{

	CEntity* plr = FindPlayer();
	if (GetEntity(record))
	{
		CreateInventoryItem(plr, item, true);
		if (firearm == true) AddAmmoToInventoryWeapon(item, 150);

	}
	else
	{
		Memory::VP::Patch<char>(0x53D8DC, 16);
		WriteDebug(21, "%s is missing on this level!", record);
	}
}

void CameraTeleporting()
{

	CVector vec;
	// reverse coords
	vec.x = *(float *)0x77D770 * -1;
	vec.y = *(float *)0x77D774 * -1;
	vec.z = *(float *)0x77D778 * -1;
	WriteDebug(22, "Press SPACE to teleport");

	if (KeyHit(VK_SPACE))
	{
		// MoveEntity
		(*(void(__thiscall **)(int, CVector *, signed int))(*(int *)*(int*)0x789490 + 60))(*(int*)0x789490, &vec, 1);
		*(int*)0x7894A4 ^= 1;
	}
}
