#ifndef KEYLOCK_H
#define KEYLOCK_H

#include "cell.h"

class Keylock : public Cell
{
public:
    Keylock(const QPoint& pos, const QString& res, QWidget* parent);
    const QPoint& pos() const { return _pos; }

protected:
    void paintContent(QPainter& painter, QPaintEvent* ev) override;

private:
    int angle() const;

private:
    QPoint _pos;
    QPixmap _icon;
};

#endif // LOCK_KEY_H
