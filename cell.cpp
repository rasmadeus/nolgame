#include "cell.h"

Cell::Cell(QWidget* parent)
    : QWidget{ parent }
{
    setFixedSize(side(), side());

    setAttribute(Qt::WA_NoSystemBackground);
    setAttribute(Qt::WA_TranslucentBackground);
}

void Cell::setToggled(bool value)
{
    _toggled = value;
    update();
}

void Cell::toggle()
{
    _animationPoint = 0;
    _toggled = !_toggled;
    _animationTimerId = startTimer(std::chrono::milliseconds(1));
}

void Cell::paintEvent(QPaintEvent* ev)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    paintContent(painter, ev);
    painter.end();
}

void Cell::mousePressEvent(QMouseEvent* ev)
{
    QWidget::mousePressEvent(ev);

    if (ev->button() == Qt::LeftButton)
        _mousePressed = true;
}

void Cell::mouseReleaseEvent(QMouseEvent* ev)
{
    QWidget::mouseReleaseEvent(ev);

    if (ev->button() == Qt::LeftButton)
    {
        _mousePressed = false;
        if (_clickable)
            emit clicked(this);
    }
}

void Cell::timerEvent(QTimerEvent* ev)
{
    if (ev->timerId() != _animationTimerId)
        return;

    ++_animationPoint;

    if (_animationPoint == animationDuration())
    {
        killTimer(_animationTimerId);
        _animationTimerId = -1;
        emit animationFinished(this);
    }

    update();
}
