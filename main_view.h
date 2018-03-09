#ifndef MAIN_VIEW_H
#define MAIN_VIEW_H

#include "pch.h"

class Champions;
class Game;
class About;
class Settings;
class History;

class MainView : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainView(QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent* ev) override;

private:
    void setupCentralWidget();
    void setupGameMenu();
    void setupHistoryMenu();
    void startGame();
    void showSettings();
    void showChampions();
    void endGame(int seconds, int width, int height);

private:
    Game* _game;
    Champions* _champions;
    Settings* _settings;
    About* _about;
    History* _history;
};

#endif // MAIN_VIEW_H
