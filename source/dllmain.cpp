// dllmain.cpp : Defines the entry point for the DLL application.

#include "common.h"
#include "calling.h"
#include "mh2.h"


#define MENU_PAGES 4
#define MENU_PAGE_ENTRY 20




// menu vars
int MenuPosition = 0;
int DisplayMenu = 0;
int CurrentPage = 0;


// function vars
int EnableGodMode = 0;
int EnableNoClip = 0;
int EnableCameraTeleportation = 1;
int EnableFunMode = 0;

std::string menuEntries[200] = {
	"  Spawn: Colt Commando",
	"  Spawn: Crowbar",
	"  Spawn: Shovel",
	"  Spawn: Fire Axe",
	"  Spawn: Shard",  
	"  Spawn: Wire",  
	"  Spawn: Syringe",  
	"  Spawn: Glock",  
	"  Spawn: Desert Eagle",
	"  Spawn: Uzi",
	"  Spawn: 6Shooter",
	"  Spawn: Shotgun",
	"  Spawn: Shotgun + Torch",
	"  Spawn: Sawnoff",
	"  Spawn: Tranq Rifle",
	"  Spawn: Sniper Rifle",
	"  Spawn: SledgeHammer",
	"  Spawn: Stunprod",
	"  Spawn: HedgeTrimmer",
	"  Spawn: Wooden Bat",
	"  Spawn: Katana", 
	// Page 2
	"  Spawn: Mace",
	"  Spawn: Pen",
	"  Spawn: Bag",
	"  Spawn: Milkbottle",
	"  Spawn: Newspaper", 
	"  Spawn: Dildo", 
	"  Spawn: Hacksaw",
	"  Spawn: Razor", 
	"  Spawn: Sickle",
	"  Spawn: Nightstick",
	"  Spawn: Pliers",
	"  Spawn: Torch",
	"  Spawn: Flaregun",
	"  Spawn: Saw",
	"  Spawn: Crossbow",
	"  Spawn: Blowtorch",
	"  Spawn: Can",
	"  Spawn: Bottle",
	"  Spawn: Brick",
	"  Spawn: Golfball",
	"  Spawn: Acidbottle",
	// Page 3
	"  Spawn: Porn",
	"  Spawn: Cash",
	"  Spawn: Uzi + Torch" ,
	"  Spawn: Metal hook",
	"  Spawn: Matchbook", 
	"  Spawn: 1H Firearm",  
	"  Spawn: 2H Firearm", 
	"  Spawn: Hammer", 
	"  Spawn: Cleaver",
	"  Spawn: Small Bat",
	"  Spawn: Spiked Bat",
	"  Spawn: Metal Bat",
	"  Spawn: Icepick",
	"  Spawn: Axe",
	"  Spawn: Nail Gun",
	"  Spawn: Knife",
	"  Spawn: Chainsaw",
	"  Spawn: Chainsaw Player",
	"  Spawn: Machete",
	"  Spawn: Silenced Sniper Rifle",
	"  Spawn: Wooden Spike",
	// Page 4 
	"  Player: God Mode =      ",
	"  Other: Shadow Cameras Check =      ",
	"  Other: Unknown MS =       ",
	"  Other: Memory Used  =      ",
	"  Other: Force Small Screen =      ",
	"  Other: Freeze World =      ",
	"  Other: Normal Blood (false - flowers) =      ",
	"  Other: Fun Mode =      ",
	"  Other: Quick Weapon Select =      ",
	"  Other: Free Camera =      ",
	"  Player: NoClip (beta)  =     ",
	"  Other: Allow Teleportation Free Cam =      ",
	"  Player: Explode",
	"  Empty",
	"  Empty",
	"  Empty",
	"  Empty",
	"  Empty",
	"  Empty",
	"  Empty",
	"  Empty", 
	// Page 5
	"  Empty_page5_0",
	"  Empty_page5_1",
	"  Empty_page5_2",
	"  Empty_page5_3",
	"  Empty_page5_4", 
	"  Empty_page5_5", 
	"  Empty_page5_6", 
	"  Empty_page5_7", 
	"  Empty_page5_8",
	"  Empty_page5_9",
	"  Empty_page5_10",
	"  Empty_page5_11",
	"  Empty_page5_12",
	"  Empty_page5_13",
	"  Empty_page5_14",
	"  Empty_page5_15",
	"  Empty_page5_16",
	"  Empty_page5_17",
	"  Empty_page5_18",
	"  Empty_page5_19",
	"  Empty_page5_20", 

};



