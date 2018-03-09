#include "cell.h"
#include "game.h"
#include "safe.h"

Game::Game(QWidget *parent)
    : QWidget{ parent }
{
    auto layout = new QHBoxLayout{ this };
    layout->setMargin(0);
}

void Game::start(int width, int height, bool shuffle)
{
    if (_safe)
    {
        layout()->removeWidget(_safe);
        _safe->deleteLater();
    }

    _width = width;
    _height = height;
    _isRunning = true;

    _safe = new Safe{ width, height, this };
    _safe->setShuffle(shuffle);
    connect(_safe, &Safe::unlocked, this, &Game::endGame);
    connect(_safe, &Safe::clicked, this, &Game::clicked);
    connect(_safe, &Safe::moveProcess, this, &Game::moveProcess);

    layout()->addWidget(_safe);
    setFixedSize(_safe->size());

    _start = std::chrono::system_clock::now();
}

void Game::endGame()
{
    _isRunning = false;
    const auto elapsed = std::chrono::system_clock::now() - _start;
    emit safeUnlocked(std::chrono::duration_cast<std::chrono::seconds>(elapsed).count(), _width, _height);    
}
