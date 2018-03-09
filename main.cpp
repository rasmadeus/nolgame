#include "main_view.h"

void setStyles(QApplication& app)
{
    QFile styles{ ":/res/styles.qss" };
    styles.open(QFile::ReadOnly);
    app.setStyleSheet(styles.readAll());
}

int main(int argc, char *argv[])
{
    QApplication app{ argc, argv };

    QApplication::setOrganizationName("Rra");
    QApplication::setOrganizationDomain("rra.com");
    QApplication::setApplicationName("nolgame");

    setStyles(app);

    MainView mainView;
    mainView.show();

    return app.exec();
}
