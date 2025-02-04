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

protected:
    bool nativeEventFilter(const QByteArray &eventType, void *message, qintptr *result) override;

private:
    int m_moveHotkeyId = 1; // Уникальный ID для горячей клавиши
    int m_resizeHotkeyId = 2; // Уникальный ID для горячей клавиши
};

#endif // HOTKEYHANDLER_H
