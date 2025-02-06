#include "hotkeyhandler.h"

HotkeyHandler& HotkeyHandler::getInstance()
{
    static HotkeyHandler instance;
    return instance;
}

HotkeyHandler::HotkeyHandler(QObject *parent) : QObject(parent) {}

HotkeyHandler::~HotkeyHandler()
{
    unregisterAllHotKeys();
}

bool HotkeyHandler::registerHotKey(int modifier, int key, unsigned hotkeyID)
{
    UINT fsModifiers = 0;
    if (modifier & MOD_ALT) fsModifiers |= MOD_ALT;
    if (modifier & MOD_CONTROL) fsModifiers |= MOD_CONTROL;
    if (modifier & MOD_SHIFT) fsModifiers |= MOD_SHIFT;
    if (modifier & MOD_WIN) fsModifiers |= MOD_WIN;

    bool registered = RegisterHotKey(
        nullptr,
        hotkeyID,
        fsModifiers,
        key
    );

    return registered;
}

bool HotkeyHandler::unregisterAllHotKeys()
{
    UnregisterHotKey(nullptr, moveHotkeyId);
    UnregisterHotKey(nullptr, resizeHotkeyId);
    UnregisterHotKey(nullptr, escHotkeyId);
    return true;
}

bool HotkeyHandler::nativeEventFilter(const QByteArray &eventType, void *message, qintptr *result)
{
    MSG* msg = static_cast<MSG*>(message);
    if (msg->message == WM_HOTKEY) {
        if (msg->wParam == moveHotkeyId) {
            emit moveHotKeyPressed();
            return true;
        } else if (msg->wParam == resizeHotkeyId) {
            emit resizeHotKeyPressed();
            return true;
        } else if (msg->wParam == escHotkeyId) {
            emit escHotKeyPressed();
            return true;
        }
    }

    return false;
}
