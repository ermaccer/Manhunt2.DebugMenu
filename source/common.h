#pragma once

#include <string>
#include <time.h>
#include <iostream>

#include "stdafx.h"
#include "mh2.h"
#include "MemoryMgr.h"


// mh2 
int& ShadowCamerasCheck = *(int*)0x75B334;
int& MemoryUsed = *(int*)0x75B300;
int& FreezeWorld = *(int*)0x78949C;
int& FreeCamera = *(int*)0x7894A4;

bool KeyHit(unsigned int keyCode)
{
	return (GetKeyState(keyCode) & 0x8000) != 0;
}


std::string GetTrueFalse(int val)
{
	std::string ret;

	if (val == 0)  ret = "false";
	if (val == 1)  ret = "true ";

	return ret;
}


// menu functions

void NoClip()
{
	CVector vec;
	vec.x = *(float *)0x704F68;
	vec.y = *(float *)0x704F6C;
	vec.z = *(float *)0x704F70;
	WriteDebug(22, "Experimental! Use WASD to control (relative to camera). You can disable Debug Menu if you want. Do NOT go too high or too far, it will crash.");
	if (KeyHit(87))
	{
		vec.z -= 0.3f;
		(*(void(__thiscall **)(int, CVector *, signed int))(*(int *)*(int*)0x789490 + 60))(*(int*)0x789490, &vec, 1);
	}
	if (KeyHit(65))
	{
		vec.x += 0.3f;
		(*(void(__thiscall **)(int, CVector *, signed int))(*(int *)*(int*)0x789490 + 60))(*(int*)0x789490, &vec, 1);
	}
	if (KeyHit(68))
	{
		vec.x -= 0.3f;
		(*(void(__thiscall **)(int, CVector *, signed int))(*(int *)*(int*)0x789490 + 60))(*(int*)0x789490, &vec, 1);
	}
	if (KeyHit(83))
	{
		vec.z += 0.3f;
		(*(void(__thiscall **)(int, CVector *, signed int))(*(int *)*(int*)0x789490 + 60))(*(int*)0x789490, &vec, 1);
	}
}

void CameraTeleporting()
{

	CVector vec;
	vec.x = *(float *)0x77D770 * -1;
	vec.y = *(float *)0x77D774 * -1;
	vec.z = *(float *)0x77D778 * -1;
	WriteDebug(22, "Press SPACE to teleport");

	if (KeyHit(VK_SPACE))
	{
		// MoveEntity
		(*(void(__thiscall **)(int, CVector *, signed int))(*(int *)*(int*)0x789490 + 60))(*(int*)0x789490, &vec, 1);
		FreeCamera ^= 1;
	}
}

void GivePlayerWeapon(int item, bool firearm, const char* record)
{

	CEntity* plr = FindPlayer();
	if (GetEntity(record))
	{
		CreateInventoryItem(plr, item, true);
		if (firearm == true) AddAmmoToInventoryWeapon(item, 150);
	}
	else WriteDebug(22, "Item does not exist here!");
}