#include "settings_spinbox.h"

SettingsSpinbox::SettingsSpinbox(QWidget* parent)
    : QSpinBox{ parent }
{
    setRange(minSide(), maxSide());
    setSingleStep(1);
}
