#ifndef HOTKEYHANDLER_H
#define HOTKEYHANDLER_H

#include <windows.h>
#include <QObject>
#include <QAbstractNativeEventFilter>

class HotkeyHandler : public QObject, public QAbstractNativeEventFilter
{
    Q_OBJECT

public:
    static const uint moveHotkeyId = 0;
    static const uint resizeHotkeyId = 1;
    static const uint escHotkeyId = 2;
    
    static HotkeyHandler& getInstance();
    
    bool registerHotKey(int modifier, int key, unsigned hotkeyID);
    bool unregisterAllHotKeys();

signals:
    void moveHotKeyPressed();
    void resizeHotKeyPressed();
    void escHotKeyPressed();

protected:
    bool nativeEventFilter(const QByteArray &eventType, void *message, qintptr *result) override;

private:
    explicit HotkeyHandler(QObject *parent = nullptr);
    ~HotkeyHandler();
    HotkeyHandler(const HotkeyHandler&) = delete;
    HotkeyHandler& operator=(const HotkeyHandler&) = delete;
};

#endif // HOTKEYHANDLER_H
