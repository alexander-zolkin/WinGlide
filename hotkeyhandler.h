#ifndef HOTKEYHANDLER_H
#define HOTKEYHANDLER_H

#include <windows.h>
#include <QObject>
#include <QAbstractNativeEventFilter>

class HotkeyHandler : public QObject, public QAbstractNativeEventFilter
{
    Q_OBJECT
public:
    explicit HotkeyHandler(QObject *parent = nullptr);
    ~HotkeyHandler();

    bool registerHotKey(int modifier, int key, unsigned hotkeyID);
    bool unregisterHotKey();

signals:
    void moveHotKeyPressed();
    void resizeHotKeyPressed();
    void escHotKeyPressed();

protected:
    bool nativeEventFilter(const QByteArray &eventType, void *message, qintptr *result) override;

private:
    const int m_moveHotkeyId = 1;
    const int m_resizeHotkeyId = 2;
    const int m_escHotkeyId = 3;
};

#endif // HOTKEYHANDLER_H
