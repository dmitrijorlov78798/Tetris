//Playing_field.cpp

#include "Tetris_graphics.h"

// ������������� ����������� ������
int Playing_field::count_figure = 0; 
int Playing_field::score = 0;
int Playing_field::score_record = 0;
int Playing_field::level = 1;
int Playing_field::field[Xsize][Ysize]{};

Playing_field::Playing_field() {}
void Playing_field::start_Playing_field()
{
	count_figure = 0;
	score = 0;
	level = 1;
	for (short x = 0; x < Xsize; x++) // ��� ���� � 
		for (short y = 0; y < Ysize; y++) // ��� ���� �
			field[x][y] = 0; // ������������� ������� ��������, �.�. � ������ ��� ������ - ��� �������� 
}
bool Playing_field::examination(int X, int Y) const // ���������� true ���� ������ �����
{
	if (X >= Xsize || X < 0 || Y >= Ysize || Y < 0) // �������� ���������� �� ������������ ���������� �������;  
		return false; // ����� �� ������� ������� �� ������ ���� �������� ����� �� ������� �������� ����, ������� ���������� 0 
	if (field[X][Y] == 0) // ���� ������ �����
		return true;  
	return false; 
}
void Playing_field::inpt_data_field(int X, int Y, int color) // ���� ������ � ����� ����
{
	if (X >= Xsize || X < 0 || Y >= Ysize || Y < 0) // �������� ���������� �� ������������ ���������� �������
		return;
	else 
		field[X][Y] = color; // ���������� � ������ ���� �������, ������ ��� ������ 
}
int Playing_field::return_data_field(int X, int Y) // ����� ������ �� �������� ����, ��� ������ �� �����, ���� ������ ������
										// ��������� 0, ���� ��� - ��������� ����
{
	if (X >= Xsize || X < 0 || Y >= Ysize || Y < 0) // �������� ���������� �� ������������ ���������� �������
		return 0;
	else 
		return field[X][Y]; // ���������� �������� �����, ���� 0, ���� ������ �����
}
void Playing_field::set_score_level() // ������� ����������� ������ � ����������� ���� ������, ��� ����������� ����������
{                      // �����, ��������� ������� ����
	for (short y = 0; y < Ysize; y++) // ��� ���� �����
	{
		bool line_down = true; // ���� ������ ���� ����� �� �������� ������ �������
		for (short x = 0; x < Xsize; x++) // ��� ���� �
			if (field[x][y] == 0) // ���� ������ �����
				line_down *= false; // ���� ������������
		if (line_down == true) // ���� ��� ������ ������ � ���� �� ���������
		{
			score += level; // ����������� ���� ������ ��������������� ������ ����
			for (short x = 0; x < Xsize; x++) // ��� ���� �������
			{
				for (short Y = y; Y > 0; Y--) // ��� ���� �
					field[x][Y] = field[x][Y - 1]; // ��������� � ������ ������ �������� �������
				field[x][1] = 0; // ����� ������� ������ ����������� ������� �������� 
			}
		}
	}
	int levelUp = 5; // ������������� �������: ��������� ��������� ����� ����� ��� �������� �� ��������� ������� ����
	for (short i = 1; i < level; i++) // �������� ��������� �� �����. � ����� ��� ���-�� �������� ����� ������
		levelUp *= 4;
	if (score > levelUp) // ���� ���������� ����� ���� ����������� ���������, ��
		level++; // ����������� �������
}
int Playing_field::return_score() // ����������� �������, ������������ ���������� ����� ������
{
	return score;
}
void Playing_field::set_score_record(int temp)
{
	score_record = temp;
}
int Playing_field::return_score_record()
{
	return score_record;
}
void Playing_field::set_score(int temp)
{
	score = temp;
}
void Playing_field::set_level(int temp)
{
	level = temp;
}
int Playing_field::return_level() // ����������� �������, ������������ ������� ����
{
	return level;
}
int Playing_field::return_count_figure() // ����������� �������, ������������ ���������� �������� �����
{
	return count_figure;
}
void Playing_field::set_count_figure(int temp) // ����������� �������, ��������������� �������� �������� �����
{
	count_figure = temp;
}

Playing_field::Exception::Exception(TCHAR messenge[])
{
	int i = 0;
	while (i < (Size - 1) || messenge[i] != '\0')
		Messenge[i] = messenge[i++];
	Messenge[i] = '\0';
}
void Playing_field::Exception::PrintException()
{
	Graphics::paint_exception(Messenge);
}