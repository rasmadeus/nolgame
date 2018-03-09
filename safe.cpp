#include "cell.h"
#include "keylock.h"
#include "lock.h"
#include "safe.h"

Safe::Safe(int width, int height, QWidget* parent)
    : QWidget{ parent }
    , _width{ width }
    , _height{ height }
{
    auto layout = new QHBoxLayout{ this };
    layout->setMargin(0);
    layout->setSpacing(0);

    fillLocks(layout);

    setFixedSize(width * Cell::side(), (height + 1) * Cell::side());
    tryUnlock();
}

void Safe::fillLocks(QHBoxLayout* layout)
{
    for(int i = 0; i < _width; ++i)
    {
        auto lock = new Lock{ i, _height, this };
        _locks.append(lock);
        layout->addWidget(lock);

        connect(lock, &Lock::clicked, this, &Safe::startUnlock);
        connect(lock, &Lock::redo, this, &Safe::redo);
        connect(lock, &Lock::animationFinished, this, &Safe::processUnlock);
    }
}

void Safe::setClickable(bool value)
{
    for(auto& lock : _locks)
        lock->setClickable(value);
}

void Safe::updateLockState()
{
    for(auto& lock : _locks)
        lock->tryUnlock();
}

void Safe::tryUnlock()
{
    const bool isLocked = std::any_of(_locks.begin(), _locks.end(), [](const auto& lock){ return lock->isLocked(); });
    if (!isLocked)
        emit unlocked();
}

void Safe::startUnlock(Cell* cell)
{
    redo(cell);
    emit clicked(cell);
}

void Safe::redo(Cell *cell)
{
    emit moveProcess(true);
    setClickable(false);
    fillUnlockSequence(cell);
    cell->toggle();
    updateLockState();
}

void Safe::processUnlock(Cell* cell)
{
    _unlockSequence.removeOne(cell);

    if (_unlockSequence.isEmpty())
    {
        emit moveProcess(false);
        setClickable(true);
        updateLockState();
        tryUnlock();
    }
    else
    {
        _unlockSequence.front()->toggle();
        updateLockState();
    }
}

void Safe::fillUnlockSequence(Cell* cell)
{
    auto keylock = static_cast<Keylock*>(cell);
    _unlockSequence << keylock;

    if (!_shuffle)
        return;

    const auto pos = keylock->pos();
    int step = 1;

    while(true)
    {
        const int xLeft = pos.x() - step;
        const int yTop = pos.y() - step;
        const int xRight = pos.x() + step;
        const int yBottom = pos.y() + step;

        const bool xLeftValid = xLeft >= 0;
        const bool yTopValid = yTop >= 0;
        const bool xRightValid = xRight < _width;
        const bool yBottomValid = yBottom < _height;

        if (xLeftValid)
            _unlockSequence << _locks[xLeft]->cell(pos.y());

        if (yTopValid)
            _unlockSequence << _locks[pos.x()]->cell(yTop);

        if (xRightValid)
            _unlockSequence << _locks[xRight]->cell(pos.y());

        if (yBottomValid)
            _unlockSequence << _locks[pos.x()]->cell(yBottom);

        if (!xLeftValid && !yTopValid && !xRightValid && !yBottomValid)
            break;

        ++step;
    }
}
