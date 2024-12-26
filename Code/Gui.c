#include <stdio.h>
#include <windows.h>
#include "Settings.h"
#include "System.c"

/*Sub Procedures*/
// How the button should behave when pressed :P
void HandleButtonPress(HWND hwnd, WPARAM wParam) {
    int buttonID = LOWORD(wParam);
    HWND hButton = GetDlgItem(hwnd, buttonID);
    
    if (!hButton) return;
    if (GetWindowTextLength(hButton) > 0) return;
    
    printf("Button %d was pressed!\n", buttonID);
    Gameplay(hwnd, hButton, buttonID);
}

// Window procedure (callback function)
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_COMMAND:
            HandleButtonPress(hwnd, wParam);
            return 0;
        case WM_CLOSE:                        // when the window is closed (by the user :P)
            DestroyWindow(hwnd);             // destroy the window COMPLETELY ⚡⚡
            return 0;
        case WM_DESTROY:                     // when the window is destroyed
            PostQuitMessage(0);             // tell Windows we're done :P
            return 0;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

// Create the main window (as the name suggests :P)
HWND CreateMainWindow(HINSTANCE hInstance, int nCmdShow) {
    // register the window class (to setup how the window should behave)
    WNDCLASSEX wc = {0};
    
    wc.cbSize           = sizeof(WNDCLASSEX);               // size of the class ig? I don't know
    wc.style            = CS_HREDRAW | CS_VREDRAW;          // the "style" of the window
    wc.lpfnWndProc      = WindowProc;                       // handle to the window procedure (like clicks, keystrokes, ect)
    wc.hInstance        = hInstance;                        // instance of the application
    wc.hIcon            = LoadIcon(NULL, IDI_APPLICATION);  // ig the icon of the window
    wc.hCursor          = LoadCursor(NULL, IDC_ARROW);      // cursor of the window
    wc.hbrBackground    = (HBRUSH)(COLOR_WINDOW + 1);       // the background color of the window
    wc.lpszClassName    = "TClass";                         // name of the window class (referenced in the settings)
    wc.hIconSm          = LoadIcon(NULL, IDI_APPLICATION);  // that silly lil icon of the window :P

    // we send them to the gulac if it's missbehaving
    if (!RegisterClassEx(&wc)) { 
        MessageBox(NULL, "Window registration failed!", "Error", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    HWND hwind = CreateWindowEx(
        WINDOW_EX_STYLE,
        "TClass",
        WINDOW_TITLE,
        WINDOW_STYLE,
        CW_USEDEFAULT, CW_USEDEFAULT,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        NULL, NULL, hInstance, NULL
    );

    if (hwind) {
        ShowWindow(hwind, nCmdShow);
        UpdateWindow(hwind);
    }

    return hwind;
}

// Create a function to make a button (just to simplify the process of making buttons)
HWND CreateButton(HWND hwndParent, HINSTANCE hInstance, int ID_BUTTON, int x, int y, int w, int h, LPCSTR text) {
    if (!text) { text = "0"; };
    DWORD style = WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON;
    
    HWND hButton = CreateWindow(
        "BUTTON",
        text,
        style,
        x, y, w, h,
        hwndParent,
        (HMENU)ID_BUTTON,
        hInstance,
        NULL
    );

    return hButton;
}


/* MAIN */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    HWND hwind = CreateMainWindow(hInstance, nCmdShow);
    if (!hwind) return 0;

    HWND B0 = CreateButton(hwind, hInstance, 1, 100, 100, 100, 100, "");
    HWND B1 = CreateButton(hwind, hInstance, 2, 200, 100, 100, 100, "");
    HWND B2 = CreateButton(hwind, hInstance, 3, 300, 100, 100, 100, "");

    HWND B3 = CreateButton(hwind, hInstance, 4, 100, 200, 100, 100, "");
    HWND B4 = CreateButton(hwind, hInstance, 5, 200, 200, 100, 100, "");
    HWND B5 = CreateButton(hwind, hInstance, 6, 300, 200, 100, 100, "");

    HWND B6 = CreateButton(hwind, hInstance, 7, 100, 300, 100, 100, "");
    HWND B7 = CreateButton(hwind, hInstance, 8, 200, 300, 100, 100, "");
    HWND B8 = CreateButton(hwind, hInstance, 9, 300, 300, 100, 100, "");
    
    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}