void Init()
{
	while (true)
	{
		if (KeyHit(VK_F1)) DisplayMenu = 1;
		if (KeyHit(VK_F2)) DisplayMenu = 0;

		// check if menu active, is player alive or does player actually exist
		if (DisplayMenu)
		{
			if (*(int*)0x75F204 || !IsAlive(FindPlayer()) || !FindPlayer())
			{
				WriteDebug(22, "ERROR: Can't use menu now!");
				DisplayMenu = false;
			}
		}


		if (FindPlayer())
		{
			if (!IsAlive(FindPlayer()))
			{
				FreeCamera = false;
				EnableNoClip = false;
			}
		}

		if (EnableGodMode && FindPlayer())
			SetHunterHideHealth(FindPlayer(), 120.0f);

		if (FreeCamera)
			EnableNoClip = false;

		if (EnableCameraTeleportation && FreeCamera && FindPlayer() && IsAlive(FindPlayer()))
		{
			EnableNoClip = false;
			CameraTeleporting();
		}

		if (EnableFunMode == 1)
			*(int*)0x76BE40 = 32;
		else
			*(int*)0x76BE40 = 0;

		if (EnableNoClip && FindPlayer() && IsAlive(FindPlayer()))
		{
			NoClip();
			EnableCameraTeleportation = false;
			FreeCamera = false;
		}
		
		if (DisplayMenu && FindPlayer() && IsAlive(FindPlayer()))
		{

			// decrease WriteDebug display time
			Memory::VP::Patch<char>(0x53D8DC, 6);
			WriteDebug(23, "Page %d/%d   ermaccer / dixmor-hospital.com", CurrentPage + 1, MENU_PAGES);

			if (KeyHit(VK_RIGHT)) {
				Sleep(130); CurrentPage += 1;
			}

			if (KeyHit(VK_LEFT)) {
				Sleep(130); CurrentPage -= 1;
			}
			if (KeyHit(VK_UP)) {
				Sleep(100); MenuPosition -= 1;
			}
			if (KeyHit(VK_DOWN)) {
				Sleep(100); MenuPosition += 1;
			}


			if (CurrentPage > MENU_PAGES - 1) CurrentPage = 0;
			if (CurrentPage < 0) CurrentPage = MENU_PAGES - 1;
			if (MenuPosition > MENU_PAGE_ENTRY) MenuPosition = 0;
			if (MenuPosition < 0) MenuPosition = MENU_PAGE_ENTRY;

			// add ->
			// also add true/false for toggle entries

			for (int i = 0; i < MENU_PAGE_ENTRY + 1; i++)
			{
				int number = i;
				switch (CurrentPage)
				{
				case 1:
					number += 21;
					break;
				case 2:
					number += 41;
					break;
				case 3:
					number += 63;
					break;
				}
				if (CurrentPage == 3)
				{
				 menuEntries[63].replace(menuEntries[63].length() - 5,5,GetTrueFalse(EnableGodMode));
				 menuEntries[64].replace(menuEntries[64].length() - 5, 5, GetTrueFalse(*(int*)0x75B334));
				 menuEntries[65].replace(menuEntries[65].length() - 5, 5, GetTrueFalse(*(int*)0x75B52C));
				 menuEntries[66].replace(menuEntries[66].length() - 5, 5, GetTrueFalse(*(int*)0x75B300));
				 menuEntries[67].replace(menuEntries[67].length() - 5, 5, GetTrueFalse(*(char*)0x79D0E4));
				 menuEntries[68].replace(menuEntries[68].length() - 5, 5, GetTrueFalse(*(int*)0x78949C));
				 menuEntries[69].replace(menuEntries[69].length() - 5, 5, GetTrueFalse(*(char*)0x6B26E5));
				 menuEntries[70].replace(menuEntries[70].length() - 5, 5, GetTrueFalse(EnableFunMode));
				 menuEntries[71].replace(menuEntries[71].length() - 5, 5, GetTrueFalse(*(char*)0x76E5B3));
				 menuEntries[72].replace(menuEntries[72].length() - 5, 5, GetTrueFalse(*(int*)0x7894A4));
				 menuEntries[73].replace(menuEntries[73].length() - 5, 5, GetTrueFalse(EnableNoClip));
				 menuEntries[74].replace(menuEntries[74].length() - 5, 5, GetTrueFalse(EnableCameraTeleportation));
				}
				
				if (MenuPosition == i) menuEntries[number].replace(0, 2, "->");
				else  menuEntries[number].replace(0, 2, "  ");


			}

			// print entries

			for (int i = 0; i < MENU_PAGE_ENTRY + 1; i++)
			{
				int number = i;
				switch (CurrentPage)
				{
				case 1:
					number += 21;
					break;
				case 2:
					number += 41;
					break;
				case 3:
					number += 63;
					break;
				}
				WriteDebug(i,menuEntries[number].c_str());
			}
			
			// functions
			if (KeyHit(VK_RETURN))
			{
				// TODO: Enum all weapons
				switch (CurrentPage)
				{
				case 0:
					switch (MenuPosition)
					{
					case 0:
						GivePlayerWeapon(CT_COLT_COMMANDO, true, "C_Commando_(CT)");
						break;
					case 1:
						GivePlayerWeapon(CT_CROWBAR, false, "Crowbar_(CT)");
						break;
					case 2:
						GivePlayerWeapon(CT_SHOVEL, false, "Shovel_(CT)");
						break;
					case 3:
						GivePlayerWeapon(CT_FIRE_AXE, false, "Fire_Axe_(CT)");
						break;
					case 4:
						GivePlayerWeapon(19, false, "Shard_(CT)");
						break;
					case 5:
						GivePlayerWeapon(92, false, "Wire_(CT)");
						break;
					case 6:
						GivePlayerWeapon(113, false, "Syringe_(CT)");
						break;
					case 7:
						GivePlayerWeapon(41, true, "Glock_(CT)");
						break;
					case 8:
						GivePlayerWeapon(48, true, "Desert_Eagle_(CT)");
						break;
					case 9:
						GivePlayerWeapon(44, true, "Uzi_(CT)");
						break;					
					case 10:					
						GivePlayerWeapon(40, true, "6Shooter_(CT)");
						break;					
					case 11:					
						GivePlayerWeapon(46, true, "Shotgun_(CT)");
						break;					
					case 12:					
						GivePlayerWeapon(47, true, "Shotgun_Torch_(CT)");
						break;					
					case 13:					
						GivePlayerWeapon(52, true, "SawnOff_Shotgun_(CT)");
						break;					
					case 14:					
						GivePlayerWeapon(51, true, "Tranq_Rifle_(CT)");
						break;
					case 15:
						GivePlayerWeapon(50, true, "Sniper_Rifle_(CT)");
						break;
					case 16:
						GivePlayerWeapon(115, false, "SledgeHammer_(CT)");
						break;
					case 17:
						GivePlayerWeapon(116, false, "Stunprod_(CT)");
						break;
					case 18:
						GivePlayerWeapon(124, false, "Hedge_Trimmer_(CT)");
						break;
					case 19:
						GivePlayerWeapon(36, false, "W_B_Bat_(CT)");
						break;
					case 20:
						GivePlayerWeapon(137, false, "katana(CT)");
						break;
					default:
						WriteDebug(22, "ERROR: This button is not programmed, yet!");
						break;
					}
				    break;
				case 1:
					switch (MenuPosition)
					{
					case 0:
						GivePlayerWeapon(123, false, "Mace_(CT)");
						break;
					case 1:
						GivePlayerWeapon(117, false, "Pen_(CT)");
						break;
					case 2:
						GivePlayerWeapon(60, false, "Bag_(CT)");
						break;
					case 3:
						GivePlayerWeapon(135, false, "milkbottle(CT)");
						break;
					case 4:
						GivePlayerWeapon(134, false, "newspaper(CT)");
						break;
					case 5:
						GivePlayerWeapon(136, false, "dildo(CT)");
						break;
					case 6:
						GivePlayerWeapon(138, false, "hacksaw(CT)");
						break;
					case 7:
						GivePlayerWeapon(121, false, "CUT_THROAT_RAZOR_(CT)");
						break;
					case 8:
						GivePlayerWeapon(27, false, "Sickle_(CT)");
						break;
					case 9:
						GivePlayerWeapon(28, false, "NightStick_(CT)");
						break;
					case 10:
						GivePlayerWeapon(34, false, "Pliers_(CT)");
						break;
					case 11:
						GivePlayerWeapon(6, false, "Torch_(CT)");
						break;
					case 12:
						GivePlayerWeapon(127, true, "FlareGun_(CT)");
						break;
					case 13:
						GivePlayerWeapon(126, false, "Circular_Saw_(CT)");
						break;
					case 14:
						GivePlayerWeapon(131, true, "Crossbow_(CT)");
						break;
					case 15:
						GivePlayerWeapon(122, false, "Blowtorch_(CT)");
						break;
					case 16:
						GivePlayerWeapon(93, false, "Can_(CT)");
						break;
					case 17:
						GivePlayerWeapon(22, false, "Bottle_(CT)");
						break;
					case 18:
						GivePlayerWeapon(58, false, "Half_Brick_(CT)");
						break;
					case 19:
						GivePlayerWeapon(139, false, "GolfBall_(CT)");
						break;
					case 20:
						GivePlayerWeapon(118, false, "AcidBottle_(CT)");
						break;
					default:
						WriteDebug(22, "ERROR: This button is not programmed, yet!");
						break;
					}
					break;
				case 2:
					switch (MenuPosition)
					{
					case 0:
						GivePlayerWeapon(141, false, "Porn_(CT)");
						break;
					case 1:
						GivePlayerWeapon(140, false, "Cash_Bundle_(CT)");
						break;
					case 2:
						GivePlayerWeapon(45, true, "Uzi_Torch_(CT)");
						break;
					case 3:
						GivePlayerWeapon(125, false, "MetalHook_(CT)");
						break;
					case 4:
						GivePlayerWeapon(142, false, "Matchbook_(CT)");
						break;
					case 5:
						GivePlayerWeapon(119, true, "1HFirearm_(CT)");
						break;
					case 6:
						GivePlayerWeapon(120, true, "2HFirearm_(CT)");
						break;
					case 7:
						GivePlayerWeapon(99, false, "Hammer_(CT)");
						break;
					case 8:
						GivePlayerWeapon(24, false, "Cleaver_(CT)");
						break;
					case 9:
						GivePlayerWeapon(33, false, "Small_Bat_(CT)");
						break;
					case 10:
						GivePlayerWeapon(39, false, "W_B_Bat_Nails_(CT)");
						break;
					case 11:
						GivePlayerWeapon(35, false, "M_B_Bat_(CT)");
						break;
					case 12:
						GivePlayerWeapon(31, false, "IcePick_(CT)");
						break;
					case 13:
						GivePlayerWeapon(30, false, "Axe_(CT)");
						break;
					case 14:
						GivePlayerWeapon(91, true, "Nail_Gun_(CT)");
						break;
					case 15:
						GivePlayerWeapon(18, false, "Hunt_Knife_(CT)");
						break;
					case 16:
						GivePlayerWeapon(90, false, "Chainsaw_(CT)");
						break;
					case 17:
						GivePlayerWeapon(110, false, "Chainsaw_Player_(CT)");
						break;
					case 18:
						GivePlayerWeapon(32, false, "Machete_(CT)");
						break;
					case 19:
						GivePlayerWeapon(95, false, "Sniper_Rifle_Silenced_(CT)");
						break;
					case 20:
						GivePlayerWeapon(94, false, "Wooden_Spike_(CT)");
						break;
					default:
						WriteDebug(22, "ERROR: This button is not programmed, yet!");
						break;
					}
					break;
				case 3:
					switch (MenuPosition)
					{
					case 0:
						EnableGodMode ^= 1;
						Sleep(130);
						break;
					case 1:
						ShadowCamerasCheck ^= 1;
						Sleep(130);
						break;
					case 2:
						*(int*)0x75B52C ^= 1;
						*(int*)0x75B2FC ^= 1;
						Sleep(130);
						break;
					case 3:
						MemoryUsed ^= 1;
						Sleep(130);
						break;
					case 4:
						*(char*)0x79D0E4 ^= 1;
						Sleep(130);
						break;
					case 5:
						FreezeWorld ^= 1;
						Sleep(130);
						break;
					case 6:
						*(char*)0x6B26E5 ^= 1;
						Sleep(130);
						break;
					case 7:
						EnableFunMode ^= 1;
						Sleep(130);
						break;
					case 8:
						*(char*)0x76E5B3 ^= 1;
						Sleep(130);
						break;
					case 9:
						*(int*)0x7894A4 ^= 1;
						Sleep(130);
						break;
					case 10:
						EnableNoClip ^= 1;
						Sleep(130);
						break;
					case 11:
						EnableCameraTeleportation ^= 1;
						Sleep(130);
						break;
					default:
						WriteDebug(22, "ERROR: This button is not programmed, yet!");
						break;
					}
					break;

				}
			}
		}
		Sleep(1);
	}
}




extern "C"
{
	__declspec(dllexport) void InitializeASI()
	{
		CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(Init), nullptr, 0, nullptr);;
	}
}


