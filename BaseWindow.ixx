module;
#pragma once
#include <Windows.h>

export module BaseWindow;

export
template <class DerivedClass>
class BaseWindow {
 public:
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
        DerivedClass *pState = NULL;
        if (uMsg == WM_NCCREATE) {
            pState = (DerivedClass*) ((CREATESTRUCT*) lParam)->lpCreateParams;
            SetWindowLongPtrW(hwnd, GWLP_USERDATA, (LONG_PTR) pState);
            pState->hwnd = hwnd;
        }
        else {
            pState = (DerivedClass*) GetWindowLongPtrW(hwnd, GWLP_USERDATA);
        }

        if (pState) {
            return pState->HandleMessage(uMsg, wParam, lParam);
        } else {
            return DefWindowProcW(hwnd, uMsg, wParam, lParam);
        }
    }

    BaseWindow() : hwnd{NULL} {}

    bool Create(PCWSTR lpWindowName, DWORD dwStyle, DWORD dwExStyle = 0, int x = CW_USEDEFAULT, int y = CW_USEDEFAULT, int nWidth = CW_USEDEFAULT, int nHeight = CW_USEDEFAULT, HWND hWndParent = 0, HMENU hMenu = 0) {
        WNDCLASSW wc = {};
        wc.lpfnWndProc = DerivedClass::WindowProc;
        wc.hInstance = GetModuleHandleW(NULL);
        wc.lpszClassName = ClassName();
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);

        RegisterClassW(&wc);
        hwnd = CreateWindowExW(dwExStyle, ClassName(), lpWindowName, dwStyle, 
            x, y, nWidth, nHeight, 
            hWndParent, hMenu, GetModuleHandleW(NULL), this);

        return hwnd;
    }
    HWND Window() const {return hwnd;}
    HWND hwnd;
 protected:
    virtual PCWSTR ClassName() const = 0;
    virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
};