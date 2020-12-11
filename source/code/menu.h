#pragma once
#include <vector>
#include <functional>


struct EMenuPage {
	int         iStart;
	int         iEnd;
};

struct EMenuItem {
	std::string                      name;
	bool                             bIsWeapon;
	bool                             bIsFunction;
	bool                             bIsCharToggle;
	bool                             bIsShortToggle;
	bool                             bIsIntegerToggle;
	int                              iWeaponID;
	char*                            ptrCharValue;
	short*                           ptrShortValue;
	int*                             ptrIntValue;
	std::function<void()>            fFunc;
	// todo: add value items
};

struct EMenuCategory {
	std::string            strName;
	int                    iID;
	bool                   bHasItems;
	bool                   bIsWeapon;
	std::vector<EMenuItem> vItems;
	std::vector<EMenuItem> vWeapons;
	std::vector<EMenuPage> vPages;
	bool                   bHasBeenWeaponsPopulated;
	bool                   bHaveBeenPagesCalculated;
	int                    iPages;
};

class EMenu {
private:
	bool bDisplayMenu;
	bool bCategoryOpen;
	bool bNavigatingInCategory;
	bool bPressedEnter;
	bool bIsHoldingMenu;

	int  iCurrentItem;
	int  iActualItemID;
	int  iCurrentPage;
	int  iCurrentCategory;
	int  iBaseCategoryID;
	int  iTotalItems;

	std::vector<EMenuItem>     vTempItems;
	std::vector<EMenuPage>     vTempPages;
	std::vector<EMenuItem>     vTempWeapons;
	std::vector<EMenuCategory> vCategories;
public:

	// settings
	int  KeyEnableMenu;
	int  KeyQuickCameraMain;
	int  KeyQuickCameraSub;
	int  KeyQuickCameraTeleport;
	int  KeyMenuExecute;
	int  KeyMenuGoBack;
	int  KeyMenuItemUP;
	int  KeyMenuItemDOWN;
	int  KeyMenuItemLEFT;
	int  KeyMenuItemRIGHT;
	int  KeySlowMotion;
	int  SlowMotionPressValue;



	void Initialize();
	void ProcessMenu();
	void ProcessToggle();
	void ProcessControls();
	void DrawMenu();
	void ProcessEnter();
	void ProcessFastCam();
	// menu stuff
	void AddCategory(std::string name, bool isWeapon = false);
	void AddItem(std::string name, bool isChar, bool isShort, bool isInt, bool isFunc, bool isWeapon, int weapID, char* ptrChar, short* ptrShort, int* ptrInt, std::function<void()> func);
	void AddWeaponEntry(int weaponID);
	void AddToggleCharEntry(std::string name, char* ptr);
	void AddToggleIntEntry(std::string name, int* ptr);
	// todo
	void AddFunctionEntry(std::string name, std::function<void()> func);
};


void ResetTimer();
std::string GetStatusAsString(int value);
void __fastcall HookVisibility(int ptr);
extern EMenu TheMenu;

void SetSpeed10();
void SetSpeed25();
void SetSpeed50();
void SetSpeed75();
void SetSpeedDefault();

void SetSpeed(int speed);
