//Figure_tetris.h
#pragma once
#include "Tetris_graphics.h"

class Figure_tetris // ������� ����������� ����� ����� �������
{
protected:
	int X, Y, color; // ��������� ������ � ������������
	char orientation; // ���������� ������ � ������������
	bool finich; // ��������� �������� ������
	Playing_field Field; // ������� ������ ������ ������� ���� 
public:
	Figure_tetris(int color);
	virtual ~Figure_tetris();
	class Exception
	{
	public:
		static const int Size = 32;
		TCHAR Messenge[Size];
		Exception(TCHAR messenge[]);
		void PrintException();
	};
	virtual bool collision_check() = 0; // �������� ������������ �����
	void moving_figure(char direction); // ������� �������� ������
	bool return_finich() const; // ������� �������� ��������� �������� ������
	void cleaning_figure(); // ������� ������� ������ � ������
	virtual void write_figure() = 0; // ����������� ������� ������ ��������� ������ � ������� ����                                     
};

class Figure_line : public Figure_tetris // ����� ������: ����� 
{
public:
	Figure_line() : Figure_tetris(1) // ������ ���� ������
	{
		finich = collision_check(); // �������� �������� ��� �������� ������
	}
	bool collision_check() override;
	void write_figure() override; // ������ ��������� ������ � ������� ���� �� ���������� ��������
};

class Figure_square : public Figure_tetris // ����� ������: ������� 
{        // ������, � �������������� � ���������� � ��� ��������� ������ Figure_line
public :
	Figure_square() : Figure_tetris(2)
	{
		finich = collision_check();
	}
	bool collision_check() override;
	void write_figure() override; // ������ ��������� ������ � ������� ���� �� ���������� ��������
};

class Figure_t : public Figure_tetris // ����� ������: ������ �. ������ � ����������� ��������� ������ Figure_line
{
public :
	Figure_t() : Figure_tetris(3)
	{
		finich = collision_check();
	}
	bool collision_check() override;
	void write_figure() override; // ������ ��������� ������ � ������� ���� �� ���������� ��������
};

class Figure_g : public Figure_tetris // ����� ������: ������ �
{                                     // ������ � ����������� ��������� ������ Figure_line
public :
	Figure_g() : Figure_tetris(4)
	{
		finich = collision_check();
	}
	bool collision_check() override;
	void write_figure() override; // ������ ��������� ������ � ������� ���� �� ���������� ��������
};

class Figure_z : public Figure_tetris // ����� ������: ������ Z
{                                     // ������ � ����������� ��������� ������ Figure_line
public :
	Figure_z() : Figure_tetris(5)
	{
		finich = collision_check();
	}
	bool collision_check() override;
	void write_figure() override; // ������ ��������� ������ � ������� ���� �� ���������� ��������
};

