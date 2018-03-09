#ifndef LOCK_H
#define LOCK_H

#include "pch.h"

class Cell;
class Keylock;
class Pawl;

class Lock : public QWidget
{
    Q_OBJECT

public:
    explicit Lock(int x, int height, QWidget* parent);

    Keylock* cell(int y) const { return _cells[y]; }
    void setClickable(bool value);
    void tryUnlock();
    bool isLocked() const;

signals:
    void redo(Cell* cell);
    void clicked(Cell* cell);
    void animationFinished(Cell* cell);

private:
    QVector<Keylock*> _cells;
    Pawl* _lock;
};

#endif // LOCK_H
