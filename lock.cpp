#include "cell.h"
#include "lock.h"
#include "keylock.h"
#include "pawl.h"

Lock::Lock(int x, int height, QWidget* parent)
    : QWidget{ parent }
    , _lock{ new Pawl{ QStringLiteral(":/res/pawl_opened.png"), QStringLiteral(":/res/pawl_closed.png"), this } }
{
    auto layout = new QVBoxLayout{ this };
    layout->setMargin(0);
    layout->setSpacing(0);

    layout->addWidget(_lock);

    for(int i = 0; i < height; ++i)
    {
        auto cell = new Keylock{ { x, i }, QStringLiteral(":/res/keylock.png"), this };
        _cells.append(cell);        
        layout->addWidget(cell);

        connect(cell, &Keylock::clicked, this, &Lock::clicked);
        connect(cell, &Keylock::redo, this, &Lock::redo);
        connect(cell, &Keylock::animationFinished, this, &Lock::animationFinished);
    }

    setFixedSize(Cell::side(), (height + 1) * Cell::side());
    tryUnlock();
}

void Lock::setClickable(bool value)
{
    for(auto& cell: _cells)
        cell->setClickable(value);
}

void Lock::tryUnlock()
{
    _lock->setToggled(!isLocked());
}

bool Lock::isLocked() const
{
    return std::any_of(_cells.begin(), _cells.end(), [](const auto& cell) { return !cell->isToggled(); });
}
