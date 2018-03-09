#include "about.h"

About::About(QWidget *parent)
    : QDialog{ parent }
{
    setModal(true);
    setWindowTitle(tr("Credits"));

    auto acceptButton = new QPushButton{ tr("Ok"), this };
    connect(acceptButton, &QPushButton::clicked, this, &About::accept);

    auto creditsLayout = new QFormLayout{};
    addCredit(QStringLiteral(":/res/keylock.png"), QStringLiteral("<a href=\"http://www.freepik.com\" title=\"Freepik\">Freepik</a>"), creditsLayout);
    addCredit(QStringLiteral(":/res/pawl_opened.png"), QStringLiteral("<a href=\"http://www.freepik.com\" title=\"Freepik\">Freepik</a>"), creditsLayout);

    auto layout = new QVBoxLayout{ this };
    layout->addLayout(creditsLayout);
    layout->addWidget(acceptButton);
}

void About::addCredit(const QString& res, const QString& author, QFormLayout *layout)
{
    auto icon = new QLabel{ this };
    icon->setPixmap(QPixmap{ res }.scaled(16, 16));

    static const auto url = QString{ "<a href=\"https://www.flaticon.com/\" title=\"Flaticon\">www.flaticon.com</a>" };
    static const auto license = QString{ "<a href=\"http://creativecommons.org/licenses/by/3.0/\" title=\"Creative Commons BY 3.0\" target=\"_blank\">CC 3.0 BY</a>" };
    static const auto pattern = tr("Icon made by %1 from %2 is licensed by %3");

    auto caption = new QLabel{ this };
    caption->setText(pattern.arg(author).arg(url).arg(license));
    caption->setWordWrap(true);

    layout->addRow(icon, caption);
}
