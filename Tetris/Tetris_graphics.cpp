//Tetris_graphics

#include "Tetris_graphics.h"

// ��������� ��� ������ �� ����� ��� ������������� ����������
TCHAR messenge_RegisterClassEx[32] = _T("Call to RegisterClassEx failed!"),
messenge_CreateWindow[29] = _T("Call to CreateWindow failed!");

// ������� ����, ���������� � ������� �������� ���� 
const int kofX = 15, kofY = 15, // ������������ �������������� ��������� ���� � �������
Xsizefield = kofX * Xsize, Ysizefield = kofY * Ysize, // ������ ���� � ��������
Xsizewin = 14 * Xsizefield / 10, Ysizewin = 14 * Ysizefield / 10, // ������ ���� � ��������
Xleft = (Xsizewin - Xsizefield) / 3, Xright = Xleft + Xsizefield,
Yup = (Ysizewin - Ysizefield) / 2, Ydown =Yup + Ysizefield; // ���������� ���� � ��������
bool Graphics::exit_game = false; // ���� �������� ���� ����� � ������������� ������ �� �������� �����
int Graphics::paint_end_game = 0; // ���������� ����������� ���������� ����� ����
char Graphics::press_key = '\0'; // ����� ��������� ������� �������
int Graphics::last_shot[Xsize][Ysize]; // ����� ���������� ������������� �����
// ����������� ������ �������� ����
color_tetris
color_field(0, 0, 0), // ���� �������� ����
color_window(255, 255, 255), // ���� ���� ����
color_frame(100, 100, 100), // ���� ����� �������� ���� 
color_figure_line(255, 0, 0), // ���� ������ �����
color_figure_square(0, 255, 0), // ���� ������ �������
color_figure_t(0, 0, 255), // ���� ������ �
color_figure_g(150, 150, 0), // ���� ������ g
color_figure_z(0, 150, 150); // ���� ������ z
// ����������� ������ ��� ������ � ����
TCHAR tetris[7] = _T("TETRIS"), score[7] = _T("score:"), record_score[14] = _T("record_score:"), level[7] = _T("level:"),
answer_new_game[31] = _T("GAME OVER, start new game? y/n"),
score_number[16] = { '/0' }, record_score_number[16] = { '/0' }, level_number[16] = { '/0' }; // ����� � ����
// ����������� �������� ��� ������ � �����
PAINTSTRUCT ps; // ��������� ��������� ������������ ������
HDC hdc; // �������� ����������
HBRUSH hBrush_field, hBrush_window, hBrush_line, hBrush_square, hBrush_t, hBrush_g, hBrush_z; // �����
HPEN hPen_frame, hPen_figure; // ����
HWND hWnd; // ���������� ����
MSG msg; // ��������� �� �������


