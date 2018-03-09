#include "settings.h"
#include "settings_spinbox.h"

Settings::Settings(QWidget *parent)
    : QDialog{ parent }
    , _shuffle{ new QCheckBox{ tr("Shuffle row/column on click"), this } }
    , _width{ new SettingsSpinbox{ this } }
    , _height{ new SettingsSpinbox{ this } }
{
    setWindowTitle(tr("Settings"));
    setModal(true);

    _shuffle->setChecked(true);

    auto acceptButton = new QPushButton{ tr("Accept"), this };
    auto rejectButton = new QPushButton{ tr("Reject"), this };

    connect(acceptButton, &QPushButton::clicked, this, &Settings::accept);
    connect(rejectButton, &QPushButton::clicked, this, &Settings::reject);

    auto sizeLayout = new QFormLayout{};
    sizeLayout->addRow(tr("Area width: "), _width);
    sizeLayout->addRow(tr("Area height: "), _height);

    auto buttonsLayout = new QHBoxLayout{};
    buttonsLayout->addWidget(acceptButton, 1);
    buttonsLayout->addWidget(rejectButton, 1);

    auto layout = new QVBoxLayout{ this };
    layout->addWidget(_shuffle);
    layout->addLayout(sizeLayout);
    layout->addLayout(buttonsLayout);
}

int Settings::getWidth() const
{
    return _width->value();
}

int Settings::getHeight() const
{
    return _height->value();
}

bool Settings::needShuffle() const
{
    return _shuffle->isChecked();
}
