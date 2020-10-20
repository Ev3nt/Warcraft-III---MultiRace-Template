#pragma once

#include <Windows.h>

template <typename R, typename F, typename ...A>
inline R stdcall(F function, A ...arguments)
{
	return reinterpret_cast<R(_stdcall*)(A...)>(function)(arguments...);
}

template <typename R, typename F, typename ...A>
inline R fastcall(F function, A ...arguments)
{
	return reinterpret_cast<R(_fastcall*)(A...)>(function)(arguments...);
}

bool patch(UINT_PTR nAddress, DWORD dwBytes, SIZE_T nSize)
{
	DWORD dwOldProtect = NULL;

	if (VirtualProtect((LPVOID)nAddress, nSize, PAGE_EXECUTE_READWRITE, &dwOldProtect))
	{
		memcpy((LPVOID)nAddress, (LPVOID)&dwBytes, nSize);
		VirtualProtect((LPVOID)nAddress, nSize, dwOldProtect, NULL);

		return true;
	}

	return false;
}

bool fill(UINT_PTR nAddress, DWORD dwBytes, SIZE_T nSize)
{
	bool retval = true;

	for (UINT i = 0; i < nSize; i++)
		if (retval)
			retval = patch(nAddress + i, dwBytes, 1);
		else
			return false;

	return true;
}

template <typename A>
bool call(UINT_PTR nAddress, A lpFunction)
{
	return patch(nAddress, 0xe8, 1) & patch(nAddress + 1, (UINT_PTR)lpFunction - (nAddress + 5), 4);
}

template <typename A>
bool jmp(UINT_PTR nAddress, A lpFunction)
{
	return patch(nAddress, 0xe9, 1) & patch(nAddress + 1, (UINT_PTR)lpFunction - (nAddress + 5), 4);
}