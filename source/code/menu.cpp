#include "menu.h"
#include "..\stdafx.h"
#include "MemoryMgr.h"
#include "debug.h"
#include "mh2.h"

void CMenu::InitMenu()
{
	// for console output
	printf("debug menu init \n");
	menuEntries = std::make_unique<MenuFunction[]>((MENU_PAGE_ENTRY * MENU_PAGES) + MENU_PAGES);

	CIniReader reader("");
	displayWeaponAvailable = reader.ReadBoolean("Settings", "DisplayWeaponAvailable", false);
	displayBackgroundBox = reader.ReadBoolean("Settings", "DisplayBackgroundBox", true);
	menuKey = reader.ReadInteger("Settings", "DebugMenuKey", VK_F1);
}

void CMenu::ProcessMenu()
{
	ToggleMenu();

	if (displayMenu == 0) return;

	if (*(int*)0x75F204 == 1 || !FindPlayer()) displayMenu = 0;


	if (displayMenu)
	{
		RenderMenu();
		Control();
	}

		

    	
}

void CMenu::ToggleMenu()
{
	if (KeyHit(menuKey))
	{
		displayMenu ^= 1;

		Memory::VP::Patch<char>(0x53D8DC, displayMenu == 1 ? 6 : 80);
		Sleep(130);
	}

}

void CMenu::RenderMenu()
{

	// arrow, true/false for toggles

	if (!displayBackgroundBox)
		Memory::VP::Patch<double>(0x65F1A0, -1.0);


	// disable menu if player ded

	if (!IsAlive(FindPlayer()))
		displayMenu = 0;

	for (int i = 0; i < MENU_PAGE_ENTRY + 1; i++)
	{
		int number = i;
		if (currentPage > 0)
			number += (MENU_PAGE_ENTRY * currentPage) + 1;

		// add arrow
		std::string entry;
		if (menuPosition == i) entry.append("->");
		else entry.append("  ");

		entry.append(menuEntries[number].name);

		
		
		if (menuEntries[number].isWeapon == true)
		{
			if (displayWeaponAvailable)
			{
				if (GetEntity(menuEntries[number].record.c_str()))
					entry.append(" + ");
				else entry.append(" - ");
			}

				
		}
		
		// true false
		if (menuEntries[number].toggle == true)
		{
			entry.append(" = ");
			if (menuEntries[number].isChar)
				entry.append(GetCharTrueFalse(*menuEntries[number].addr_small));
			else entry.append(GetTrueFalse(*menuEntries[number].addr));
		}
			

		WriteDebug(i, entry.c_str());
	}
#ifdef USE_DIXMOR
	WriteDebug(22, "Page %d/%d ermaccer / dixmor-hospital.com", currentPage + 1, MENU_PAGES);
#else
	WriteDebug(22, "Page %d/%d", currentPage + 1, MENU_PAGES);
#endif
}

void CMenu::Control()
{


	if (*(int*)0x75B334 == 1)
	{
		displayMenu = 0;
	}


	if (KeyHit(VK_UP))
	{
		menuPosition--;
		Sleep(100);
	}
	if (KeyHit(VK_DOWN))
	{
		menuPosition++;
		Sleep(100);
	}
	if (KeyHit(VK_LEFT))
	{
		menuPosition = 0;
		currentPage--;
		Sleep(130);
	}
	if (KeyHit(VK_RIGHT))
	{
		menuPosition = 0;
		currentPage++;
		Sleep(130);
	}


	if (currentPage > MENU_PAGES - 1) currentPage = 0;
	if (currentPage < 0) currentPage = MENU_PAGES - 1;
	if (menuPosition > MENU_PAGE_ENTRY) menuPosition = 0;
	if (menuPosition < 0) menuPosition = MENU_PAGE_ENTRY;
    
	if (KeyHit(VK_RETURN))
	{
		int number = menuPosition;
		if (currentPage > 0)
		    number += (MENU_PAGE_ENTRY * currentPage) + 1;

		if (!menuEntries[number].toggle)
		{
			if (menuEntries[number].isWeapon)
				GivePlayerWeapon(menuEntries[number].weaponId, menuEntries[number].record.c_str(), menuEntries[number].isFirearm);
			if (menuEntries[number].hasfunction)
				menuEntries[number].func();
		}


		if (menuEntries[number].toggle)
		{
			if (menuEntries[number].isChar)
				*menuEntries[number].addr_small ^= 1;
			else *menuEntries[number].addr ^= 1;
		    Sleep(130);
		}
	}

}

void CMenu::AddFunction(std::string name, std::function<void()> func, bool toggle, int * addr, bool has_func, char * recordname, int weaponid, bool isweapon, bool isfirearm, char* addr_sm, bool is_char)
{


	MenuFunction menfunc;
	menfunc.name = name;
	menfunc.func = func;
	menfunc.toggle = toggle;
	menfunc.addr = addr;
	menfunc.hasfunction = has_func;
	menfunc.weaponId = weaponid;
	menfunc.isWeapon = isweapon;
	menfunc.isFirearm = isfirearm;
	menfunc.record = recordname;
	menfunc.addr_small = addr_sm;
	menfunc.isChar = is_char;
	menuEntries[lastEntry] = menfunc;
	lastEntry++;
}

void CMenu::CallFunction(std::string name, std::function<void()> func)
{
	int temp;
	AddFunction(name, func, 0, &temp,true,"none",0,0,0,0,0);
}

void CMenu::CreateWeaponEntry(std::string name, int id, char* record, bool firearm)
{
	std::function<void()> dummy;
	AddFunction(name, dummy, false, 0, false, record, id, true, firearm, 0, 0);
}

void CMenu::ToggleValue(std::string name, int* value)
{
	std::function<void()> dummy;
	AddFunction(name, dummy, true, value, false, "none", 0, 0, 0, 0, 0);
}

void CMenu::ToggleValueChar(std::string name, char * value)
{
	std::function<void()> dummy;
	AddFunction(name, dummy, true, 0, false, "none", 0, 0, 0, value, true);
}

int CMenu::GetFunctionsAmount()
{
	return lastEntry;
}
