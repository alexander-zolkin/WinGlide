#include <windows.h>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include "hotkeyhandler.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    HotkeyHandler hotkeyHandler;
    QGuiApplication::instance()->installNativeEventFilter(&hotkeyHandler);

    hotkeyHandler.registerHotKey(MOD_WIN | MOD_ALT, 'V', 1);
    hotkeyHandler.registerHotKey(MOD_WIN | MOD_ALT, 'C', 2);

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("WinGlide", "Main");

    QObject::connect(&hotkeyHandler, &HotkeyHandler::moveHotKeyPressed, [&](){
        qDebug() << "Move hotkey pressed!";

        HWND hwnd = GetForegroundWindow();
        if (!hwnd) return;
        // SendMessage(hwnd, WM_SYSCOMMAND, SC_MOVE, 0);

        RECT window_rect;
        if (!GetWindowRect(hwnd, &window_rect)) return;

        // Getting the height of the window title
        const int title_height = GetSystemMetrics(SM_CYCAPTION) +
                                 GetSystemMetrics(SM_CYSIZEFRAME) +
                                 GetSystemMetrics(SM_CXPADDEDBORDER);

        // Calculating the coordinates of the center of the header
        const int center_x = (window_rect.left + window_rect.right) / 2;
        const int center_y = window_rect.top + (title_height / 2);

        // Setting the cursor position
        SetCursorPos(center_x, center_y);
        // Most likely it would be better to move window with mouse
        // SetWindowPos(hwnd, NULL, 100, 100, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

        INPUT inputs[2] = {0};

        // Clicking the left mouse button
        inputs[0].type = INPUT_MOUSE;
        inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

        SendInput(2, inputs, sizeof(INPUT));
    });

    QObject::connect(&hotkeyHandler, &HotkeyHandler::resizeHotKeyPressed, [&](){
        qDebug() << "Resize hotkey pressed!";

        HWND hwnd = GetForegroundWindow();
        if (!hwnd) return;

        RECT window_rect;
        if (!GetWindowRect(hwnd, &window_rect)) return;

        // Setting the cursor position
        SetCursorPos(window_rect.right - 1, window_rect.bottom - 1);

        INPUT inputs[2] = {0};

        // Clicking the left mouse button
        inputs[0].type = INPUT_MOUSE;
        inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

        SendInput(2, inputs, sizeof(INPUT));
    });

    return app.exec();
}
