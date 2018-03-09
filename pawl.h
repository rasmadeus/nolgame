#ifndef PAWL_H
#define PAWL_H

#include "cell.h"

class Pawl : public Cell
{
    Q_OBJECT

public:
    Pawl(const QString& opened, const QString& closed, QWidget* parent);

protected:
    void paintContent(QPainter& painter, QPaintEvent* ev) override;

private:
    QPixmap _opened;
    QPixmap _closed;
};

#endif // PAWL_H
