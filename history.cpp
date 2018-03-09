#include "cell.h"
#include "history.h"

namespace
{
    const int maxSize = 10;
}

History::History(QObject *parent)
    : QObject{ parent }
{
}

void History::append(Cell* cell)
{
    if (_pos != -1 && _pos < _cells.size() - 1)
        _cells.remove(_pos + 1, _cells.size() - _pos - 1);

    _cells << cell;

    if (_cells.size() > ::maxSize)
        _cells.takeFirst();

    _pos = _cells.size() - 1;

    notify();
}

void History::clear()
{
    _cells.clear();
    _pos = -1;
    notify();
}

void History::next()
{
    if (_pos < _cells.size() - 1)
    {
        _pos++;
        jump();
        notify();
    }
}

void History::prev()
{
    if (_pos >= 0)
    {
        jump();
        _pos--;
        notify();
    }
}

void History::jump()
{
    auto cell = _cells[_pos];
    cell->redo(cell);
}

void History::notify()
{
    emit canPrev(_cells.size() > 0 && _pos != -1);
    emit canNext(_cells.size() > 0 && _pos < _cells.size() - 1);
}
