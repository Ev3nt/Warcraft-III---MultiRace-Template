#include <Windows.h>
#include <vector>
#include "Memory.h"

using namespace std;

extern "C"
{
	DWORD dwGame = (DWORD)GetModuleHandle("game.dll");

	vector<string> Races = { "Human", "Orc", "Undead", "NightElf" };
	vector<string> RacesNames = { "HUMAN", "ORC", "UNDEAD", "NIGHT_ELF" };

	UINT GetRacesCount()
	{
		return Races.size();
	}

	UINT GetRacesNamesCount()
	{
		return RacesNames.size();
	}

	void RaceUI();

	void RaceSounds();

	void RaceLoadingScreen();

	void RaceName();

	void RaceScoreScreen();

	void RaceOrder();

	void RaceSlot();

	void RaceStartUnits();

	void RaceBlocked();

	void RaceIncreaser();

	void RaceInit();
}

BOOL APIENTRY DllMain(HMODULE hModule, UINT ul_reason_for_call, LPVOID lpReserve)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH && dwGame)
	{
		jmp(dwGame + 0x3a2840, RaceUI);
		jmp(dwGame + 0x31f5d0, RaceSounds);
		jmp(dwGame + 0x5a3d84, RaceLoadingScreen);
		jmp(dwGame + 0x58aa02, RaceName);
		jmp(dwGame + 0x39f710, RaceScoreScreen);
		jmp(dwGame + 0x559580, RaceOrder);
		jmp(dwGame + 0x5bed8e, dwGame + 0x5bedab);
		jmp(dwGame + 0x559260, RaceSlot);
		jmp(dwGame + 0x3a31a0, RaceStartUnits);
		jmp(dwGame + 0x599bcc, RaceBlocked);
		fill(dwGame + 0x5c0a1b, 0x90, 6);
		fill(dwGame + 0x5c0a25, 0x90, 5);
		jmp(dwGame + 0x3c11d0, RaceIncreaser);
		jmp(dwGame + 0x3c11a0, RaceInit);
		patch(dwGame + 0x5bf4e3, 0, 1);

		//stdcall<int>(GetProcAddress(GetModuleHandle("storm.dll"), (LPCSTR)279), "scorescreen-player-unknown.blp", 0, 0, 1, 0);
	}

	return TRUE;
}