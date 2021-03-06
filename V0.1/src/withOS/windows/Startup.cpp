//A startup in Windows, using WinAPI
//Build by C++Builder3.1, File->New->Consol Wizard-> windows(GUI)
//or Borland C++ 3.1 
#include <windows.h>
#include <condefs.h>
#include "rbltype.h"
#include "rblmain.h"
#pragma hdrstop
USEUNIT("test.c");
USEUNIT("..\..\osmain\R_TCB.C");
USEUNIT("..\..\osmain\R_main.c");
USEUNIT("..\..\osmain\R_MEM.C");
USEUNIT("..\..\osmain\R_MSG.C");
USEUNIT("..\..\osmain\R_PAT.C");
USEUNIT("..\..\osmain\R_PCB.C");
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

HWND	oshwnd;

LRESULT CALLBACK  WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;

    switch (message) {
    case WM_TIMER:
		handle_10ms();
		sch_proc();

    return 0;

    case WM_USER:
		sch_msg();

    return 0;

    case WM_CREATE:
		oshwnd=hwnd;
		SetTimer(hwnd,(UINT)0001,(UINT)0010,NULL);
		init_all();
    return 0;

    case WM_DESTROY:
    PostQuitMessage (0);
    return 0;
    }
    return DefWindowProc (hwnd, message, wParam, lParam);
}

extern "C"       //??*.c????????
{
void cli_int();
void sti_int();
WORD get_sp();
void set_sp(WORD sp);
void next_ret(WORD sp);
void send_ret();
}

void cli_int()
{
}
void sti_int()
{
}
WORD 	get_sp()
{
return 0;
}
void 	next_ret(WORD sp)
{

}
void 	next_ret()
{
}

void	send_ret()
{
	PostMessage(oshwnd, WM_USER, NULL, NULL);

}





