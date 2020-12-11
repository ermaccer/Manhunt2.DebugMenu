#include "menu.h"
#include "mh2.h"
#include "debug.h"
#include "MemoryMgr.h"
#include "IniReader.h"
#include <Windows.h>

using namespace Memory::VP;

// some mh2 variables

char& bQuickSelect = *(char*)0x76E5B3;
char& bFlowerBlood = *(char*)0x6B26E5;
char& bPlayerVisible = *(char*)0x6D02CD;
char& bTimer = *(char*)0x75B724;
char& bActivateTimer = *(char*)0x75B728;
char& bBodyCount = *(char*)0x75B734;

int&  iShadowCameras = *(int*)0x75B334;
int&  iMemoryUsed = *(int*)0x75B300;
int&  iCalibrationLines = *(int*)0x75B108;
int&  iFreezeWorld = *(int*)0x78949C;
int&  iFreeCamera = *(int*)0x7894A4;
int&  iPlayerMovement = *(int*)0x6B17C4;
int&  iTimeControl = *(int*)0x75B7CC;

int& iTimeStep = *(int*)0x695034;

// custom

int bPlayerInfiniteHealth = 0;
int bDisplayPlayerCoords = 0;
int bDisableAI = 0;
int bInfiniteAmmo = 0;
int bFunMode = 0;
int bFallDamage = 1;
int bSilenceWeapons = 0;
int bGiveMaxStars = 0;
int bGodMode = 0;
int bEnableKillCounter = 0;

static int iTimer = GetTickCount();
char msgBuffer[256];
char buffer[256];
EMenu TheMenu;

