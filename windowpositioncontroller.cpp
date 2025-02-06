    #include <windows.h>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QTimer>
#include "windowpositioncontroller.h"

WindowPositionController& WindowPositionController::getInstance()
{
    static WindowPositionController instance;
    return instance;
}

WindowPositionController::WindowPositionController(QObject *parent)
    : QObject{parent}
{
    positionControllTimer.setInterval(timerInterval);
}

void WindowPositionController::onResizeTimeout()
{
    qDebug() << "Resize timer!";

    HWND hwnd = GetForegroundWindow();
    if (!hwnd) return;

    RECT window_rect;
    if (!GetWindowRect(hwnd, &window_rect)) return;

    POINT pt;
    if (GetCursorPos(&pt)) {
        qDebug() << "Mouse position:" << pt.x << pt.y;
        SetWindowPos(hwnd, NULL, window_rect.left, window_rect.top, pt.x - window_rect.left + windowEdgeOffset,
                     pt.y - window_rect.top + windowEdgeOffset, SWP_NOZORDER);
    }
}

void WindowPositionController::onMoveTimeout()
{
    qDebug() << "Move timer!";

    HWND hwnd = GetForegroundWindow();
    if (!hwnd) return;

    RECT window_rect;
    if (!GetWindowRect(hwnd, &window_rect)) return;

    POINT pt;
    if (GetCursorPos(&pt)) {
        qDebug() << "Mouse position:" << pt.x << pt.y;
        int windowWidth = window_rect.right - window_rect.left;
        int windowHeight = window_rect.bottom - window_rect.top;
        SetWindowPos(hwnd, NULL, pt.x - windowWidth / 2, pt.y - windowHeight / 2, window_rect.right - window_rect.left,
                     window_rect.bottom - window_rect.top, SWP_NOZORDER);
    }
}

void WindowPositionController::resizeWindow()
{
    qDebug() << "Resize hotkey pressed!";

    HWND hwnd = GetForegroundWindow();
    if (!hwnd) return;

    RECT window_rect;
    if (!GetWindowRect(hwnd, &window_rect)) return;

    SetCursorPos(window_rect.right - windowEdgeOffset, window_rect.bottom - windowEdgeOffset);

    QObject::connect(&positionControllTimer, &QTimer::timeout, this, &WindowPositionController::onResizeTimeout);

    if (!positionControllTimer.isActive()) {
        positionControllTimer.start();
    }
}

void WindowPositionController::onEsc()
{
    qDebug() << "Esc hotkey pressed!";
    QObject::disconnect(&positionControllTimer, &QTimer::timeout, this, &WindowPositionController::onResizeTimeout);
    QObject::disconnect(&positionControllTimer, &QTimer::timeout, this, &WindowPositionController::onMoveTimeout);
    positionControllTimer.stop();
}

void WindowPositionController::moveWindow()
{
    qDebug() << "Move hotkey pressed!";

    HWND hwnd = GetForegroundWindow();
    if (!hwnd) return;

    RECT window_rect;
    if (!GetWindowRect(hwnd, &window_rect)) return;

    int windowWidth = window_rect.right - window_rect.left;
    int windowHeight = window_rect.bottom - window_rect.top;
    SetCursorPos(window_rect.left + windowWidth / 2, window_rect.top + windowHeight / 2);

    QObject::connect(&positionControllTimer, &QTimer::timeout, this, &WindowPositionController::onMoveTimeout);

    if (!positionControllTimer.isActive()) {
        positionControllTimer.start();
    }
}
