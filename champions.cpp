#include "champions.h"

namespace
{
    QString group(int width, int height)
    {
        return QString{"%1x%2"}.arg(width).arg(height);
    }
}

Champions::Champions(QWidget* parent)
    : QDialog{ parent }
    , _lastResult{ new QLabel{ tr("<h2>You have no win for this game session</h2>"), this } }
    , _records{ new QTextEdit{ this } }
{    
    setModal(true);
    setWindowTitle("The game's champions");

    auto acceptButton = new QPushButton{ tr("Ok"), this };
    connect(acceptButton, &QPushButton::clicked, this, &Champions::accept);

    auto layout = new QVBoxLayout{ this };
    layout->addWidget(_lastResult);
    layout->addWidget(_records);
    layout->addWidget(acceptButton);

    _lastResult->setWordWrap(true);
    _lastResult->setAlignment(Qt::AlignCenter);
    _records->setReadOnly(true);
}

void Champions::showWith(int width, int height)
{
    restoreGroup(width, height);
    exec();
}

void Champions::trySave(int seconds, int width, int height)
{
    _lastResult->setText(tr("<h2>Your time for field %1x%2 is %3 seconds!</h2>").arg(width).arg(height).arg(seconds));

    const auto group = ::group(width, height);

    auto records = readRecords(group);
    records.emplace_back(seconds);

    std::sort(records.begin(), records.end());
    static const std::size_t maxItems = 10;
    records.resize(std::min(maxItems, records.size()));

    saveRecords(group, records);
}

void Champions::restoreGroup(int width, int height)
{
    _records->clear();

    const auto group = ::group(width, height);
    _records->append(QString{ "<b>Field: %1</b>" }.arg(group));

    const auto seconds = readRecords(group);
    if (seconds.empty())
    {
        _records->append(tr("No records"));
        return;
    }

    for(const auto& value: seconds)
        _records->append(tr("%1 seconds").arg(value));
}

std::vector<int> Champions::readRecords(const QString& group) const
{
    std::vector<int> res;

    QSettings settings;
    settings.beginGroup(group);

    const int size = settings.beginReadArray(QStringLiteral("records"));
    for (int i = 0; i < size; ++i)
    {
        settings.setArrayIndex(i);
        res.emplace_back(settings.value("seconds").toInt());
    }
    settings.endArray();
    settings.endGroup();

    std::sort(res.begin(), res.end());
    return res;
}

void Champions::saveRecords(const QString& group, const std::vector<int>& seconds)
{
    QSettings settings;
    settings.beginGroup(group);
    settings.beginWriteArray("records");
    for (int i = 0; i < static_cast<int>(seconds.size()); ++i)
    {
        settings.setArrayIndex(i);
        settings.setValue("seconds", seconds[i]);
    }
    settings.endArray();
    settings.endGroup();
}
