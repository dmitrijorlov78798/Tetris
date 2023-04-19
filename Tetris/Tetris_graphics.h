//Tetris_graphics

#pragma once
#include <fstream>
#include <windows.h>
#include <tchar.h>

const int Xsize = 15, Ysize = 20; // размер игрогого поля

class Playing_field // Класс состояния игрового поля, взаимодействие фигурок
{
private:
	static int count_figure; // Счет количества фигур
	static int score; // Счет очков игрока
	static int score_record; // Рекорд
	static int level; // Уровень игры
	static int field[Xsize][Ysize]; // Массив состояния игрового поля (0 - нет квадрата фигуры, i > 0 - цвет квадрата фигуры)
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
	static void start_Playing_field(); // Установка игровых значений для новой игры 
	bool examination(int X, int Y) const; // Проверка занятости ячейки
	static void inpt_data_field(int X, int Y, int color); // Ввод данных в сетку поля
	static int return_data_field(int X, int Y); // Вывод данных из игрового поля
	void set_score_level(); // Убираем заполненную строку и увеличиваем очки игрока, при опеделенном количестве
	static int return_score(); // Статическая функция, возвращающая количество очков игрока
	static int return_score_record(); // Возвращает рекорд
	static void set_score_record(int temp); // Устанавливает рекорд
	static void set_score(int temp); // Устанавливает счет
	static void set_level(int temp); // Устанавливает уровень
	static int return_level(); // Статическая функция, возвращающая уровень игры
	static int return_count_figure(); // Статическая функция, возвращающая количество созданых фигур
	static void set_count_figure(int temp); // Статическая функция, устанавливающая значение счетчика фигур
};

struct color_tetris // цвет объектов в окне
{
	int R, G, B;
	color_tetris(int r, int g, int b)
	{
		R = r; G = g; B = b;
	}
};

class Graphics // Графика и графические функции. Требуется подключение <Windows.h>
{
private :
	WNDCLASSEX wcex; // структура, содержащая сведения об окне
	HINSTANCE hInst; // Дескриптор окна
public:
	Graphics(HINSTANCE hInstance, int nCmdShow);  // Конструктор
	~Graphics(); // деструктор
	class Exception
	{
	public:
		static const int Size = 32;
		TCHAR Messenge[Size];
		Exception(TCHAR messenge[]);
		void PrintException();
	};
	static bool exit_game; // флаг выхода из игры
	static int paint_end_game; // Переменная синхронизации прорисовки вопроса перезапуска игры
	static char press_key; // счетчик после нажатия клавиши, для настройки чувствительности 
	static int last_shot[Xsize][Ysize]; // Последний отрисованный кадр
	bool getmsg(); // функция обработки сообщений
	void destroy_win(); // Уничтожает окно при выходе из игрового цикла
	static void exit_window(); // Выходит из игрового цикла при уничтожении окна
	static void create_win_obj(); // создает кисти и заливки
	static void delete_win_obj(); // удаляет кисти и заливки
	static void paint_square(int X, int Y, int Color); // Вывести квадрат фигурки на экран на позиции Х, У
	static void paint_text(); // Выводит текст в окне
	static void paint_for_system(); // Прорисовка для системы
	static void paint_for_game(); // Игровая прорисовка
	static bool events_press_key(char Key); // возвращает 1 при нажатии клавиши
	static void end_game(int temp); // Устанавливает значение переменной paint_end_game 
	static void paint_exception(TCHAR messenge[]); // Выводит сообщения исключений
};

extern MSG msg; // сообщения от системы

LRESULT CALLBACK WndProc(_In_ HWND hWnd, _In_ UINT message, _In_ WPARAM wParam, _In_ LPARAM lParam); //процедура обработки событий окна

