#include <iostream>
#include<windows.h>

int Offset1;
int Offset2;

char playerName[20];
int Health;

using namespace std;

int main()
{
	HWND hWnd = FindWindowA(0, "AssaultCube");
	GetWindowThreadProcessId(hWnd, &pid);
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

	ReadProcessMemory(hProcess, (LPVOID)LocalPlayer, &pBase, sizeof(DWORD), 0);

	if (hProcess == NULL) {
		cout << "OpenProcess failed. GetLastError = " << dec << GetLastError() << endl;
		system("pause");
		return EXIT_FAILURE;
	}
	else
	{
		SetConsoleTitle(L"Assault Cube - Entity");
		int Counter = 0;
		ReadProcessMemory(hProcess, (LPCVOID)(0x400000 + EntityAddr), &Offset1, 4, NULL);
		printf_s("Entity Adress: 0x%04X\n\n", Offset1);
		for (int i = 4; i < 128; i += 4) {
			ReadProcessMemory(hProcess, (LPCVOID)(Offset1 + i), &Offset2, 4, NULL);
			ReadProcessMemory(hProcess, (LPCVOID)(Offset2 + name_Offset), &playerName, 20, NULL);
			ReadProcessMemory(hProcess, (LPCVOID)(Offset2 + p_Health), &Health, 20, NULL);
			ReadProcessMemory(hProcess, (LPCVOID)(Offset2 + p_CoordsX), &X, 4, NULL);
			ReadProcessMemory(hProcess, (LPCVOID)(Offset2 + p_CoordsY), &Y, 4, NULL);
			ReadProcessMemory(hProcess, (LPCVOID)(Offset2 + p_CoordsZ), &Z, 4, NULL);
			printf("[INFO]: Player %d - Name: %s\nCoordination: %f, %f, %f\nHealth: %i\nOffset: 0x%X\n\n", Counter++, playerName, X, Y, Z, Health, Offset2);
		}
		getchar();
	}
	return 0;
}