void EMenu::Initialize()
{
	bDisplayMenu = false;
	iCurrentItem = 0;
	iActualItemID = 0;
	iCurrentPage = 0;
	iCurrentCategory = 0;
	iBaseCategoryID = 0;
	iTotalItems = 0;
	bNavigatingInCategory = false;
	bCategoryOpen = false;
	bPressedEnter = false;
	bIsHoldingMenu = false;


	CIniReader ini("");

	KeyEnableMenu = ini.ReadInteger("Settings", "KeyEnableMenu", VK_F1);
	KeyQuickCameraMain = ini.ReadInteger("Settings", "KeyQuickCameraMain", VK_CONTROL);
	KeyQuickCameraSub = ini.ReadInteger("Settings", "KeyQuickCameraSub", 86);
	KeyQuickCameraTeleport = ini.ReadInteger("Settings", "KeyQuickCameraTeleport", VK_SPACE);
	KeyMenuExecute = ini.ReadInteger("Settings", "KeyMenuExecute", VK_RETURN);
	KeyMenuGoBack = ini.ReadInteger("Settings", "KeyMenuGoBack", VK_BACK);
	KeyMenuItemDOWN = ini.ReadInteger("Settings", "KeyMenuItemDown", VK_DOWN);
	KeyMenuItemUP = ini.ReadInteger("Settings", "KeyMenuItemUp", VK_UP);
	KeyMenuItemLEFT = ini.ReadInteger("Settings", "KeyMenuItemLeft", VK_LEFT);
	KeyMenuItemRIGHT = ini.ReadInteger("Settings", "KeyMenuItemRight", VK_RIGHT);
	KeySlowMotion = ini.ReadInteger("Settings", "KeySlowMotion", VK_F5);

	SlowMotionPressValue = 16;

	AddToggleIntEntry("Infinite Health", &bPlayerInfiniteHealth);
	AddToggleIntEntry("God Mode", &bGodMode);
	AddToggleIntEntry("Display Coordinates", &bDisplayPlayerCoords);
	AddToggleIntEntry("Fall Damage", &bFallDamage);
	AddFunctionEntry("Kill", KillPlayer);
	AddCategory("Player");
	// pistols
	AddWeaponEntry(CT_6SHOOTER);
	AddWeaponEntry(CT_GLOCK);

	AddWeaponEntry(CT_DESERT_EAGLE);
	AddWeaponEntry(CT_UZI);
	AddWeaponEntry(CT_UZI_TORCH);
	AddWeaponEntry(CT_NAILGUN);
	AddWeaponEntry(CT_TRANQ_RIFLE);
	AddWeaponEntry(CT_FLAREGUN);
	AddWeaponEntry(CT_1H_FIREARM);


	// rifles
	AddWeaponEntry(CT_SHOTGUN);
	AddWeaponEntry(CT_SHOTGUN_TORCH);
	AddWeaponEntry(CT_2H_FIREARM);
	AddWeaponEntry(CT_COLT_COMMANDO);
	AddWeaponEntry(CT_SNIPER_RIFLE);
	AddWeaponEntry(CT_CROSSBOW);
	AddWeaponEntry(CT_SAWNOFF);
	// melee
	AddWeaponEntry(CT_SHOVEL);
	AddWeaponEntry(CT_FIRE_AXE);
	AddWeaponEntry(CT_BASEBALL_BAT);
	AddWeaponEntry(CT_HEDGETRIMMER);
	AddWeaponEntry(CT_KATANA);
	AddWeaponEntry(CT_SLEDGEHAMMER);
	AddWeaponEntry(CT_STUNPROD);
	AddWeaponEntry(CT_MACE);
	AddWeaponEntry(CT_CROWBAR);
	AddWeaponEntry(CT_TORCH);
	AddWeaponEntry(CT_SICKLE);
	AddWeaponEntry(CT_PLIERS);
	AddWeaponEntry(CT_HACKSAW);
	AddWeaponEntry(CT_NIGHTSTICK);
	AddWeaponEntry(CT_CUT_THROAT_RAZOR);
	AddWeaponEntry(CT_DILDO);
	AddWeaponEntry(CT_CIRCULAR_SAW);
	AddWeaponEntry(CT_BLOWTORCH);
	AddWeaponEntry(CT_PEN);
	AddWeaponEntry(CT_MILKBOTTLE);
	AddWeaponEntry(CT_NEWSPAPER);
	AddWeaponEntry(CT_ACID_BOTTLE);
	AddWeaponEntry(CT_CAN);
	AddWeaponEntry(CT_BOTTLE);
	AddWeaponEntry(CT_BRICK_HALF);
	AddWeaponEntry(CT_GOLFBALL);
	AddWeaponEntry(CT_PORN);
	//AddWeaponEntry(CT_CASH);
	AddWeaponEntry(CT_WIRE);
	AddWeaponEntry(CT_SHARD);
	AddWeaponEntry(CT_SYRINGE);
	AddWeaponEntry(CT_METAL_HOOK);
	// manhunt leftovers
	AddWeaponEntry(CT_HAMMER);
	AddWeaponEntry(CT_CLEAVER);
	AddWeaponEntry(CT_SMALL_BAT);
	AddWeaponEntry(CT_BASEBALL_BAT_BLADES);
	AddWeaponEntry(CT_ICEPICK);
	AddWeaponEntry(CT_AXE);
	AddWeaponEntry(CT_KNIFE);
	AddWeaponEntry(CT_MACHETE);
	AddWeaponEntry(CT_WOODEN_SPIKE);
	AddWeaponEntry(CT_CHAINSAW);
	AddWeaponEntry(CT_CHAINSAW_PLAYER);
	AddWeaponEntry(CT_PIGSY_WIRE);
	AddWeaponEntry(CT_PIGSY_SHARD);
	AddCategory("Weapons", true);
	AddToggleCharEntry("Timer", &bTimer);
	AddToggleCharEntry("Body Count", &bBodyCount);
	AddToggleIntEntry("Enable Body Count",&bEnableKillCounter);
	AddCategory("HUD");
	AddFunctionEntry("Free", SetWeatherFree);
	AddFunctionEntry("Clear", SetWeatherClear);
	AddFunctionEntry("Cloudy", SetWeatherCloudy);
	AddFunctionEntry("Thunder", SetWeatherThunder);
	AddFunctionEntry("Rainy", SetWeatherRainy);
	AddFunctionEntry("Foggy", SetWeatherFoggy);
	AddFunctionEntry("Windy", SetWeatherWindy);
	AddCategory("Weather");
	AddFunctionEntry("Complete", CompleteLevel);
	AddFunctionEntry("Restart", RestartLevel);
	AddFunctionEntry("Fail", FailLevel);
	AddFunctionEntry("Give 5*", Hook5Stars);
	AddCategory("Level");
	AddToggleIntEntry("Enable", &iTimeControl);
	AddFunctionEntry("10%", SetSpeed10);
	AddFunctionEntry("25%", SetSpeed25);
	AddFunctionEntry("50%", SetSpeed50);
	AddFunctionEntry("75%", SetSpeed75);
	AddFunctionEntry("Default", SetSpeedDefault);
	AddCategory("Slowmotion");
	AddToggleCharEntry("Quick Select", &bQuickSelect);
	AddToggleCharEntry("Blood (false - flowers)", &bFlowerBlood);
	AddToggleIntEntry("Fun Mode", &bFunMode);
	AddToggleIntEntry("Disable AI", &bDisableAI);
	AddToggleIntEntry("Infinite Ammo", &bInfiniteAmmo);
	AddToggleIntEntry("Shadow Cameras Check", &iShadowCameras);
	AddToggleIntEntry("Mem. Used", &iMemoryUsed);
	AddToggleIntEntry("Calibration Lines", &iCalibrationLines);
	AddToggleIntEntry("Freeze World", &iFreezeWorld);
	AddToggleIntEntry("Free Camera", &iFreeCamera);
	AddToggleCharEntry("Player Visible", &bPlayerVisible);
	AddToggleIntEntry("Silence Weapons", &bSilenceWeapons);
	AddFunctionEntry("Change Difficulty to Sane", SetDifficultySane);
	AddFunctionEntry("Change Difficulty to Insane", SetDifficultyInsane);
	AddToggleIntEntry("Allow Controls", &iPlayerMovement);

	AddCategory("Misc.");

}

