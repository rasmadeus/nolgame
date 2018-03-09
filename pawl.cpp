#include "pawl.h"

Pawl::Pawl(const QString& opened, const QString& closed, QWidget* parent)
    : Cell{ parent }
    , _opened{ opened }
    , _closed{ closed }
{
    setClickable(false);
}

void Pawl::paintContent(QPainter& painter, QPaintEvent* ev)
{
    painter.drawPixmap(ev->rect(), isToggled() ? _opened : _closed);
}
