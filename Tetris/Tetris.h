//Tetris.h
#pragma once
#include "Figure_tetris.h"


class Game_Tetris // Класс взаимодействия фигурок и иигрового поля
{
private:
	Figure_tetris* ptr; // Указатель на абстрактный класс фигур
	int count; // Счетчик игровых циклов
	char choice; // Выбор игрока, введенный с клавиатуры
	bool make_new_figure; // Флаг создания новой фигуры 
	bool end_game; // Флаг конца игры
	bool new_game; // Флаг перезапуска игры
	int last1_rand, last2_rand; // Последнее и предпоследнее значение случайного числа для создания случайной фигуры
	std::ifstream infile; // файл для загрузки рекорда
	std::ofstream outfile; // файл для сохранения рекорда
	Graphics Graph; // Объект для работы с графикой и окном
public:
	Game_Tetris(HINSTANCE hInstance, int nCmdShow); // Аргументы конструктора необходимы для инициализации окна в объетке Graph
	~Game_Tetris();
	class Exception // Класс исключения
	{
	public:
		static const int Size = 32;
		TCHAR Messenge[Size];
		Exception(TCHAR messenge[]);
		void PrintException(); // Метод вывода сообщения исключения
	};
	int random_number(); // Функция возврата случайного числа от 1 до 5 для создания фигур
	void save_score(); // Сохранение рекорда
	void game_cicle(); // Игровой цикл
	void load_score(); // загрузка рекорда
	void game(); // Запуск игры
};