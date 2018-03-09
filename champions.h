#ifndef CHAMPIONS_H
#define CHAMPIONS_H

#include "pch.h"

class Champions : public QDialog
{
    Q_OBJECT

public:
    explicit Champions(QWidget* parent);
    void showWith(int width, int height);
    void trySave(int seconds, int width, int height);

private:
    void restoreGroup(int width, int height);
    std::vector<int> readRecords(const QString& group) const;
    void saveRecords(const QString& group, const std::vector<int>& seconds);

private:
    QLabel* _lastResult;
    QTextEdit* _records;
};

#endif // CHAMPIONS_H
