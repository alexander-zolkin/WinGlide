#include "hotkeyhandler.h"

HotkeyHandler::HotkeyHandler(QObject *parent) : QObject(parent) {}

HotkeyHandler::~HotkeyHandler()
{
    unregisterHotKey();
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

bool HotkeyHandler::unregisterHotKey()
{
    UnregisterHotKey(nullptr, m_moveHotkeyId);
    UnregisterHotKey(nullptr, m_resizeHotkeyId);
    UnregisterHotKey(nullptr, m_escHotkeyId);
    return true;
}

bool HotkeyHandler::nativeEventFilter(const QByteArray &eventType, void *message, qintptr *result)
{
    MSG* msg = static_cast<MSG*>(message);
    if (msg->message == WM_HOTKEY)
    {
        if (msg->wParam == m_moveHotkeyId)
        {
            emit moveHotKeyPressed();
            return true;
        } else if (msg->wParam == m_resizeHotkeyId) {
            emit resizeHotKeyPressed();
            return true;
        } else if (msg->wParam == m_escHotkeyId) {
            emit escHotKeyPressed();
            return true;
        }
    }
    return false;
}
