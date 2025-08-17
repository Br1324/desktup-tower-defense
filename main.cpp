#include <iostream>
#include <Windows.h>
#pragma comment(lib, "User32")
#pragma comment(lib, "Gdi32")
#include <d2d1.h> 
#pragma comment(lib, "d2d1")
#pragma comment(lib, "Ole32")
#include <wincodec.h>
#pragma comment(lib, "windowscodecs")
#include <array>
#include <list>
#include <memory>
#include <optional>
#include <string>
#include <vector>
#include <cmath>
#include <set>
#include <compare>
#include <numbers>
#include <map>

#include <windowsx.h>
#include <dwrite.h>
#pragma comment(lib, "Dwrite")
#include <winrt/base.h>
#pragma comment(lib, "oleaut32")
#include "BaseWindow.cpp"

#include "include/App.hpp"
#include "include/ConsoleOut.hpp"

#include "include/load-bitmap.cpp"
#include "include/draw-bitmap.cpp"
#include "classes/Bitmap.cpp"

#include "logic/prelogic.cpp"
#include "classes/Arrow.cpp"
#include "classes/Block.hpp"
#include "classes/Grid.cpp"
#include "classes/Enemy.hpp"
#include "classes/Tower.hpp"
#include "classes/Projectile.hpp"
#include "logic/rounds.cpp"
#include "logic/main-logic.cpp"
#include "logic/draw.cpp"
#include "include/App.cpp"
#include "classes/Enemy.cpp"
#include "classes/Tower.cpp"
#include "classes/Projectile.cpp"
#include "classes/Block.cpp"


#include "include/mouse-events.cpp"
#include "rendering/render-loop.cpp"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int nCmdShow) {
    AllocConsole();
    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    App window;
    ::window = &window;

    if (!window.Create(L"Template", WS_OVERLAPPEDWINDOW)) { return 0; }

    ShowWindow(window.hwnd, nCmdShow);

    BOOL bBool = FALSE;
    SetUserObjectInformationW(GetCurrentProcess(), UOI_TIMERPROC_EXCEPTION_SUPPRESSION, &bBool, sizeof(BOOL));
    SetTimer(window.hwnd, 0, logicInterval, nullptr);
    SetTimer(window.hwnd, 1, renderInterval, nullptr);

    MSG msg = {};
    while (GetMessageW(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    if (SUCCEEDED(hr)) { CoUninitialize(); }
    return 0;
}