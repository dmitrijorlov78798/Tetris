//Figure_tetris.cpp
#include "Figure_tetris.h"
// Сообщения вывода исключений на экран
TCHAR messenge_Figure_line_write_figure[26] = _T("Figure_line::write_figure"),
messenge_Figure_t_write_figure[23] = _T("Figure_t::write_figure"),
messenge_Figure_g_write_figure[23] = _T("Figure_g::write_figure"),
messenge_Figure_z_write_figure[23] = _T("Figure_z::write_figure");

//Figure_tetris
Figure_tetris::Figure_tetris(int Color) : X(Xsize / 2), Y(3), color(Color), orientation('1'), finich(false) 
{}
Figure_tetris::~Figure_tetris()
{}
void Figure_tetris::moving_figure(char direction) 
{ 
	switch (direction)  // В зависимости от напрвления перемещения фигуры
	{
	case 'a': // Перемещение влево
		X--;
		if (collision_check()) // Проверка на коллизию (столкновение)
			X++; // Если произошло столкновение, отменяем перемещение
		break;
	case 's': // ...... вниз
		Y++;
		if (collision_check()) 
		{
			Y--; // Если столконовение фигуры произошло при движении вниз, значит она окончила свое движение, необходимо 
			finich = true;  // создавать новую фигуру
		}
		break;
	case 'd': // ...... вправо
		X++; 
		if (collision_check())
			X--;
		break;
	case 'q': // Поворот фигуры по часовой стрелке
		orientation++; // изменение ориентации фигуры
		if (orientation > '4') // Возможно лишь 4 положения фигуры
			orientation = '1'; 
		if (collision_check()) // Проверка коллизи
		{
			orientation--; // Если произошло столкновение, возврат поворота фигуры
			if (orientation < '1')
				orientation = '4';
		}
		break;
	case 'e': // Поворот против часовой стрелки
		orientation--;
		if (orientation < '1')
			orientation = '4';
		if (collision_check())
		{
			orientation++;
			if (orientation > '4')
				orientation = '1';
		}
		break;
	default:
		break; 
	}
}
bool Figure_tetris::return_finich() const // Функция возврата окончания движения фигуры
{
	return finich;
}
void Figure_tetris::cleaning_figure()
{
	short colortemp = color; 
	color = 0;
	write_figure(); // Записываем 0(отсутствие фигуры) в игровое поле
	color = colortemp;
}

// Figure_line
bool Figure_line::collision_check()
{
	bool permission = true; // Флаг проверки установим 1
	// В зависимости от ориентации фигуры, выполняем проверку на коллизию каждого квадрата фигуры
	if (orientation == '1') for (short i = 0; i < 4; i++) permission *= Field.examination(X + i, Y); 
	if (orientation == '2') for (short i = -1; i < 3; i++) permission *= Field.examination(X, Y + i);
	if (orientation == '3') for (short i = 0; i < 4; i++) permission *= Field.examination(X + i, Y);
	if (orientation == '4') for (short i = -1; i < 3; i++) permission *= Field.examination(X, Y - i);
	return !permission;
}
void Figure_line::write_figure() // Запись положения фигуры в игровое поле
{
	switch (orientation) // Для одной из четырех ориентаций
	{
	case '1':
		for (short i = 0; i < 4; i++)
			Field.inpt_data_field(X + i, Y, color); // Каждый квадрат фигуры записываем в массив игрового поля
		break;
	case '2':
		for (short i = -1; i < 3; i++)
			Field.inpt_data_field(X, Y + i, color);
		break;
	case '3':
		for (short i = 0; i < 4; i++)
			Field.inpt_data_field(X + i, Y, color);
		break;
	case '4':
		for (short i = -1; i < 3; i++)
			Field.inpt_data_field(X, Y - i, color);
		break;
	default:
		throw Exception(messenge_Figure_line_write_figure);
		break;
	}
	if (finich)
		Field.set_score_level(); // После записи фигуры, проверяем заполняемость полос и обновляем счет очков игрока
}                            

//Figure_square
bool Figure_square::collision_check()
{
	bool permission = true;       
	for (short i = 0; i < 2; i++)
		permission *= Field.examination(X + i, Y);
	for (short i = 0; i < 2; i++)
		permission *= Field.examination(X + i, Y + 1);
	return !permission;
}
void Figure_square::write_figure() // Запись положения фигуры в игровое поле по завершению движения
{
	for (short i = 0; i < 2; i++)
		Field.inpt_data_field(X + i, Y, color);
	for (short i = 0; i < 2; i++)
		Field.inpt_data_field(X + i, Y + 1, color);
	if (finich)
		Field.set_score_level(); // После записи фигуры, проверяем заполняемость полос и обновляем счет очков игрока
}

