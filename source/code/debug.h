#pragma once
#include <string>

bool KeyHit(unsigned int keyCode);
std::string GetTrueFalse(int val);
std::string GetCharTrueFalse(char val);
void GivePlayerWeapon(int weaponid);
void CameraTeleporting();
void PrintCoords();
void SetDifficultySane();
void SetDifficultyInsane();
void SetWeatherFree();
void SetWeatherCloudy();
void SetWeatherWindy();
void SetWeatherRainy();
void SetWeatherThunder();
void SetWeatherFoggy();
void SetWeatherClear();
void KillPlayer();
void RestartLevel();
void CompleteLevel();
void FailLevel();
void Hook5Stars();
void Give5Stars();
void PlayAnim();