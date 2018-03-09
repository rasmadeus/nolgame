#include "keylock.h"

namespace
{
    const int maxAngle = 90;
}

Keylock::Keylock(const QPoint& pos, const QString& res, QWidget* parent)
    : Cell{ parent }
    , _pos{ pos }
    , _icon{ res }
{
    setToggled(std::rand() % 2 == 0);
}

void Keylock::paintContent(QPainter& painter, QPaintEvent* ev)
{
    const auto center = ev->rect().center();
    painter.translate(center);
    painter.rotate(isToggled() ? ::maxAngle - angle() : angle());
    painter.translate(-center);
    painter.drawPixmap(ev->rect(), _icon);
}

int Keylock::angle() const
{
    if (animationPoint() == 0)
        return ::maxAngle;

    const double animationState = animationPoint() / static_cast<double>(animationDuration());
    return ::maxAngle * animationState;
}
