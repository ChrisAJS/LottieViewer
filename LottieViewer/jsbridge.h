#ifndef JSBRIDGE_H
#define JSBRIDGE_H

#include <QObject>
#include <QString>

class JSBridge : public QObject
{
    Q_OBJECT
public:
    JSBridge(QObject *parent = nullptr);
    virtual ~JSBridge() {}
public slots:
    void animationLoaded(int frames, int frameRate);
    void enteredFrame(int frame);

signals:
    void displayAnimation(QString anim);
    void pauseAnimation();
    void playAnimation();
    void seekToFrame(int frame);
    void onAnimationLoaded(int frames, int frameRate);
    void onEnterFrame(int frame);
    void setSpeed(int speed);
};

#endif // JSBRIDGE_H