void EMenu::ProcessMenu()
{
	if (bPlayerInfiniteHealth)
	{
		if (FindPlayer())
		{
			SetHunterHideHealth(FindPlayer(), 120.0f);
		}
	}
	if (FindPlayer())
		SetEntityFlag(FindPlayer(), 0x100, bGodMode);
		
	if (bEnableKillCounter)
		Game::iBodyCounterKills = Game::iHuntersExecuted + Game::iHuntersKilled;


	if (iFreeCamera)
		CameraTeleporting();

	if (!bFallDamage)
	{
		Patch<int>(0x4E1D82, 0x75909090);
		Patch<int>(0x4E4AD7, 0x74909090);
	}
	else
	{
		Patch<int>(0x4E1D82, 0x757C5ED9);
		Patch<int>(0x4E4AD7, 0x747C5ED9);
	}

	if (bSilenceWeapons)
		Patch<char>(0x529105 + 1, 8);
	else
		Patch<char>(0x529105 + 1, 7);



	if (bFunMode)
		Patch<int>(0x76BE40, 32);
	else
		Patch<int>(0x76BE40, 0);

	if (bInfiniteAmmo)
		Patch<char>(0x604DFA + 3, 0);
	else
		Patch<char>(0x604DFA + 3, -1);
 

	ProcessFastCam();

	if (bDisplayPlayerCoords)
	{
		sprintf(buffer, "X: %.3f Y: %.3f Z: %.3f", *(float *)0x704F68, *(float *)0x704F6C, *(float *)0x704F70);
		SetDrawRGBA(0, 0, 0, 255);
		PrintText(buffer, 0.552f, 0, 0.7f, 0.7f, 0.0, FONT_TYPE_DEFAULT);
		SetDrawRGBA(255, 255, 255, 255);
		PrintText(buffer, 0.554f, 0, 0.7f, 0.7f, 0.0, FONT_TYPE_DEFAULT);
	}


	if (KeyHit(KeySlowMotion))
	{
		if (GetTickCount() - iTimer <= 240) return;
		iTimeControl ^= 1;
		iTimer = GetTickCount();

	}

	if (*(int*)0x75F204 == 1 || !FindPlayer()) bDisplayMenu = 0;

	ProcessToggle();
	



	if (bDisplayMenu)
	{
		DrawMenu();
		ProcessControls();
	}


}

void EMenu::ProcessToggle()
{
	if (KeyHit(KeyEnableMenu))
	{
		if (GetTickCount() - iTimer <= 240) return;
		iTimer = GetTickCount();
		bDisplayMenu ^= 1;
		iCurrentCategory = 0;
		iCurrentItem = 0;
		bCategoryOpen = false;
		bNavigatingInCategory = false;
		vCategories[iCurrentCategory].vPages.clear();
		vCategories[iCurrentCategory].vWeapons.clear();
		vTempPages.clear();
		vTempWeapons.clear();

	}
}

void EMenu::ProcessControls()
{

	if (bPressedEnter)
		ProcessEnter();

	if (KeyHit(KeyMenuItemUP))
	{


		if (GetTickCount() - iTimer <= 100) return;
		iTimer = GetTickCount();
		if (bCategoryOpen && vCategories[iCurrentCategory].bHasItems)
		{

			iCurrentItem--;
			if (iCurrentItem < 0)
				iCurrentItem = iTotalItems - 1;
		}

		else 
		    iCurrentCategory--;
	}

	if (KeyHit(KeyMenuItemDOWN))
	{


		if (GetTickCount() - iTimer <= 100) return;
		iTimer = GetTickCount();
		if (bCategoryOpen && vCategories[iCurrentCategory].bHasItems)
		{
			iCurrentItem++;
			if (iCurrentItem + 1 > iTotalItems)
				iCurrentItem = 0;

		}
		else 
		  iCurrentCategory++;
		

	}

	if (KeyHit(KeyMenuItemLEFT))
	{
		if (GetTickCount() - iTimer <= 100) return;
		iTimer = GetTickCount();
		iCurrentItem = 0;
		iCurrentPage--;
	}
	if (KeyHit(KeyMenuItemRIGHT))
	{
		if (GetTickCount() - iTimer <= 140) return;
		iTimer = GetTickCount();
		iCurrentItem = 0;
		iCurrentPage++;
	}

	if (!bCategoryOpen && !bNavigatingInCategory)
	{
		if (vCategories[iCurrentCategory].bHasItems && vCategories[iCurrentCategory].vItems.size() > 0)
		{
			if (KeyHit(KeyMenuExecute))
			{
				if (GetTickCount() - iTimer <= 140) return;
				iTimer = GetTickCount();
				if (vCategories[iCurrentCategory].bIsWeapon)
				{
					vCategories[iCurrentCategory].vWeapons.clear();
					vCategories[iCurrentCategory].bHasBeenWeaponsPopulated = false;

				}
				vTempPages.clear();
				vCategories[iCurrentCategory].vPages.clear();
				vCategories[iCurrentCategory].bHaveBeenPagesCalculated = false;
				bCategoryOpen = true;
				bPressedEnter = true;
				bNavigatingInCategory = true;
			}
		}

	}

	if (bCategoryOpen)
	{
		if (KeyHit(KeyMenuGoBack))
		{
			if (vCategories[iCurrentCategory].bIsWeapon)
			{
				vCategories[iCurrentCategory].vWeapons.clear();
				vTempWeapons.clear();
				vCategories[iCurrentCategory].bHasBeenWeaponsPopulated = false;

			}

			if (GetTickCount() - iTimer <= 140) return;
			iTimer = GetTickCount();
			bCategoryOpen = false;
			bNavigatingInCategory = false;
			vTempPages.clear();
			vCategories[iCurrentCategory].vPages.clear();
			vCategories[iCurrentCategory].bHaveBeenPagesCalculated = false;
			iCurrentItem = 0;
		}
	}

	if (bNavigatingInCategory && bCategoryOpen && !bPressedEnter)
	{
		if (KeyHit(KeyMenuExecute))
		{
			if (vCategories[iCurrentCategory].bIsWeapon && vCategories[iCurrentCategory].bHasBeenWeaponsPopulated)
			{
				int weapon = iCurrentItem + vCategories[iCurrentCategory].vPages[iCurrentPage].iStart;
				if (vCategories[iCurrentCategory].vWeapons[weapon].bIsWeapon)
					GivePlayerWeapon(vCategories[iCurrentCategory].vWeapons[weapon].iWeaponID);

			}
			if (vCategories[iCurrentCategory].vItems[iCurrentItem].bIsFunction)
			{
				int item = iCurrentItem + vCategories[iCurrentCategory].vPages[iCurrentPage].iStart;
				vCategories[iCurrentCategory].vItems[item].fFunc();
			}
			if (vCategories[iCurrentCategory].vItems[iCurrentItem].bIsCharToggle || vCategories[iCurrentCategory].vItems[iCurrentItem].bIsShortToggle
				|| vCategories[iCurrentCategory].vItems[iCurrentItem].bIsIntegerToggle)
			{
				int item = iCurrentItem + vCategories[iCurrentCategory].vPages[iCurrentPage].iStart;

				if (vCategories[iCurrentCategory].vItems[item].bIsCharToggle)
				{
					if (GetTickCount() - iTimer <= 140) return;
					iTimer = GetTickCount();
					*vCategories[iCurrentCategory].vItems[item].ptrCharValue ^= 1;
				}
				if (vCategories[iCurrentCategory].vItems[item].bIsIntegerToggle)
				{
					if (GetTickCount() - iTimer <= 140) return;
					iTimer = GetTickCount();
					*vCategories[iCurrentCategory].vItems[item].ptrIntValue ^= 1;
				}
			}
		}
	}



	if (iCurrentPage + 1 > vCategories[iCurrentCategory].vPages.size()) iCurrentPage = 0;
	if (iCurrentPage < 0) iCurrentPage = vCategories[iCurrentCategory].vPages.size() - 1;
	if (iCurrentCategory + 1 > vCategories.size()) iCurrentCategory = 0;
	if (iCurrentCategory < 0) iCurrentCategory = vCategories.size() - 1;
}

