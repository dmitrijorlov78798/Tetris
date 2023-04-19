// Tetris.cpp
#include "Tetris.h"
// Сообщения для вывода на экран при возникновении исключения
TCHAR messenge_Tetris_game_cicle[24] = _T("Game_Tetris::game_cicle"),
messenge_Tetris_game_save_score[24] = _T("Game_Tetris::save_score");

Game_Tetris::Game_Tetris(HINSTANCE hInstance, int nCmdShow) : Graph(hInstance, nCmdShow),
count(0), choice('\0'), make_new_figure(true), end_game(false), new_game(false), last1_rand(-1), last2_rand(-2)
{
	ptr = new Figure_line; 
}
Game_Tetris::~Game_Tetris()
{
	delete ptr;
}
int Game_Tetris::random_number() // Функция возврата случайного числа от 1 до 5 для создания фигур 
{   
	srand(time(NULL));
	int random = ((rand() + Playing_field::return_level()
		+ Playing_field::return_count_figure()) % 5);
	if (last1_rand == random)  // Если значение повторяется с чотя бы с одним из двух предыдущих, меняем его
		random = (random + 2) % 5;
	if (last2_rand == random)
		random = (random + 1) % 5;
	last2_rand = last1_rand;
	last1_rand = random;
	return random; 
}
void Game_Tetris::game_cicle() // Игровой цикл
{
	Playing_field::start_Playing_field(); // Устанавливаем все игровые значения
	load_score(); // Загружаем рекорд
	while (!end_game && Graph.getmsg()) // Пока флаг конца игры сброшен и открыто окно выполняем:
	{
		if (new_game) // Если был перезапуск игры
		{
			new_game = false;
			if (Playing_field::return_score_record() < Playing_field::return_score()) // Проверяем есть ли новый рекорд
				Playing_field::set_score_record(Playing_field::return_score());
			Playing_field::start_Playing_field(); // Переустанавлимаем все игровые значения для начала игры
			make_new_figure = true;
			Graph.end_game(2); // Устанавливаем значение для прорисовки перезапуска игры
		}
		if (make_new_figure) // Если флаг создания новой фигуры выставлен выполняем:
		{
			delete ptr; // Удаляем прошлую фигуру
			switch (random_number()) // Для номеров от одного до пяти
			{
			case 0:
				ptr = new Figure_line; // При номере один, создаем новый объект Figure_line и присваиваем его 
				break;                 // адрес нашему указателю
			case 1:
				ptr = new Figure_square; // При номере два, создаем объект Figure_square и т.д.
				break;
			case 2:
				ptr = new Figure_t;
				break;
			case 3:
				ptr = new Figure_g;
				break;
			case 4:
				ptr = new Figure_z;
				break;
			default:
				throw Exception(messenge_Tetris_game_cicle);
				break;
			}
			Playing_field::set_count_figure(Playing_field::return_count_figure() + 1); // Увеличиваем счет фигур
			make_new_figure = false; // Сбрасываем флаг сосздания новой фигуры 
			if (ptr->return_finich()) // Если при создании новой фигуры, она сразу же достигла другой фигуры
			{                         // то игра окончена
				Graph.end_game(1);    // Прорисовываем вопрос о перезапуске игры
				while (Graph.getmsg())  // Пока открыто окно
				{
					if (Graph.events_press_key('y')) // ответ положителен, перезапускаем игру
					{
						end_game = false;
						if (Playing_field::return_score_record() < Playing_field::return_score())
							Playing_field::set_score_record(Playing_field::return_score());
						Playing_field::start_Playing_field();
						make_new_figure = true;
						break;
					}
					if (Graph.events_press_key('n'))  // Ответ отрицателен, выходим из игры
					{
						end_game = true;
						if (Playing_field::return_score_record() < Playing_field::return_score())
							Playing_field::set_score_record(Playing_field::return_score());
						break;
					}
					Sleep(25);
				}
				Graph.end_game(2); // Перепрорисовываем вопрос о перезапуске
				if (end_game) 
					break;
				else
					continue;
			}
			ptr->write_figure(); // Записываем фигуру в игровое поле, при следующей игровой прорисовке она появится на экране;
		} // Если же флаг создания новой фигуры был сброшен то:
		choice = '\0';
		while (Graph.getmsg())
		{
			count += Playing_field::return_level(); // Увеличиваем значение игрового счетчика на значение уровня
			if (count > 50) // Если счетчик больше фиксированного значения 
				{
					count = 0; // Сбрасываем его
					choice = 's'; // Задаем выбор, опустить фигуру вниз на одну ячейку
					break;
				}
			if (Graphics::events_press_key('s'))
			{
				ptr->cleaning_figure(); // стираем фигуру 
				while (!(ptr->return_finich())) // Пока фигура не закончила движение вниз выполняем:
					ptr->moving_figure('s'); // Задаем новое перемещение фигуры, в данном случае вниз на одну ячейку 
				ptr->write_figure(); // Записываем фигуру
				make_new_figure = true;
				break;
			}
			if (Graphics::events_press_key('p')) // Пауза
				do 
				{
					Sleep(25);
				} while ((!Graphics::events_press_key('p')) && Graph.getmsg());
			if (Graphics::events_press_key('w')) // Выход из игры
				{
					if (Playing_field::return_score_record() < Playing_field::return_score())
						Playing_field::set_score_record(Playing_field::return_score());
					end_game = true; 
					break; // Выходим из игрового цикла
				}
			if (Graphics::events_press_key('a')) // Движение фигуры влево
			{
				choice = 'a'; break;
			}
			if (Graphics::events_press_key('d')) // ...... вправо
			{
				choice = 'd'; break;
			}
			if (Graphics::events_press_key('q')) // Поворот фигуры по часовой стрелке
			{
				choice = 'q'; break;
			}
			if (Graphics::events_press_key('e')) // Поворот фигуры против часовой стрелки
			{
				choice = 'e'; break;
			}
			if (Graph.events_press_key('x')) // Перезапуск игры
			{
				new_game = true; break;
			}
			Sleep(25);
		}
		if (!make_new_figure) // если текущая фигура не достигла конца своего дживения вниз
		{
			ptr->cleaning_figure(); // стираем фигуру
			ptr->moving_figure(choice); // Перемещаем фигуру
			ptr->write_figure(); // Запоминаем ее в памяти игрового поля
			count += Playing_field::return_level(); // Убираем задержку автоматического продвижения фигуры вниз
			if (ptr->return_finich()) // Если после последнего перемещения фигуры, она заканчивает свое движение в низ
			{
				make_new_figure = true;
			} // Устанавливаем флаг создания новой фигуры
		}
	if (Graph.exit_game) // Если игрок принудительно закрыл окно
	{
		end_game = true;
		break;
	}
	} // Конец игрового цикла
	save_score();  // Сохраняем рекорд
	Graph.destroy_win(); // Уничтожаем окно
}
void Game_Tetris::save_score()
{
	outfile.open("record_score.txt");
	if (!outfile)
		throw Exception(messenge_Tetris_game_save_score);
	int temp = Playing_field::return_score_record();
	outfile << temp;
	outfile.close();
}
void Game_Tetris::load_score()
{
	infile.open("record_score.txt");
	int temp;
	if (!infile) // если игра запускается впервые
		Playing_field::set_score_record(0); // рекорд равен нулю
	else
	{
		infile >> temp;
		Playing_field::set_score_record(temp);
	}
	infile.close();
}
void Game_Tetris::game()
{
	try
	{
		game_cicle(); // Запускаем цикл и ловим исключения
	}
	catch (Game_Tetris::Exception Ex)
	{
		Ex.PrintException();
	}
	catch (Figure_tetris::Exception Ex)
	{
		Ex.PrintException();
	}
	catch (Graphics::Exception Ex)
	{
		Ex.PrintException();
	}
	catch (Playing_field::Exception Ex)
	{
		Ex.PrintException();
	}
}

Game_Tetris::Exception::Exception(TCHAR messenge[])
{
	int i = 0;
	while (i < (Size - 1) || messenge[i] != '\0')
		Messenge[i] = messenge[i++];
	Messenge[i] = '\0';
}
void Game_Tetris::Exception::PrintException()
{
	Graphics::paint_exception(Messenge);
}