#ifndef HISTORY_H
#define HISTORY_H

#include "pch.h"

class Cell;

class History : public QObject
{
    Q_OBJECT

public:
    explicit History(QObject* parent);

    void append(Cell* cell);
    void clear();
    void next();
    void prev();

signals:
    void canPrev(bool can);
    void canNext(bool can);

private:
    void jump();
    void notify();

private:
    QVector<Cell*> _cells;
    int _pos = -1;
};

#endif // HISTORY_H
