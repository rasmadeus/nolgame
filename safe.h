#ifndef SAFE_H
#define SAFE_H

#include "pch.h"

class Cell;
class Lock;

class Safe : public QWidget
{
    Q_OBJECT
public:
    explicit Safe(int width, int height, QWidget* parent);
    void setShuffle(bool value) { _shuffle = value; }

signals:
    void moveProcess(bool started);
    void clicked(Cell* cell);
    void unlocked();

private:
    void fillLocks(QHBoxLayout* layout);
    void updateLockState();
    void tryUnlock();
    void fillUnlockSequence(Cell* cell);
    void setClickable(bool value);
    void startUnlock(Cell* cell);
    void redo(Cell* cell);
    void processUnlock(Cell* cell);

private:
    int _width;
    int _height;
    QVector<Lock*> _locks;
    QVector<Cell*> _unlockSequence;
    bool _shuffle = true;
};

#endif // SAFE_H
