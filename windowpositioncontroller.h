#ifndef WINDOWPOSITIONCONTROLLER_H
#define WINDOWPOSITIONCONTROLLER_H

#include <QObject>
#include <QTimer>

class WindowPositionController : public QObject
{
    Q_OBJECT
public:
    explicit WindowPositionController(QObject *parent = nullptr);

signals:

public slots:
    void moveWindow();
    void resizeWindow();
    void onEsc();

private slots:
    void onResizeTimeout();
    void onMoveTimeout();

private:
    QTimer positionControllTimer;
};

#endif // WINDOWPOSITIONCONTROLLER_H
