#pragma once
#include <memory>
#include <string>
#include <iostream>
#include <functional>

#include "IniReader.h"
#define MENU_PAGES 4
#define MENU_PAGE_ENTRY 20


struct MenuFunction {
	std::string                       name;
	std::function<void()>             func;
	bool                              toggle;
	int*                              addr;
	char*                             addr_small;
	bool                              hasfunction;
	bool                              isWeapon;
	bool                              isChar;
	std::string                       record;
	bool                              isFirearm;
	int                               weaponId;
};




class CMenu {

	int displayMenu = 0;
	int currentPage = 0;
	int menuPosition = 0;
	int lastEntry = 0;
	std::unique_ptr<MenuFunction[]> menuEntries;

	// menu settings
	bool displayWeaponAvailable;
	bool displayBackgroundBox;
	int  menuKey;

public:
	void InitMenu();
	void ProcessMenu();
	void ToggleMenu();
	void RenderMenu();
	void Control();
	void AddFunction(std::string name, std::function<void()> func, bool toggle, int* addr, bool has_func, char* recordname, int weaponid, bool isweapon, bool isfirearm, char* addr_sm, bool is_char);
	void CallFunction(std::string name, std::function<void()> func);
	void CreateWeaponEntry(std::string name, int id, char* record, bool firearm);
	void ToggleValue(std::string name, int* value);
	void ToggleValueChar(std::string name, char* value);
	int  GetFunctionsAmount();
	

};