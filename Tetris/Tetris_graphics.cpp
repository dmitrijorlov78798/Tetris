//Tetris_graphics

#include "Tetris_graphics.h"

// Сообщения для вывода на экран при возникновении исключения
TCHAR messenge_RegisterClassEx[32] = _T("Call to RegisterClassEx failed!"),
messenge_CreateWindow[29] = _T("Call to CreateWindow failed!");

// Размеры окна, координаты и размеры игрового поля 
const int kofX = 15, kofY = 15, // коэффициенты преобразования координат поля в пиксели
Xsizefield = kofX * Xsize, Ysizefield = kofY * Ysize, // размер поля в пикселях
Xsizewin = 14 * Xsizefield / 10, Ysizewin = 14 * Ysizefield / 10, // размер окна в пикселях
Xleft = (Xsizewin - Xsizefield) / 3, Xright = Xleft + Xsizefield,
Yup = (Ysizewin - Ysizefield) / 2, Ydown =Yup + Ysizefield; // координаты поля в пикселях
bool Graphics::exit_game = false; // Флаг закрытия окна мышью и необходимости выхода из игрового цикла
int Graphics::paint_end_game = 0; // Переменная координации прорисовки конца игры
char Graphics::press_key = '\0'; // Буфер последней нажатой клавиши
int Graphics::last_shot[Xsize][Ysize]; // Буфер последнего отрисованного кадра
// Определение цветов элемнтов окна
color_tetris
color_field(0, 0, 0), // цвет игрового поля
color_window(255, 255, 255), // цвет фона окна
color_frame(100, 100, 100), // цвет рамки игрового поля 
color_figure_line(255, 0, 0), // цвет фигуры линия
color_figure_square(0, 255, 0), // цвет фигуры квадрат
color_figure_t(0, 0, 255), // цвет фигуры т
color_figure_g(150, 150, 0), // цвет фигуры g
color_figure_z(0, 150, 150); // цвет фигуры z
// Опреденелие текста для вывода в окне
TCHAR tetris[7] = _T("TETRIS"), score[7] = _T("score:"), record_score[14] = _T("record_score:"), level[7] = _T("level:"),
answer_new_game[31] = _T("GAME OVER, start new game? y/n"),
score_number[16] = { '/0' }, record_score_number[16] = { '/0' }, level_number[16] = { '/0' }; // текст в окне
// Определение объектов для работы с окном
PAINTSTRUCT ps; // экземпляр структуры графического вывода
HDC hdc; // контекст устройства
HBRUSH hBrush_field, hBrush_window, hBrush_line, hBrush_square, hBrush_t, hBrush_g, hBrush_z; // кисть
HPEN hPen_frame, hPen_figure; // перо
HWND hWnd; // дескриптор окна
MSG msg; // сообщения от системы


// Определение процедуры обработки событий окна
LRESULT CALLBACK WndProc(_In_ HWND hWnd, _In_ UINT message, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT :   // Системная прорисовка
		hdc = BeginPaint(hWnd, &ps); 
		Graphics::paint_for_system(); 
		EndPaint(hWnd, &ps); 
		break;
	case WM_DESTROY :  // Уничтожение окна
		Graphics::exit_window(); 
		PostQuitMessage(0);
		break;
	case WM_TIMER :  // Покадровая игровая прорисовка
		hdc = GetDC(hWnd);
		Graphics::paint_for_game();
		ReleaseDC(hWnd, hdc);
		break;
	default :
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
	return 0;
} 

