#ifndef SETTINGS_SPINBOX_H
#define SETTINGS_SPINBOX_H

#include "pch.h"

class SettingsSpinbox : public QSpinBox
{
    Q_OBJECT

public:
    static int minSide() { return 4; }
    static int maxSide() { return 10; }

    explicit SettingsSpinbox(QWidget* parent);
};

#endif // SETTINGS_SPINBOX_H
