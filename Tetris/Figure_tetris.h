//Figure_tetris.h
#pragma once
#include "Tetris_graphics.h"

class Figure_tetris // Базовый абстрактный класс фигур Тетриса
{
protected:
	int X, Y, color; // Положение фигуры в пространстве
	char orientation; // Ориентация фигуры в пространстве
	bool finich; // Окончание движения фигуры
	Playing_field Field; // Создаем объект класса игровое поле 
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
	virtual bool collision_check() = 0; // проверка столкновений фигур
	void moving_figure(char direction); // Функция движения фигуры
	bool return_finich() const; // Функция возврата окончания движения фигуры
	void cleaning_figure(); // функция очистки фигуры с экрана
	virtual void write_figure() = 0; // Виртуальная функция записи положения фигуры в игровом поле                                     
};

class Figure_line : public Figure_tetris // Класс фигура: линия 
{
public:
	Figure_line() : Figure_tetris(1) // задаем цвет фигуры
	{
		finich = collision_check(); // Проверка коллизии при создании фигуры
	}
	bool collision_check() override;
	void write_figure() override; // Запись положения фигуры в игровое поле по завершению движения
};

class Figure_square : public Figure_tetris // Класс фигура: квадрат 
{        // Методы, а соответственно и коментарии к ним идентичны классу Figure_line
public :
	Figure_square() : Figure_tetris(2)
	{
		finich = collision_check();
	}
	bool collision_check() override;
	void write_figure() override; // Запись положения фигуры в игровое поле по завершению движения
};

class Figure_t : public Figure_tetris // Класс фигура: буквой Т. Методы и комментарии идентичны классу Figure_line
{
public :
	Figure_t() : Figure_tetris(3)
	{
		finich = collision_check();
	}
	bool collision_check() override;
	void write_figure() override; // Запись положения фигуры в игровое поле по завершению движения
};

class Figure_g : public Figure_tetris // Класс фигура: буквой г
{                                     // Методы и комментарии идентичны классу Figure_line
public :
	Figure_g() : Figure_tetris(4)
	{
		finich = collision_check();
	}
	bool collision_check() override;
	void write_figure() override; // Запись положения фигуры в игровое поле по завершению движения
};

class Figure_z : public Figure_tetris // Класс фигура: буквой Z
{                                     // Методы и комментарии идентичны классу Figure_line
public :
	Figure_z() : Figure_tetris(5)
	{
		finich = collision_check();
	}
	bool collision_check() override;
	void write_figure() override; // Запись положения фигуры в игровое поле по завершению движения
};

