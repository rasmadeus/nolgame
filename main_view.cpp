#include "cell.h"
#include "main_view.h"
#include "champions.h"
#include "game.h"
#include "settings.h"
#include "about.h"
#include "history.h"

MainView::MainView(QWidget* parent)
    : QMainWindow{ parent }
    , _game{ new Game{ this } }
    , _champions{ new Champions{ this } }
    , _settings{ new Settings{ this } }
    , _about{ new About{ this } }
    , _history{ new History{ this } }
{
    setObjectName(QStringLiteral("mainView"));
    setWindowTitle(tr("Arrange all carrots horizontally"));
    setupCentralWidget();
    setupGameMenu();
    setupHistoryMenu();
    startGame();
}

void MainView::setupCentralWidget()
{
    setCentralWidget(_game);
    connect(_game, &Game::safeUnlocked, this, &MainView::endGame);
    connect(_game, &Game::clicked, _history, &History::append);
}

void MainView::setupGameMenu()
{
    auto menu = menuBar()->addMenu(tr("Game"));

    auto newGame = new QAction{ tr("New game"), this };
    connect(newGame, &QAction::triggered, this, &MainView::startGame);
    menu->addAction(newGame);

    auto showSettings = new QAction{ tr("Show settings"), this };
    connect(showSettings, &QAction::triggered, this, &MainView::showSettings);
    menu->addAction(showSettings);

    auto showChampions = new QAction{ tr("Show champions"), this };
    connect(showChampions, &QAction::triggered, this, &MainView::showChampions);
    menu->addAction(showChampions);

    auto showAbout = new QAction{ tr("About"), this };
    connect(showAbout, &QAction::triggered, _about, &About::exec);
    menu->addAction(showAbout);

    menu->addSeparator();
    auto exit = new QAction{ tr("Exit"), this };
    connect(exit, &QAction::triggered, this, &MainView::close);
    menu->addAction(exit);
}

void MainView::setupHistoryMenu()
{
    auto menu = menuBar()->addMenu(tr("History"));

    auto prev = new QAction{ tr("Previous move"), this };
    connect(prev, &QAction::triggered, _history, &History::prev);
    connect(_history, &History::canPrev, prev, &QAction::setEnabled);
    menu->addAction(prev);

    auto next = new QAction{ tr("Next move"), this };
    connect(next, &QAction::triggered, _history, &History::next);
    connect(_history, &History::canNext, next, &QAction::setEnabled);
    menu->addAction(next);

    connect(_game, &Game::moveProcess, menu, &QMenu::setDisabled);
}

void MainView::paintEvent(QPaintEvent* ev)
{
    std::ignore = ev;

    QStyleOption opt;
    opt.init(this);

    QPainter painter{ this };
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void MainView::startGame()
{
    _history->clear();
    _game->start(_settings->getWidth(), _settings->getHeight(), _settings->needShuffle());
    setFixedSize(_game->size().width(), _game->size().height() + menuBar()->height());
    setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, size(), qApp->desktop()->availableGeometry()));
}

void MainView::showSettings()
{
    if (_settings->exec() == QDialog::Accepted)
        startGame();
}

void MainView::showChampions()
{
    _champions->showWith(_game->getWidth(), _game->getHeight());
    if (!_game->isRunning())
        startGame();
}

void MainView::endGame(int seconds, int width, int height)
{
    _history->clear();
    _champions->trySave(seconds, width, height);
    showChampions();
}
