#include <windows.h>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QTimer>
#include "hotkeyhandler.h"
#include "windowpositioncontroller.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    HotkeyHandler& hotkeyHandler = HotkeyHandler::getInstance();
    QGuiApplication::instance()->installNativeEventFilter(&hotkeyHandler);
    WindowPositionController& wpc = WindowPositionController::getInstance();

    DWORD lastError;
    if (!hotkeyHandler.registerHotKey(MOD_WIN | MOD_ALT, 'V', HotkeyHandler::moveHotkeyId)) {
        lastError = GetLastError();
        qDebug() << "Can't register Win+Alt+V. Error code:" << lastError;
    }

    if (!hotkeyHandler.registerHotKey(MOD_WIN | MOD_ALT, 'C', HotkeyHandler::resizeHotkeyId)) {
        lastError = GetLastError();
        qDebug() << "Can't register Win+Alt+C. Error code:" << lastError;
    }

    if (!hotkeyHandler.registerHotKey(0, VK_ESCAPE, HotkeyHandler::escHotkeyId)) {
        lastError = GetLastError();
        qDebug() << "Can't register Escape. Error code:" << lastError;
    }

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("WinGlide", "Main");

    QObject::connect(&hotkeyHandler, &HotkeyHandler::moveHotKeyPressed, &wpc, &WindowPositionController::moveWindow);
    QObject::connect(&hotkeyHandler, &HotkeyHandler::resizeHotKeyPressed, &wpc, &WindowPositionController::resizeWindow);
    QObject::connect(&hotkeyHandler, &HotkeyHandler::escHotKeyPressed, &wpc, &WindowPositionController::onEsc);

    return app.exec();
}
