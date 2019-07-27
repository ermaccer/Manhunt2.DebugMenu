// dllmain.cpp : Defines the entry point for the DLL application.
#include "code\mh2.h"
#include "code\menu.h"
#include "code\debug.h"
#include "code\MemoryMgr.h"
#include <string>



#include "stdafx.h"



int& FreezeWorld = *(int*)0x78949C;
int& FreeCamera = *(int*)0x7894A4;
int& ShadowCamerasCheck = *(int*)0x75B334;
char& QuickSelect = *(char*)0x76E5B3;
char& FlowerBlood = *(char*)0x6B26E5;

int EnableGodMode = 0;
int EnableTeleportCamera = 1;
int EnableFunMode = 0;


void Init()
{

	// init menu
	CMenu* menu = new CMenu;
	menu->InitMenu();

	// init functions

	// Firearms
	menu->CreateWeaponEntry("Spawn: Colt Commando  ", 49, "C_Commando_(CT)", true);
	menu->CreateWeaponEntry("Spawn: Crossbow  ", 131, "Crossbow_(CT)", true);
	menu->CreateWeaponEntry("Spawn: Sniper Rifle", 50, "Sniper_Rifle_(CT)", true);
	menu->CreateWeaponEntry("Spawn: Sniper Rifle (Silenced)", 50, "Sniper_Rifle_Silenced_(CT)", true);
	menu->CreateWeaponEntry("Spawn: Tranq Rifle", 51, "Tranq_Rifle_(CT)", true);
	menu->CreateWeaponEntry("Spawn: Shotgun", 46, "Shotgun_(CT)", true);
	menu->CreateWeaponEntry("Spawn: Shotgun (Torch)", 47, "Shotgun_Torch_(CT)", true);
	menu->CreateWeaponEntry("Spawn: SawnOff Shotgun", 52, "SawnOff_Shotgun_(CT)", true);
	menu->CreateWeaponEntry("Spawn: Desert Eagle", 48, "Desert_Eagle_(CT)", true);
	menu->CreateWeaponEntry("Spawn: Uzi", 44, "Uzi_(CT)", true);
	menu->CreateWeaponEntry("Spawn: Uzi (Torch)", 45, "Uzi_Torch_(CT)", true);
	menu->CreateWeaponEntry("Spawn: Glock", 41, "Glock_(CT)", true);
	menu->CreateWeaponEntry("Spawn: 6Shooter", 40, "Glock_(CT)", true);
	menu->CreateWeaponEntry("Spawn: Flare Gun", 127, "FlareGun_(CT)", true);
	menu->CreateWeaponEntry("Spawn: Nail Gun", 91, "Nail_Gun_(CT)", true); // mh1
	// melee
	menu->CreateWeaponEntry("Spawn: Shovel", 114, "Shovel_(CT)", false);
	menu->CreateWeaponEntry("Spawn: Fire Axe", 37, "Fire_Axe_(CT)", false);
	menu->CreateWeaponEntry("Spawn: Baseball Bat", 36, "W_B_Bat_(CT)", false);
	menu->CreateWeaponEntry("Spawn: Hedge Trimmers", 124, "Hedge_Trimmer_(CT)", false);
	menu->CreateWeaponEntry("Spawn: Katana", 124, "katana(CT)", false);
	menu->CreateWeaponEntry("Spawn: Sledgehammer", 115, "SledgeHammer_(CT)", false);
	menu->CreateWeaponEntry("Spawn: Stunprod", 116, "Stunprod_(CT)", false);
	menu->CreateWeaponEntry("Spawn: Mace", 123, "Mace_(CT)", false);
	menu->CreateWeaponEntry("Spawn: Crowbar", 26, "Crowbar_(CT)", false);
	menu->CreateWeaponEntry("Spawn: Torch", 6, "Torch_(CT)", false);
	menu->CreateWeaponEntry("Spawn: Sickle", 27, "Sickle_(CT)", false);
	menu->CreateWeaponEntry("Spawn: Pliers",34, "Pliers_(CT)", false);
	menu->CreateWeaponEntry("Spawn: Hacksaw", 138, "hacksaw(CT)", false);
	menu->CreateWeaponEntry("Spawn: NightStick", 28, "NightStick_(CT)", false);
	menu->CreateWeaponEntry("Spawn: Razor", 121, "CUT_THROAT_RAZOR_(CT)", false);
	menu->CreateWeaponEntry("Spawn: Dildo", 136, "dildo(CT)", false);
	menu->CreateWeaponEntry("Spawn: Saw", 126, "Circular_Saw_(CT)", false);
	menu->CreateWeaponEntry("Spawn: Blowtorch", 122, "Blowtorch_(CT)", false);
	menu->CreateWeaponEntry("Spawn: Pen", 117, "Pen_(CT)", false);
	menu->CreateWeaponEntry("Spawn: Bag", 60, "Bag_(CT)", false);
	menu->CreateWeaponEntry("Spawn: Milkbottle", 135, "milkbottle(CT)", false);
	menu->CreateWeaponEntry("Spawn: Newspaper", 134, "newspaper(CT)", false);
	menu->CreateWeaponEntry("Spawn: Acidbottle", 118, "AcidBottle_(CT)", false);
	menu->CreateWeaponEntry("Spawn: Can", 93, "Can_(CT)", false);
	menu->CreateWeaponEntry("Spawn: Bottle", 22, "Bottle_(CT)", false);
	menu->CreateWeaponEntry("Spawn: Brick", 58, "Half_Brick_(CT)", false);
	menu->CreateWeaponEntry("Spawn: Golfball", 139, "GolfBall_(CT)", false);
	menu->CreateWeaponEntry("Spawn: Cash", 140, "Cash_Bundle_(CT)", false);
	menu->CreateWeaponEntry("Spawn: Porn", 141, "Cash_Bundle_(CT)", false);
	menu->CreateWeaponEntry("Spawn: Shard", 19, "Shard_(CT)", false);
	menu->CreateWeaponEntry("Spawn: Wire", 92, "Wire_(CT)", false);
	menu->CreateWeaponEntry("Spawn: Syringe", 113, "Syringe_(CT)", false);
	menu->CreateWeaponEntry("Spawn: Metal Hook", 125, "MetalHook_(CT)", false);
	menu->CreateWeaponEntry("Spawn: 1H Firearm", 119, "1HFirearm_(CT)", true);
	menu->CreateWeaponEntry("Spawn: 2H Firearm", 119, "2HFirearm_(CT)", true);
	menu->CreateWeaponEntry("Spawn: Metal Hook", 125, "MetalHook_(CT)", false);
	// manhunt leftovers
	menu->CreateWeaponEntry("Spawn: Hammer", 99, "Hammer_(CT)", false);
	menu->CreateWeaponEntry("Spawn: Cleaver", 24, "Cleaver_(CT)", false);
	menu->CreateWeaponEntry("Spawn: Small Bat", 33, "Small_Bat_(CT)", false);
	menu->CreateWeaponEntry("Spawn: Spiked Bat", 39, "W_B_Bat_Nails_(CT)", false);
	menu->CreateWeaponEntry("Spawn: Metal Bat", 35, "M_B_Bat_(CT)", false);
	menu->CreateWeaponEntry("Spawn: Ice Pick", 31, "IcePick_(CT)", false);
	menu->CreateWeaponEntry("Spawn: Axe", 30, "Axe_(CT)", false);
	menu->CreateWeaponEntry("Spawn: Knife", 18, "Hunt_Knife_(CT)", false);
	menu->CreateWeaponEntry("Spawn: Machete", 32, "Machete_(CT)", true);
	menu->CreateWeaponEntry("Spawn: Wooden Spike", 94, "Wooden_Spike_(CT)", true);
	menu->CreateWeaponEntry("Spawn: Chainsaw", 90, "Chainsaw_(CT)", true);
	menu->CreateWeaponEntry("Spawn: Chainsaw Player", 110, "Chainsaw_Player_(CT)", true);
	// toggles
	menu->ToggleValue("Other: Freeze World", &FreezeWorld);
	menu->ToggleValue("Other: Free Camera", &FreeCamera);
	menu->ToggleValue("Other: Teleporting Camera", &EnableTeleportCamera);
	menu->ToggleValue("Other: FunMode", &EnableFunMode);
	menu->ToggleValueChar("Other: Quick Select", &QuickSelect);
	menu->ToggleValueChar("Other: Blood Type (false - flowers)", &FlowerBlood);
	menu->ToggleValue("Player: God Mode", &EnableGodMode);




	while (true)
	{
		Sleep(1);
		menu->ProcessMenu();

		if (EnableGodMode)
			SetHunterHideHealth(FindPlayer(), 120.0f);

		if (EnableTeleportCamera && FreeCamera)
			CameraTeleporting();

		if (EnableFunMode == 1)
			*(int*)0x76BE40 = 32;
		else
			*(int*)0x76BE40 = 0;


	}
}


extern "C"
{
	__declspec(dllexport) void InitializeASI()
	{
		if (*(int*)0x63BC93 != (unsigned int)'hnaM')
		{
			MessageBoxA(0, "Invalid executable!", 0, 0);
		}
		else CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(Init), nullptr, 0, nullptr);;
	}
}


