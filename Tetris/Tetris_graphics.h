//Tetris_graphics

#pragma once
#include <fstream>
#include <windows.h>
#include <tchar.h>

const int Xsize = 15, Ysize = 20; // ������ �������� ����

class Playing_field // ����� ��������� �������� ����, �������������� �������
{
private:
	static int count_figure; // ���� ���������� �����
	static int score; // ���� ����� ������
	static int score_record; // ������
	static int level; // ������� ����
	static int field[Xsize][Ysize]; // ������ ��������� �������� ���� (0 - ��� �������� ������, i > 0 - ���� �������� ������)
public:
	Playing_field();
	class Exception
	{
	public:
		static const int Size = 32;
		TCHAR Messenge[Size];
		Exception(TCHAR messenge[]);
		void PrintException();
	};
	static void start_Playing_field(); // ��������� ������� �������� ��� ����� ���� 
	bool examination(int X, int Y) const; // �������� ��������� ������
	static void inpt_data_field(int X, int Y, int color); // ���� ������ � ����� ����
	static int return_data_field(int X, int Y); // ����� ������ �� �������� ����
	void set_score_level(); // ������� ����������� ������ � ����������� ���� ������, ��� ����������� ����������
	static int return_score(); // ����������� �������, ������������ ���������� ����� ������
	static int return_score_record(); // ���������� ������
	static void set_score_record(int temp); // ������������� ������
	static void set_score(int temp); // ������������� ����
	static void set_level(int temp); // ������������� �������
	static int return_level(); // ����������� �������, ������������ ������� ����
	static int return_count_figure(); // ����������� �������, ������������ ���������� �������� �����
	static void set_count_figure(int temp); // ����������� �������, ��������������� �������� �������� �����
};

struct color_tetris // ���� �������� � ����
{
	int R, G, B;
	color_tetris(int r, int g, int b)
	{
		R = r; G = g; B = b;
	}
};

class Graphics // ������� � ����������� �������. ��������� ����������� <Windows.h>
{
private :
	WNDCLASSEX wcex; // ���������, ���������� �������� �� ����
	HINSTANCE hInst; // ���������� ����
public:
	Graphics(HINSTANCE hInstance, int nCmdShow);  // �����������
	~Graphics(); // ����������
	class Exception
	{
	public:
		static const int Size = 32;
		TCHAR Messenge[Size];
		Exception(TCHAR messenge[]);
		void PrintException();
	};
	static bool exit_game; // ���� ������ �� ����
	static int paint_end_game; // ���������� ������������� ���������� ������� ����������� ����
	static char press_key; // ������� ����� ������� �������, ��� ��������� ���������������� 
	static int last_shot[Xsize][Ysize]; // ��������� ������������ ����
	bool getmsg(); // ������� ��������� ���������
	void destroy_win(); // ���������� ���� ��� ������ �� �������� �����
	static void exit_window(); // ������� �� �������� ����� ��� ����������� ����
	static void create_win_obj(); // ������� ����� � �������
	static void delete_win_obj(); // ������� ����� � �������
	static void paint_square(int X, int Y, int Color); // ������� ������� ������� �� ����� �� ������� �, �
	static void paint_text(); // ������� ����� � ����
	static void paint_for_system(); // ���������� ��� �������
	static void paint_for_game(); // ������� ����������
	static bool events_press_key(char Key); // ���������� 1 ��� ������� �������
	static void end_game(int temp); // ������������� �������� ���������� paint_end_game 
	static void paint_exception(TCHAR messenge[]); // ������� ��������� ����������
};

extern MSG msg; // ��������� �� �������

LRESULT CALLBACK WndProc(_In_ HWND hWnd, _In_ UINT message, _In_ WPARAM wParam, _In_ LPARAM lParam); //��������� ��������� ������� ����

