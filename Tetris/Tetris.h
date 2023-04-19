//Tetris.h
#pragma once
#include "Figure_tetris.h"


class Game_Tetris // ����� �������������� ������� � ��������� ����
{
private:
	Figure_tetris* ptr; // ��������� �� ����������� ����� �����
	int count; // ������� ������� ������
	char choice; // ����� ������, ��������� � ����������
	bool make_new_figure; // ���� �������� ����� ������ 
	bool end_game; // ���� ����� ����
	bool new_game; // ���� ����������� ����
	int last1_rand, last2_rand; // ��������� � ������������� �������� ���������� ����� ��� �������� ��������� ������
	std::ifstream infile; // ���� ��� �������� �������
	std::ofstream outfile; // ���� ��� ���������� �������
	Graphics Graph; // ������ ��� ������ � �������� � �����
public:
	Game_Tetris(HINSTANCE hInstance, int nCmdShow); // ��������� ������������ ���������� ��� ������������� ���� � ������� Graph
	~Game_Tetris();
	class Exception // ����� ����������
	{
	public:
		static const int Size = 32;
		TCHAR Messenge[Size];
		Exception(TCHAR messenge[]);
		void PrintException(); // ����� ������ ��������� ����������
	};
	int random_number(); // ������� �������� ���������� ����� �� 1 �� 5 ��� �������� �����
	void save_score(); // ���������� �������
	void game_cicle(); // ������� ����
	void load_score(); // �������� �������
	void game(); // ������ ����
};