void EMenu::DrawMenu()
{
	if (bDisplayMenu)
	{
		// control execution

		for (int i = 0; i < vCategories.size(); i++)
		{

			sprintf(msgBuffer, "ermaccer / dixmor-hospital.com", iCurrentPage + 1, vCategories[iCurrentCategory].vPages.size());
			SetDrawRGBA(0, 0, 0, 255);
			PrintText(msgBuffer, 0.048f, 0.012f, 0.5f, 0.5f, 0.0, FONT_TYPE_DEFAULT);
			SetDrawRGBA(255, 255, 255, 255);
			PrintText(msgBuffer, 0.050f, 0.010f, 0.5f, 0.5f, 0.0, FONT_TYPE_DEFAULT);


			SetDrawRGBA(0, 0, 0, 255);
			PrintText(vCategories[i].strName.c_str(), 0.048f, 0.102f + 0.04 * i, 0.7f, 0.7f, 0.0, FONT_TYPE_DEFAULT);
			if (i == iCurrentCategory)
				SetDrawRGBA(255, 64, 64, 255);
			else
				SetDrawRGBA(255, 255, 255, 255);
			PrintText(vCategories[i].strName.c_str(), 0.050f, 0.10f + 0.04 * i, 0.7f, 0.7f, 0.0, FONT_TYPE_DEFAULT);

			// draw sub items
			if (vCategories[i].bHasItems && bCategoryOpen)
			{
				if (i == iCurrentCategory)
				{
					if (vCategories[i].bIsWeapon)
					{
						if (!vCategories[i].bHasBeenWeaponsPopulated)
						{
							for (int j = 0; j < vCategories[i].vItems.size(); j++)
							{
								if (vCategories[i].vItems[j].bIsWeapon)
								{
									if (GetEntity(GetRecordName(vCategories[i].vItems[j].iWeaponID)))
										vTempWeapons.push_back(vCategories[i].vItems[j]);
								}
							}
							vCategories[i].vWeapons = vTempWeapons;
							vCategories[i].bHasBeenWeaponsPopulated = true;
						}

						if (!vCategories[iCurrentCategory].bHaveBeenPagesCalculated)
						{
							EMenuPage page;
							int itemCounter = 0;
							int fullPages = vCategories[iCurrentCategory].vWeapons.size() / 16;
							int leftOver = vCategories[iCurrentCategory].vWeapons.size() % 16;
							int lastEnd = 0;
							page.iStart = 0;
							for (int p = 0; p < vCategories[iCurrentCategory].vWeapons.size(); p++)
							{
								if (itemCounter >= 16)
								{
									page.iEnd = p;
									page.iStart += lastEnd;
									lastEnd = page.iEnd - page.iStart;
									itemCounter = 0;
									vTempPages.push_back(page);
								}
								itemCounter++;
							}
							page.iEnd = vCategories[iCurrentCategory].vWeapons.size();
							page.iStart = vCategories[iCurrentCategory].vWeapons.size() - leftOver;
							vTempPages.push_back(page);
							vCategories[iCurrentCategory].vPages = vTempPages;
							vCategories[iCurrentCategory].bHaveBeenPagesCalculated = true;
						}
						iTotalItems = vCategories[iCurrentCategory].vPages[iCurrentPage].iEnd - vCategories[iCurrentCategory].vPages[iCurrentPage].iStart;

						for (int j = vCategories[iCurrentCategory].vPages[iCurrentPage].iStart; j < vCategories[iCurrentCategory].vPages[iCurrentPage].iEnd; j++)
						{
							iActualItemID = j;
							std::string entry = vCategories[i].vWeapons[j].name.c_str();
							SetDrawRGBA(0, 0, 0, 255);
							PrintText(entry.c_str(), 0.122f, 0.102f + 0.04 * (j - (vCategories[iCurrentCategory].vPages[iCurrentPage].iStart)), 0.7f, 0.7f, 0.0, FONT_TYPE_DEFAULT);
							if ((j - (vCategories[iCurrentCategory].vPages[iCurrentPage].iStart)) == iCurrentItem)
								SetDrawRGBA(255, 64, 64, 255);
							else
								SetDrawRGBA(255, 255, 255, 255);
							PrintText(entry.c_str(), 0.124f, 0.10f + 0.04 * (j - (vCategories[iCurrentCategory].vPages[iCurrentPage].iStart)), 0.7f, 0.7f, 0.0, FONT_TYPE_DEFAULT);
						}
						if (vCategories[iCurrentCategory].vPages.size() > 1)
						{
							sprintf(msgBuffer, "Page %d/%d", iCurrentPage + 1, vCategories[iCurrentCategory].vPages.size());
							SetDrawRGBA(0, 0, 0, 255);
							PrintText(msgBuffer, 0.122f, 0.808f, 0.7f, 0.7f, 0.0, FONT_TYPE_DEFAULT);
							SetDrawRGBA(255, 255, 255, 255);
							PrintText(msgBuffer, 0.124f, 0.810f, 0.7f, 0.7f, 0.0, FONT_TYPE_DEFAULT);
						}

					}
					else
					{
						iTotalItems = vCategories[i].vItems.size();

						if (!vCategories[iCurrentCategory].bHaveBeenPagesCalculated)
						{
							EMenuPage page;
							int itemCounter = 0;
							int fullPages = vCategories[iCurrentCategory].vItems.size() / 16;
							int leftOver = vCategories[iCurrentCategory].vItems.size() % 16;
							int lastEnd = 0;
							page.iStart = 0;
							for (int p = 0; p < vCategories[iCurrentCategory].vItems.size(); p++)
							{
								if (itemCounter >= 16)
								{
									page.iEnd = p;
									page.iStart += lastEnd;
									lastEnd = page.iEnd - page.iStart;
									itemCounter = 0;
									vTempPages.push_back(page);
								}
								itemCounter++;
							}
							page.iEnd = vCategories[iCurrentCategory].vItems.size();
							page.iStart = vCategories[iCurrentCategory].vItems.size() - leftOver;
							vTempPages.push_back(page);
							vCategories[iCurrentCategory].vPages = vTempPages;
							vCategories[iCurrentCategory].bHaveBeenPagesCalculated = true;
						}

						// to do: add optional description params
						if (vCategories[i].vItems[iCurrentItem].name == "Free Camera")
						{
							sprintf(msgBuffer, "Press SPACE to teleport, press CTRL+V to quickly activate");
							SetDrawRGBA(0, 0, 0, 255);
							PrintText(msgBuffer, 0.122f, 0.852f, 0.7f, 0.7f, 0.0, FONT_TYPE_DEFAULT);
							SetDrawRGBA(255, 255, 255, 255);
							PrintText(msgBuffer, 0.124f, 0.850f, 0.7f, 0.7f, 0.0, FONT_TYPE_DEFAULT);
						}


						if (vCategories[i].vItems[iCurrentItem].name == "Give 5*")
						{
							sprintf(msgBuffer, "Will affect whole playthrough once activated.");
							SetDrawRGBA(0, 0, 0, 255);
							PrintText(msgBuffer, 0.122f, 0.852f, 0.7f, 0.7f, 0.0, FONT_TYPE_DEFAULT);
							SetDrawRGBA(255, 255, 255, 255);
							PrintText(msgBuffer, 0.124f, 0.850f, 0.7f, 0.7f, 0.0, FONT_TYPE_DEFAULT);
						}



						for (int j = vCategories[iCurrentCategory].vPages[iCurrentPage].iStart; j < vCategories[iCurrentCategory].vPages[iCurrentPage].iEnd; j++)
						{
							iActualItemID = j;
							std::string entry = vCategories[i].vItems[j].name.c_str();
							if (vCategories[i].vItems[j].bIsCharToggle || vCategories[i].vItems[j].bIsShortToggle || vCategories[i].vItems[j].bIsIntegerToggle)
							{
								entry.append(" = ");
								if (vCategories[i].vItems[j].bIsCharToggle)
									entry.append(GetStatusAsString(*vCategories[i].vItems[j].ptrCharValue));
								if (vCategories[i].vItems[j].bIsIntegerToggle)
									entry.append(GetStatusAsString(*vCategories[i].vItems[j].ptrIntValue));
							}
	




							SetDrawRGBA(0, 0, 0, 255);
							PrintText(entry.c_str(), 0.122f, 0.102f + 0.04 * j, 0.7f, 0.7f, 0.0, FONT_TYPE_DEFAULT);
							if (j == iCurrentItem)
								SetDrawRGBA(255, 64, 64, 255);
							else
								SetDrawRGBA(255, 255, 255, 255);
							PrintText(entry.c_str(), 0.124f, 0.10f + 0.04 * j, 0.7f, 0.7f, 0.0, FONT_TYPE_DEFAULT);



							if (vCategories[iCurrentCategory].vPages.size() > 1)
							{
								sprintf(msgBuffer, "Page %d/%d", iCurrentPage + 1, vCategories[iCurrentCategory].vPages.size());
								SetDrawRGBA(0, 0, 0, 255);
								PrintText(msgBuffer, 0.122f, 0.808f, 0.7f, 0.7f, 0.0, FONT_TYPE_DEFAULT);
								SetDrawRGBA(255, 255, 255, 255);
								PrintText(msgBuffer, 0.124f, 0.810f, 0.7f, 0.7f, 0.0, FONT_TYPE_DEFAULT);
							}
						}
					}

				}
			}

		}

	}
}

