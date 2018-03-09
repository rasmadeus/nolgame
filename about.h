#ifndef ABOUT_H
#define ABOUT_H

#include "pch.h"

class About : public QDialog
{
    Q_OBJECT

public:
    explicit About(QWidget* parent);

private:
    void addCredit(const QString& res, const QString& author, QFormLayout* layout);
};

#endif // ABOUT_H