// Определение методов Graphics
Graphics::Graphics(HINSTANCE hInstance, int nCmdShow)  // Конструктор
{
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc; //указатель на функцию окна
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;  //идентификатор текущего приложения
	wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW); // загружаем курсор
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); //цвет фона окна
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = tetris; // имя программы
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

	hInst = hInstance;
	if (!RegisterClassEx(&wcex))  //регистрация окна
	{
		throw Exception(messenge_RegisterClassEx);
		return;
	}
	hWnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, _T("Tetris"), // имя программы
		_T("Tetris"), //заголовок окна 
		WS_OVERLAPPEDWINDOW, // стиль окна - перекрывающееся
		CW_USEDEFAULT, // положение окна по Х 
		CW_USEDEFAULT, // положение ока по У
		Xsizewin, // ширина 
		Ysizewin, // высота
		NULL, // идентификатор родительского окна
		NULL, // идентификатор меню
		hInstance, // идентификатор экземпляра программы
		NULL // отсутствие дополнительных параметров
	); // создание окна
	if (!hWnd)  
	{
		throw Exception(messenge_CreateWindow);
		return;
	}
	else
	{
		ShowWindow(hWnd, nCmdShow); // делаем окно видимым
		UpdateWindow(hWnd);
	}
	SetTimer(hWnd, 1, 25, NULL);  // Создаем таймер для игровой прорисовки
	create_win_obj();
	for (short x = 0; x < Xsize; x++)  // Инициализация буфера последнего кадра
		for (short y = 0; y < Ysize; y++)
			last_shot[x][y] = -1;
}
Graphics::~Graphics()
{
	delete_win_obj();
	KillTimer(hWnd, 1);  // Уничтожаем таймер для игровой прорисовки
}
void Graphics::create_win_obj()
{
	//задаем кисти
	hBrush_field = CreateSolidBrush(RGB(color_field.R, color_field.G, color_field.B));
	hBrush_window = CreateSolidBrush(RGB(color_window.R, color_window.G, color_window.B));
	hBrush_line = CreateSolidBrush(RGB(color_figure_line.R, color_figure_line.G, color_figure_line.B));
	hBrush_square = CreateSolidBrush(RGB(color_figure_square.R, color_figure_square.G, color_figure_square.B));
	hBrush_t = CreateSolidBrush(RGB(color_figure_t.R, color_figure_t.G, color_figure_t.B));
	hBrush_g = CreateSolidBrush(RGB(color_figure_g.R, color_figure_g.G, color_figure_g.B));
	hBrush_z = CreateSolidBrush(RGB(color_figure_z.R, color_figure_z.G, color_figure_z.B));
	// задаем перья
	hPen_frame = CreatePen(PS_SOLID, 10, RGB(color_frame.R, color_frame.G, color_frame.B));
	hPen_figure = CreatePen(PS_SOLID, 1, RGB(color_field.R, color_field.G, color_field.B));
}
void Graphics::delete_win_obj()
{
	// удаление кистей
	DeleteObject(hBrush_field);
	DeleteObject(hBrush_window);
	DeleteObject(hBrush_line);
	DeleteObject(hBrush_square);
	DeleteObject(hBrush_t);
	DeleteObject(hBrush_g);
	DeleteObject(hBrush_z);
	// удаление перьев
	DeleteObject(hPen_frame);
	DeleteObject(hPen_figure);
}
void Graphics::destroy_win()
{
	DestroyWindow(hWnd); // Отправляем сообщение системе об уничтожении окна, при выходе из игры
}
void Graphics::exit_window()
{
	exit_game = true; // Заканчиваем игру после закрытия окна
}
bool Graphics::getmsg() // функция получения сообщения от системы
{
	if (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		return !exit_game; // Если по логике игры происходит выход из игры, функция возвращает 0 для прерывания цикла
	}
	else
		return false; 
}
void Graphics::paint_square(int X, int Y, int Color) // Вывести квадрат фигурки на экран на позиции Х, У
{
	SelectObject(hdc, hPen_figure); // Выбираем перо
	switch (Color) // Выбираем кисти
	{
	case 0 :
		SelectObject(hdc, hBrush_field);
		break;
	case 1 :
		SelectObject(hdc, hBrush_line);
		break;
	case 2 :
		SelectObject(hdc, hBrush_square);
		break;
	case 3 :
		SelectObject(hdc, hBrush_t);
		break;
	case 4 :
		SelectObject(hdc, hBrush_g);
		break;
	case 5 :
		SelectObject(hdc, hBrush_z);
		break;
	default :
		return;
	}
	Rectangle(hdc, (Xleft + kofX * X), (Yup + kofY * Y), (Xleft + kofX * (X + 1)), (Yup + kofY * (Y + 1))); //прямоугольник залитый
	ValidateRect(hWnd, NULL); //обнавляем окно
}
void Graphics::paint_text()
{   //  Вывод текста
	SetTextColor(hdc, RGB(color_frame.R, color_frame.G, color_frame.B));
	TextOut(hdc, (Xsizewin * 0.38), (Ysizewin * 0.03), tetris, _tcslen(tetris));
	SetTextColor(hdc, RGB(color_figure_t.R, color_figure_t.G, color_figure_t.B));
	TextOut(hdc, (Xsizewin * 0.06), (Ysizewin * 0.07), score, _tcslen(score));
	TextOut(hdc, (Xsizewin * 0.3), (Ysizewin * 0.07), level, _tcslen(level));
	TextOut(hdc, (Xsizewin * 0.5), (Ysizewin * 0.07), record_score, _tcslen(record_score));
	// Преобразование переменных в текст
	_stprintf_s(score_number, TEXT("%d"), Playing_field::return_score());
	_stprintf_s(level_number, TEXT("%d"), Playing_field::return_level());
	_stprintf_s(record_score_number, TEXT("%d"), Playing_field::return_score_record());
	// Вывод переменных
	SetTextColor(hdc, RGB(color_figure_line.R, color_figure_line.G, color_figure_line.B));
	TextOut(hdc, (Xsizewin * 0.21), (Ysizewin * 0.07), score_number, _tcslen(score_number));
	TextOut(hdc, (Xsizewin * 0.44), (Ysizewin * 0.07), level_number, _tcslen(level_number));
	TextOut(hdc, (Xsizewin * 0.8), (Ysizewin * 0.07), record_score_number, _tcslen(record_score_number));
	if (paint_end_game == 1) // если игра окончена, необходимо спросить игрока о ее перезапуске
	{
		SetTextColor(hdc, RGB(color_figure_line.R, color_figure_line.G, color_figure_line.B));
		TextOut(hdc, (Xsizewin * 0.1), (Ysizewin * 0.4), answer_new_game, _tcslen(answer_new_game));
	}
}
void Graphics::paint_for_system() 
{	
	// Рисуем рамку игрового поля
	SelectObject(hdc, hBrush_window);
	Rectangle(hdc, 0, 0, Xsizewin, Ysizewin);
	SelectObject(hdc, hPen_frame);
	Rectangle(hdc, Xleft - 5, Yup - 5, Xright + 5, Ydown + 5);
	// Рисуем фигуры
	for (short x = 0; x < Xsize; x++)
		for (short y = 0; y < Ysize; y++)
			paint_square(x, y, Playing_field::return_data_field(x, y));
	
	paint_text(); // Рисуем текст
	ValidateRect(hWnd, NULL); //обнавляем окно
	
}
void Graphics::paint_for_game()
{
	if (last_shot[1][1] == -1) // Если кадр первый, то рисуум рамку игрового поля
	{   
		SelectObject(hdc, hBrush_window);
		Rectangle(hdc, 0, 0, Xsizewin, Ysizewin);
		SelectObject(hdc, hPen_frame);
		Rectangle(hdc, Xleft - 5, Yup - 5, Xright + 5, Ydown + 5);
	}
	if (paint_end_game == 2)  // Если игрок выбрал перезапуск игры, необходимо закрасить текст вопроса о перезапуске
	{
		SelectObject(hdc, hBrush_window);
		Rectangle(hdc, 0, 0, Xsizewin, Ysizewin);
		SelectObject(hdc, hPen_frame);
		Rectangle(hdc, Xleft - 5, Yup - 5, Xright + 5, Ydown + 5);
		for (short x = 0; x < Xsize; x++)
			for (short y = 0; y < Ysize; y++)
				paint_square(x, y, Playing_field::return_data_field(x, y));
		paint_end_game = 0;  
	}
	// Если кадр не первый, Рисуем изменения по сравнению с последним кадром, затем перезаписываем последний кадр
	for (short x = 0; x < Xsize; x++)
		for (short y = 0; y < Ysize; y++)
			if (last_shot[x][y] != Playing_field::return_data_field(x, y))
			{
				paint_square(x, y, Playing_field::return_data_field(x, y));
				last_shot[x][y] = Playing_field::return_data_field(x, y);
			}
	paint_text();
	ValidateRect(hWnd, NULL); //обнавляем окно
}
bool Graphics::events_press_key(char Key)
{
	if ((press_key != Key) && (GetAsyncKeyState(VkKeyScan(Key)) < 0)) // Если нажата новая клавиша равная аргументу, то возвращаем 1,
	{                                                                 // иначе, игнорируем нажатую клавишу 
		press_key = Key;                                              //чтобы избежать залипание клавиш
		return true;
	}
	else
	{                                                                 // Если нажата другая новая клавиша, возвращаем 0, и 
		if (!(GetAsyncKeyState(VkKeyScan(press_key)) < 0))            // сбрасываем буфер последней нажатой клавиши
			press_key = '\0';
		return false;
	}
}
void Graphics::end_game(int temp)
{
	paint_end_game = temp;
}
void Graphics::paint_exception(TCHAR messenge[])
{
	MessageBox(NULL, messenge, _T("Windows Desktop Guided Tour"), NULL); // Вывод сообщения исключения
}


Graphics::Exception::Exception(TCHAR messenge[])  // Класс исключения
{
	int i = 0;
	while (i < (Size - 1) || messenge[i] != '\0')
		Messenge[i] = messenge[i++];
	Messenge[i] = '\0';
}
void Graphics::Exception::PrintException()
{
	Graphics::paint_exception(Messenge);
}

