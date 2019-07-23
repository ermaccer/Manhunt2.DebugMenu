#pragma once
#include "calling.h"
struct CVector {
	float x, y, z;
};

struct CEntity{
	//todo: pretty much everything
	char field[124];
	float health;
};




CEntity* GetEntity(const char* name);
void     CreateInventoryItem(CEntity* ent, int item, bool b1);
void     AddAmmoToInventoryWeapon(int item, int amount);
void     SetHunterHideHealth(CEntity* ent, float health);
CVector  GetEntityPosition();
CEntity* FindPlayer();
CEntity* FindEntity(const char* name);
bool     IsAlive(CEntity* ent);


template<typename ...Args>
void WriteDebug(int line, const char * msg, Args ...args)
{
	Call<0x53D8D0, int, const char*, Args...>(line, msg, args...);
}

// todo: fill up
enum Item {
	CT_CROWBAR = 26,
	CT_FIRE_AXE = 37,
	CT_COLT_COMMANDO = 49,
	CT_SHOVEL = 114
};

