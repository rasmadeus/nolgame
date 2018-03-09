#ifndef SETTINGS_H
#define SETTINGS_H

#include "pch.h"

class SettingsSpinbox;

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget* parent);

    int getWidth() const;
    int getHeight() const;
    bool needShuffle() const;

private:
    QCheckBox* _shuffle;
    SettingsSpinbox* _width;
    SettingsSpinbox* _height;
};

#endif // SETTINGS_H
