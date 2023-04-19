//Playing_field.cpp

#include "Tetris_graphics.h"

// Инициализация статических данных
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
	for (short x = 0; x < Xsize; x++) // Для всех Х 
		for (short y = 0; y < Ysize; y++) // Для всех У
			field[x][y] = 0; // Устанавливаем нулевое значение, т.е. в ячейке нет фигуры - она свободна 
}
bool Playing_field::examination(int X, int Y) const // Возвращает true если клетка пуста
{
	if (X >= Xsize || X < 0 || Y >= Ysize || Y < 0) // Проверка аргументов на соответствие требований массива;  
		return false; // Выход за границы массива по логике игры означает выход за границы игрового поля, поэтому возвращаем 0 
	if (field[X][Y] == 0) // Если ячейка пуста
		return true;  
	return false; 
}
void Playing_field::inpt_data_field(int X, int Y, int color) // Ввод данных в сетку поля
{
	if (X >= Xsize || X < 0 || Y >= Ysize || Y < 0) // Проверка аргументов на соответствие требований массива
		return;
	else 
		field[X][Y] = color; // Записиваем в ячейку цвет фигурки, теперь она занята 
}
int Playing_field::return_data_field(int X, int Y) // Вывод данных из игрового поля, для вывода на экран, если ячейка пустая
										// выводится 0, если нет - выводится цвет
{
	if (X >= Xsize || X < 0 || Y >= Ysize || Y < 0) // Проверка аргументов на соответствие требований массива
		return 0;
	else 
		return field[X][Y]; // Возвращаем значение цвета, либо 0, если ячейка пуста
}
void Playing_field::set_score_level() // Убираем заполненную строку и увеличиваем очки игрока, при опеделенном количестве
{                      // очков, поднимаем уровень игры
	for (short y = 0; y < Ysize; y++) // Для всех строк
	{
		bool line_down = true; // Флаг спуска всей линии на соседний нижний уровень
		for (short x = 0; x < Xsize; x++) // Для всех Х
			if (field[x][y] == 0) // Если ячейка пуста
				line_down *= false; // Флаг сбрасывается
		if (line_down == true) // Если все ячейки заняты и флаг не сбросился
		{
			score += level; // Увеличиваем счет игрока пропорционально уровню игры
			for (short x = 0; x < Xsize; x++) // Для всех столбов
			{
				for (short Y = y; Y > 0; Y--) // Для всех У
					field[x][Y] = field[x][Y - 1]; // Сохраняем в нижней ячейке значение верхней
				field[x][1] = 0; // Самой верхней ячейке присваиваем нулевое значение 
			}
		}
	}
	int levelUp = 5; // Устанавливаем уровень: сохраняем кратность числа очков для перехода на следующий уровень игры
	for (short i = 1; i < level; i++) // Умножаем кратность на коэфф. в цикле где кол-во итераций равно уровню
		levelUp *= 4;
	if (score > levelUp) // Если количество очков выше полученного выражения, то
		level++; // Увеличиваем уровень
}
int Playing_field::return_score() // Статическая функция, возвращающая количество очков игрока
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
int Playing_field::return_level() // Статическая функция, возвращающая уровень игры
{
	return level;
}
int Playing_field::return_count_figure() // Статическая функция, возвращающая количество созданых фигур
{
	return count_figure;
}
void Playing_field::set_count_figure(int temp) // Статическая функция, устанавливающая значение счетчика фигур
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