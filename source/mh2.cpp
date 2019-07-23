#include "mh2.h"


CEntity * GetEntity(const char * name)
{
	return CallAndReturn<CEntity*, 0x4E9130, const char*>(name);
}

void CreateInventoryItem(CEntity * ent, int item, bool b1)
{
	CallMethod<0x4F6500, CEntity*, int, bool>(ent, item, b1);
}

void AddAmmoToInventoryWeapon(int item, int amount)
{
	// using direct player pointer, not any entity
	// as spawner gives stuff to player anwyay
	int v0 = *(int*)(*(int*)0x789490 + 444);
	int v1 = ((int(__thiscall*)(int, int))0x5726F0)(v0, item);

	((void(__thiscall*)(int, int))0x5D2B30)(*(int*)(v1 + 516), amount);
}

void SetHunterHideHealth(CEntity * ent, float health)
{
	CallMethod<0x4E1D20, CEntity*, float>(ent, health);
}

CEntity* FindPlayer()
{
	return *(CEntity**)0x789490;
}

// script space only
CEntity * FindEntity(const char * name)
{
	return CallAndReturn<CEntity*, 0x4EC530, const char*>(name);
}

bool IsAlive(CEntity * ent)
{
	if (ent->health > 0.0)
		return true;
	else
		return false;
}


