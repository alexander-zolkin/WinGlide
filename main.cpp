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

    HotkeyHandler hotkeyHandler;
    QGuiApplication::instance()->installNativeEventFilter(&hotkeyHandler);

    WindowPositionController wpc;

    if (!hotkeyHandler.registerHotKey(MOD_WIN | MOD_ALT, 'V', 1)) {
        auto lastError = GetLastError();
        qDebug() << "Не удалось зарегистрировать горячую клавишу Win+Alt+V. Код ошибки:" << lastError;
    }

    if (!hotkeyHandler.registerHotKey(MOD_WIN | MOD_ALT, 'C', 2)) {
        auto lastError = GetLastError();
        qDebug() << "Не удалось зарегистрировать горячую клавишу Win+Alt+C. Код ошибки:" << lastError;
    }

    if (!hotkeyHandler.registerHotKey(0, VK_ESCAPE, 3)) {
        auto lastError = GetLastError();
        qDebug() << "Не удалось зарегистрировать горячую клавишу Escape. Код ошибки:" << lastError;
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
