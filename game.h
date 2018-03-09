#ifndef GAME_H
#define GAME_H

#include "pch.h"

class Cell;
class Safe;

class Game : public QWidget
{
    Q_OBJECT

public:
    explicit Game(QWidget* parent);
    void start(int width, int height, bool shuffle);
    bool isRunning() const { return _isRunning; }
    int getWidth() const { return _width; }
    int getHeight() const { return _height; }

signals:
    void moveProcess(bool started);
    void safeUnlocked(int seconds, int width, int height);
    void clicked(Cell* cell);

private:
    void endGame();

private:
    Safe* _safe = nullptr;
    std::chrono::time_point<std::chrono::system_clock> _start;
    int _width = 0;
    int _height = 0;
    bool _isRunning = false;
};

#endif // GAME_H