void EMenu::ProcessEnter()
{
	if (GetTickCount() - iTimer <= 155)  return;
	iTimer = GetTickCount();
	bPressedEnter = false;
}

void EMenu::ProcessFastCam()
{
	if (KeyHit(KeyQuickCameraMain) && KeyHit(KeyQuickCameraSub))
	{
		if (GetTickCount() - iTimer <= 200) return;
		iTimer = GetTickCount();
		iFreeCamera ^= 1;
		iFreezeWorld ^= 1;
	}

}

void EMenu::AddCategory(std::string name, bool isWeap)
{
	EMenuCategory newCat;
	newCat.strName = name;
	newCat.bIsWeapon = isWeap;
	newCat.iID = iBaseCategoryID;
	newCat.bHasBeenWeaponsPopulated = false;
	newCat.bHaveBeenPagesCalculated = false;
	newCat.iPages = 0;
	if (vTempItems.size() > 0)
	{
		newCat.vItems = vTempItems;
		newCat.bHasItems = true;
	}

	vCategories.push_back(newCat);
	iBaseCategoryID++;
	vTempItems.clear();
}

void EMenu::AddItem(std::string name, bool isChar, bool isShort, bool isInt, bool isFunc, bool isWeapon, int weapID, char* ptrChar, short* ptrShort, int* ptrInt, std::function<void()> func)
{
	EMenuItem item;
	item.ptrIntValue = ptrInt;
	item.ptrShortValue = ptrShort;
	item.ptrCharValue = ptrChar;
	item.bIsCharToggle = isChar;
	item.bIsShortToggle = isShort;
	item.bIsIntegerToggle = isInt;
	item.bIsFunction = isFunc;
	item.bIsWeapon = isWeapon;
	item.iWeaponID = weapID;
	item.name = name;
	item.fFunc = func;
	
	vTempItems.push_back(item);
}

