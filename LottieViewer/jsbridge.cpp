#include "jsbridge.h"
#include <QDebug>

JSBridge::JSBridge(QObject *parent) : QObject(parent)
{

}

void JSBridge::animationLoaded(int frames, int frameRate) {
    emit onAnimationLoaded(frames, frameRate);
}

void JSBridge::enteredFrame(int frame) {
    emit onEnterFrame(frame);
}
