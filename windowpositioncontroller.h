#ifndef WINDOWPOSITIONCONTROLLER_H
#define WINDOWPOSITIONCONTROLLER_H

#include <QObject>
#include <QTimer>
#include <windows.h>

class WindowPositionController : public QObject
{
    Q_OBJECT

public:
    static WindowPositionController& getInstance();

    WindowPositionController(const WindowPositionController&) = delete;
    WindowPositionController& operator=(const WindowPositionController&) = delete;

signals:

public slots:
    void moveWindow();
    void resizeWindow();
    void onEsc();

private slots:
    void onResizeTimeout();
    void onMoveTimeout();

private:
    explicit WindowPositionController(QObject *parent = nullptr);
    static const int timerInterval = 10;
    static const int windowEdgeOffset = 10;
    
    QTimer positionControllTimer;
    
    bool getWindowHandle(HWND& hwnd, RECT& rect) const;
    bool updateCursorPosition(POINT& pt) const;
    void stopAllTimers();
};

#endif // WINDOWPOSITIONCONTROLLER_H