void EMenu::AddWeaponEntry(int weaponID)
{
	std::string str = GetRecordName(weaponID);;
	std::wstring wstr = GetCollectableName(weaponID);
	if (!wstr.empty())
		str = std::string(wstr.begin(), wstr.end());

	std::function<void()> dummy;
	AddItem(str, false, false, false, false, true, weaponID,nullptr,nullptr,nullptr,dummy);
}

void EMenu::AddToggleCharEntry(std::string name, char * ptr)
{
	std::function<void()> dummy;
	AddItem(name, true, false, false, false, false, false, ptr, nullptr, nullptr, dummy);
}

void EMenu::AddToggleIntEntry(std::string name, int * ptr)
{
	std::function<void()> dummy;
	AddItem(name, false, false, true, false, false, false, nullptr, nullptr, ptr,dummy);
}

void EMenu::AddFunctionEntry(std::string name, std::function<void()> func)
{
	AddItem(name, false, false, false, true, false, 0, nullptr, nullptr, nullptr, func);
}

void ResetTimer()
{
	iTimer = 0;
	bDisableAI = 0;
}

std::string GetStatusAsString(int value)
{
	if (value) return "true";
	else return "false";
}

void __fastcall HookVisibility(int ptr)
{
	if (!bDisableAI) CallMethod<0x420100, int>(ptr);
}

void SetSpeed10()
{
	SetSpeed(1);
}

void SetSpeed25()
{
	SetSpeed(4);
}

void SetSpeed50()
{
	SetSpeed(8);
}

void SetSpeed75()
{
	SetSpeed(12);
}

void SetSpeedDefault()
{
	iTimeStep = 16;
}

void SetSpeed(int speed)
{
	TheMenu.SlowMotionPressValue = speed;
	iTimeStep = speed;
}