// ����������� ��������� ��������� ������� ����
LRESULT CALLBACK WndProc(_In_ HWND hWnd, _In_ UINT message, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT :   // ��������� ����������
		hdc = BeginPaint(hWnd, &ps); 
		Graphics::paint_for_system(); 
		EndPaint(hWnd, &ps); 
		break;
	case WM_DESTROY :  // ����������� ����
		Graphics::exit_window(); 
		PostQuitMessage(0);
		break;
	case WM_TIMER :  // ���������� ������� ����������
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

// ����������� ������� Graphics
Graphics::Graphics(HINSTANCE hInstance, int nCmdShow)  // �����������
{
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc; //��������� �� ������� ����
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;  //������������� �������� ����������
	wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW); // ��������� ������
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); //���� ���� ����
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = tetris; // ��� ���������
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

	hInst = hInstance;
	if (!RegisterClassEx(&wcex))  //����������� ����
	{
		throw Exception(messenge_RegisterClassEx);
		return;
	}
	hWnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, _T("Tetris"), // ��� ���������
		_T("Tetris"), //��������� ���� 
		WS_OVERLAPPEDWINDOW, // ����� ���� - ���������������
		CW_USEDEFAULT, // ��������� ���� �� � 
		CW_USEDEFAULT, // ��������� ��� �� �
		Xsizewin, // ������ 
		Ysizewin, // ������
		NULL, // ������������� ������������� ����
		NULL, // ������������� ����
		hInstance, // ������������� ���������� ���������
		NULL // ���������� �������������� ����������
	); // �������� ����
	if (!hWnd)  
	{
		throw Exception(messenge_CreateWindow);
		return;
	}
	else
	{
		ShowWindow(hWnd, nCmdShow); // ������ ���� �������
		UpdateWindow(hWnd);
	}
	SetTimer(hWnd, 1, 25, NULL);  // ������� ������ ��� ������� ����������
	create_win_obj();
	for (short x = 0; x < Xsize; x++)  // ������������� ������ ���������� �����
		for (short y = 0; y < Ysize; y++)
			last_shot[x][y] = -1;
}
Graphics::~Graphics()
{
	delete_win_obj();
	KillTimer(hWnd, 1);  // ���������� ������ ��� ������� ����������
}
void Graphics::create_win_obj()
{
	//������ �����
	hBrush_field = CreateSolidBrush(RGB(color_field.R, color_field.G, color_field.B));
	hBrush_window = CreateSolidBrush(RGB(color_window.R, color_window.G, color_window.B));
	hBrush_line = CreateSolidBrush(RGB(color_figure_line.R, color_figure_line.G, color_figure_line.B));
	hBrush_square = CreateSolidBrush(RGB(color_figure_square.R, color_figure_square.G, color_figure_square.B));
	hBrush_t = CreateSolidBrush(RGB(color_figure_t.R, color_figure_t.G, color_figure_t.B));
	hBrush_g = CreateSolidBrush(RGB(color_figure_g.R, color_figure_g.G, color_figure_g.B));
	hBrush_z = CreateSolidBrush(RGB(color_figure_z.R, color_figure_z.G, color_figure_z.B));
	// ������ �����
	hPen_frame = CreatePen(PS_SOLID, 10, RGB(color_frame.R, color_frame.G, color_frame.B));
	hPen_figure = CreatePen(PS_SOLID, 1, RGB(color_field.R, color_field.G, color_field.B));
}
void Graphics::delete_win_obj()
{
	// �������� ������
	DeleteObject(hBrush_field);
	DeleteObject(hBrush_window);
	DeleteObject(hBrush_line);
	DeleteObject(hBrush_square);
	DeleteObject(hBrush_t);
	DeleteObject(hBrush_g);
	DeleteObject(hBrush_z);
	// �������� ������
	DeleteObject(hPen_frame);
	DeleteObject(hPen_figure);
}
void Graphics::destroy_win()
{
	DestroyWindow(hWnd); // ���������� ��������� ������� �� ����������� ����, ��� ������ �� ����
}
void Graphics::exit_window()
{
	exit_game = true; // ����������� ���� ����� �������� ����
}
bool Graphics::getmsg() // ������� ��������� ��������� �� �������
{
	if (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		return !exit_game; // ���� �� ������ ���� ���������� ����� �� ����, ������� ���������� 0 ��� ���������� �����
	}
	else
		return false; 
}
void Graphics::paint_square(int X, int Y, int Color) // ������� ������� ������� �� ����� �� ������� �, �
{
	SelectObject(hdc, hPen_figure); // �������� ����
	switch (Color) // �������� �����
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
	Rectangle(hdc, (Xleft + kofX * X), (Yup + kofY * Y), (Xleft + kofX * (X + 1)), (Yup + kofY * (Y + 1))); //������������� �������
	ValidateRect(hWnd, NULL); //��������� ����
}
void Graphics::paint_text()
{   //  ����� ������
	SetTextColor(hdc, RGB(color_frame.R, color_frame.G, color_frame.B));
	TextOut(hdc, (Xsizewin * 0.38), (Ysizewin * 0.03), tetris, _tcslen(tetris));
	SetTextColor(hdc, RGB(color_figure_t.R, color_figure_t.G, color_figure_t.B));
	TextOut(hdc, (Xsizewin * 0.06), (Ysizewin * 0.07), score, _tcslen(score));
	TextOut(hdc, (Xsizewin * 0.3), (Ysizewin * 0.07), level, _tcslen(level));
	TextOut(hdc, (Xsizewin * 0.5), (Ysizewin * 0.07), record_score, _tcslen(record_score));
	// �������������� ���������� � �����
	_stprintf_s(score_number, TEXT("%d"), Playing_field::return_score());
	_stprintf_s(level_number, TEXT("%d"), Playing_field::return_level());
	_stprintf_s(record_score_number, TEXT("%d"), Playing_field::return_score_record());
	// ����� ����������
	SetTextColor(hdc, RGB(color_figure_line.R, color_figure_line.G, color_figure_line.B));
	TextOut(hdc, (Xsizewin * 0.21), (Ysizewin * 0.07), score_number, _tcslen(score_number));
	TextOut(hdc, (Xsizewin * 0.44), (Ysizewin * 0.07), level_number, _tcslen(level_number));
	TextOut(hdc, (Xsizewin * 0.8), (Ysizewin * 0.07), record_score_number, _tcslen(record_score_number));
	if (paint_end_game == 1) // ���� ���� ��������, ���������� �������� ������ � �� �����������
	{
		SetTextColor(hdc, RGB(color_figure_line.R, color_figure_line.G, color_figure_line.B));
		TextOut(hdc, (Xsizewin * 0.1), (Ysizewin * 0.4), answer_new_game, _tcslen(answer_new_game));
	}
}
void Graphics::paint_for_system() 
{	
	// ������ ����� �������� ����
	SelectObject(hdc, hBrush_window);
	Rectangle(hdc, 0, 0, Xsizewin, Ysizewin);
	SelectObject(hdc, hPen_frame);
	Rectangle(hdc, Xleft - 5, Yup - 5, Xright + 5, Ydown + 5);
	// ������ ������
	for (short x = 0; x < Xsize; x++)
		for (short y = 0; y < Ysize; y++)
			paint_square(x, y, Playing_field::return_data_field(x, y));
	
	paint_text(); // ������ �����
	ValidateRect(hWnd, NULL); //��������� ����
	
}
void Graphics::paint_for_game()
{
	if (last_shot[1][1] == -1) // ���� ���� ������, �� ������ ����� �������� ����
	{   
		SelectObject(hdc, hBrush_window);
		Rectangle(hdc, 0, 0, Xsizewin, Ysizewin);
		SelectObject(hdc, hPen_frame);
		Rectangle(hdc, Xleft - 5, Yup - 5, Xright + 5, Ydown + 5);
	}
	if (paint_end_game == 2)  // ���� ����� ������ ���������� ����, ���������� ��������� ����� ������� � �����������
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
	// ���� ���� �� ������, ������ ��������� �� ��������� � ��������� ������, ����� �������������� ��������� ����
	for (short x = 0; x < Xsize; x++)
		for (short y = 0; y < Ysize; y++)
			if (last_shot[x][y] != Playing_field::return_data_field(x, y))
			{
				paint_square(x, y, Playing_field::return_data_field(x, y));
				last_shot[x][y] = Playing_field::return_data_field(x, y);
			}
	paint_text();
	ValidateRect(hWnd, NULL); //��������� ����
}
bool Graphics::events_press_key(char Key)
{
	if ((press_key != Key) && (GetAsyncKeyState(VkKeyScan(Key)) < 0)) // ���� ������ ����� ������� ������ ���������, �� ���������� 1,
	{                                                                 // �����, ���������� ������� ������� 
		press_key = Key;                                              //����� �������� ��������� ������
		return true;
	}
	else
	{                                                                 // ���� ������ ������ ����� �������, ���������� 0, � 
		if (!(GetAsyncKeyState(VkKeyScan(press_key)) < 0))            // ���������� ����� ��������� ������� �������
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
	MessageBox(NULL, messenge, _T("Windows Desktop Guided Tour"), NULL); // ����� ��������� ����������
}


Graphics::Exception::Exception(TCHAR messenge[])  // ����� ����������
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

