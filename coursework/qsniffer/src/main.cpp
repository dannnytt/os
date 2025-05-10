#include "mainwindow.h"
#include <QMetaType>
#include "packetdata.h"
#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    qRegisterMetaType<PacketData>("PacketData");
    app.setWindowIcon(QIcon(":/icons/spyware.png"));
    MainWindow w;
    w.show();
    return app.exec();
}
