
#include <windows.h>
#pragma hdrstop
#include <condefs.h>


USEUNIT("r_func.c");
USEUNIT("r_main.c");
USEUNIT("t_main.c");
USEUNIT("..\osmain\r_msg.c");
USEUNIT("..\osmain\r_pat.c");
USEUNIT("..\osmain\r_pcb.c");
USEUNIT("..\osmain\r_tcb.c");
USEUNIT("..\osmain\t_tcb.c");
//---------------------------------------------------------------------------
#pragma argsused

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);

int PASCAL WinMain (HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpszCmdLine,int nCmdShow)
{
    WNDCLASS wc;
    HWND hwnd;
    MSG msg;

    if (hPrevInstance)
    return msg.wParam;

    wc.style = 0;                                   // Class style
    wc.lpfnWndProc = (WNDPROC) WndProc;             // Window procedure address
    wc.cbClsExtra = 0;                              // Class extra bytes
    wc.cbWndExtra = 0;                              // Window extra bytes
    wc.hInstance = hInstance;                       // Instance handle
    wc.hIcon = LoadIcon (NULL, IDI_APPLICATION);    // Icon handle
    wc.hCursor = LoadCursor (NULL, IDC_ARROW);      // Cursor handle
    wc.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1); // Background color
    wc.lpszMenuName = NULL;                         // Menu name
    wc.lpszClassName = "MyWndClass";                // WNDCLASS name

    RegisterClass (&wc);
	

    hwnd = CreateWindow (
        "MyWndClass",               // WNDCLASS name
        "RBLOS in Windows",          // Window title
        WS_OVERLAPPEDWINDOW,        // Window style
        CW_USEDEFAULT,              // Horizontal position
        CW_USEDEFAULT,              // Vertical position        
        CW_USEDEFAULT,              // Initial width
        CW_USEDEFAULT,              // Initial height
        HWND_DESKTOP,               // Handle of parent window
        NULL,                       // Menu handle
        hInstance,                  // Application's instance handle
        NULL                        // Window-creation data
    );

    ShowWindow (hwnd, nCmdShow);
    UpdateWindow (hwnd);

    while (GetMessage (&msg, NULL, 0, 0)) {
        TranslateMessage (&msg);
        DispatchMessage (&msg);
    }
    return msg.wParam;
}

//---------------------------------------------------------------------------
extern "C"  //被C++编译器调用
{
extern void main_ini(void);
extern void main_10ms(void);
extern void main_msg(void);
}

HWND	oshwnd;

LRESULT CALLBACK  WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;

    switch (message) {
    case WM_TIMER:
		main_10ms();

    return 0;

    case WM_USER:
		main_msg();

    return 0;

    case WM_CREATE:
		oshwnd=hwnd;
		SetTimer(hwnd,(UINT)0001,(UINT)0010,NULL);
		main_ini();
    return 0;

    case WM_DESTROY:
    PostQuitMessage (0);
    return 0;
    }
    return DefWindowProc (hwnd, message, wParam, lParam);
}

extern "C"       //被*.c文件调用
{
void send_ret();
}

void	send_ret()
{
	PostMessage(oshwnd, WM_USER, NULL, NULL);
}