//Figure_t
bool Figure_t::collision_check()
{
	bool permission = true;
	if (orientation == '1') {
		for (short i = 0; i < 3; i++) permission *= Field.examination(X + i, Y);
		permission *= Field.examination(X + 1, Y + 1);
	}
	if (orientation == '2') { 
		for (short i = 0; i < 3; i++) permission *= Field.examination(X, Y + i); 
		permission *= Field.examination(X - 1, Y + 1);
	}
	if (orientation == '3') { 
		for (short i = 0; i < 3; i++) permission *= Field.examination(X + i, Y);
		permission *= Field.examination(X + 1, Y - 1);
	}
	if (orientation == '4') {
		for (short i = 0; i < 3; i++) permission *= Field.examination(X, Y + i);
		permission *= Field.examination(X + 1, Y + 1);
	}
	return !permission;
}
void Figure_t::write_figure() // Запись положения фигуры в игровое поле по завершению движения
{
	switch (orientation)
	{
	case '1':
		for (short i = 0; i < 3; i++)
			Field.inpt_data_field(X + i, Y, color);
		Field.inpt_data_field(X + 1, Y + 1, color);
		break;
	case '2':
		for (short i = 0; i < 3; i++)
			Field.inpt_data_field(X, Y + i, color);
		Field.inpt_data_field(X - 1, Y + 1, color);
		break;
	case '3':
		for (short i = 0; i < 3; i++)
			Field.inpt_data_field(X + i, Y, color);
		Field.inpt_data_field(X + 1, Y - 1, color);
		break;
	case '4':
		for (short i = 0; i < 3; i++)
			Field.inpt_data_field(X, Y + i, color);
		Field.inpt_data_field(X + 1, Y + 1, color);
		break;
	default:
		throw Exception(messenge_Figure_t_write_figure);
		break;
	}
	if (finich)
		Field.set_score_level(); // После записи фигуры, проверяем заполняемость полос и обновляем счет очков игрока
}

//Figure_g
bool Figure_g::collision_check()
{
	bool permission = true;
	if (orientation == '1') {
		for (short i = 0; i < 3; i++) permission *= Field.examination(X + i, Y);
		permission *= Field.examination(X + 2, Y + 1);
	}
	if (orientation == '2') {
		for (short i = 0; i < 3; i++) permission *= Field.examination(X, Y + i);
		permission *= Field.examination(X - 1, Y + 2);
	}
	if (orientation == '3') {
		for (short i = 0; i < 3; i++) permission *= Field.examination(X + i, Y);
		permission *= Field.examination(X, Y - 1);
	}
	if (orientation == '4') {
		for (short i = 0; i < 3; i++) permission *= Field.examination(X, Y + i);
		permission *= Field.examination(X + 1, Y);
	}
	return !permission;
}
void Figure_g::write_figure() // Запись положения фигуры в игровое поле по завершению движения
{
	switch (orientation)
	{
	case '1':
		for (short i = 0; i < 3; i++)
			Field.inpt_data_field(X + i, Y, color);
		Field.inpt_data_field(X + 2, Y + 1, color);
		break;
	case '2':
		for (short i = 0; i < 3; i++)
			Field.inpt_data_field(X, Y + i, color);
		Field.inpt_data_field(X - 1, Y + 2, color);
		break;
	case '3':
		for (short i = 0; i < 3; i++)
			Field.inpt_data_field(X + i, Y, color);
		Field.inpt_data_field(X, Y - 1, color);
		break;
	case '4':
		for (short i = 0; i < 3; i++)
			Field.inpt_data_field(X, Y + i, color);
		Field.inpt_data_field(X + 1, Y, color);
		break;
	default:
		throw Exception(messenge_Figure_g_write_figure);
		break;
	}
	if (finich)
		Field.set_score_level(); // После записи фигуры, проверяем заполняемость полос и обновляем счет очков игрока
}

//Figure_z
bool Figure_z::collision_check()
{
	bool permission = true;
	if (orientation == '1') {
		for (short i = 0; i < 2; i++) permission *= Field.examination(X + i, Y);
		for (short i = 0; i < 2; i++) permission *= Field.examination(X + 1 + i, Y + 1);
	}
	if (orientation == '2') {
		for (short i = 0; i < 2; i++) permission *= Field.examination(X, Y + i);
		for (short i = 0; i < 2; i++) permission *= Field.examination(X - 1, Y + 1 + i);
	}
	if (orientation == '3') {
		for (short i = 0; i < 2; i++) permission *= Field.examination(X + i, Y);
		for (short i = 0; i < 2; i++) permission *= Field.examination(X - 1 + i, Y - 1);
	}
	if (orientation == '4') {
		for (short i = 0; i < 2; i++) permission *= Field.examination(X, Y + i);
		for (short i = 0; i < 2; i++) permission *= Field.examination(X + 1, Y - 1 + i);
	}
	return !permission;
}
void Figure_z::write_figure() // Запись положения фигуры в игровое поле по завершению движения
{
	switch (orientation)
	{
	case '1':
		for (short i = 0; i < 2; i++)
			Field.inpt_data_field(X + i, Y, color);
		for (short i = 0; i < 2; i++)
			Field.inpt_data_field(X + 1 + i, Y + 1, color);
		break;
	case '2':
		for (short i = 0; i < 2; i++)
			Field.inpt_data_field(X, Y + i, color);
		for (short i = 0; i < 2; i++)
			Field.inpt_data_field(X - 1, Y + 1 + i, color);
		break;
	case '3':
		for (short i = 0; i < 2; i++)
			Field.inpt_data_field(X + i, Y, color);
		for (short i = 0; i < 2; i++)
			Field.inpt_data_field(X - 1 + i, Y - 1, color);
		break;
	case '4':
		for (short i = 0; i < 2; i++)
			Field.inpt_data_field(X, Y + i, color);
		for (short i = 0; i < 2; i++)
			Field.inpt_data_field(X + 1, Y - 1 + i, color);
		break;
	default:
		throw Exception(messenge_Figure_z_write_figure);
		break;
	}
	if (finich)
		Field.set_score_level(); // После записи фигуры, проверяем заполняемость полос и обновляем счет очков игрока
}

Figure_tetris::Exception::Exception(TCHAR messenge[])
{
	int i = 0;
	while (i < (Size - 1) || messenge[i] != '\0')
		Messenge[i] = messenge[i++];
	Messenge[i] = '\0';
}
void Figure_tetris::Exception::PrintException()
{
	Graphics::paint_exception(Messenge);
}