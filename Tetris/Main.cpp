//Main.cpp
#include "Tetris.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR    lpCmdLine,
	_In_ int       nCmdShow) //����� �����
{

	Game_Tetris tetris(hInstance, nCmdShow); // ������� ������ ���� ������
	while (GetMessage(&msg, NULL, 0, 0))
		tetris.game();// ��������� ������� ����
	return (int)msg.wParam;
}