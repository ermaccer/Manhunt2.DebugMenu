#pragma once
#include <string>

bool KeyHit(unsigned int keyCode);
std::string GetTrueFalse(int val);
std::string GetCharTrueFalse(char val);
void GivePlayerWeapon(int weaponid, const char* record, bool firearm);
void CameraTeleporting();