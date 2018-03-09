#ifndef CELL_H
#define CELL_H

#include "pch.h"

class Cell : public QWidget
{
    Q_OBJECT    

public:
    static int side() { return 64; }
    static int animationDuration() { return 200; }

    explicit Cell(QWidget* parent);

    void setClickable(bool value) { _clickable = value; }
    int animationPoint() const { return _animationPoint; }
    bool isToggled() const { return _toggled; }

    void setToggled(bool value);
    void toggle();

signals:
    void redo(Cell* self);
    void clicked(Cell* self);
    void animationFinished(Cell* self);

protected:
    void paintEvent(QPaintEvent* ev) override;
    void mousePressEvent(QMouseEvent* ev) override;
    void mouseReleaseEvent(QMouseEvent* ev) override;
    void timerEvent(QTimerEvent* ev) override;

protected:
    virtual void paintContent(QPainter& painter, QPaintEvent* ev) = 0;

private:
    bool _mousePressed = false;
    bool _clickable = true;
    bool _toggled = false;
    int _animationTimerId = -1;
    int _animationPoint = 0;
};

#endif // CELL_H
