#include "about.h"

About::About(QWidget *parent)
    : QDialog{ parent }
{
    setModal(true);
    setWindowTitle(tr("Credits"));

    auto acceptButton = new QPushButton{ tr("Ok"), this };
    connect(acceptButton, &QPushButton::clicked, this, &About::accept);

    auto creditsLayout = new QFormLayout{};
    creditsLayout->addRow(tr("<b>Author:</b>"), new QLabel{ QStringLiteral("rasmadeus@gmail.com"), this });
    creditsLayout->addRow(tr("<b>Credits:</b>"), new QLabel{ tr("Icons made by %1").arg(QStringLiteral("www.flaticon.com")), this });

    auto layout = new QVBoxLayout{ this };
    layout->addLayout(creditsLayout);
    layout->addWidget(acceptButton);
}
