#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "packetsniffer.h"
#include "packetdata.h"

#include <QMainWindow>

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QStringList>
#include <QString>
#include <QThread>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QStringList getAllNetIfaces();

private slots:
    void startSniffing();
    void stopSniffing();
    void clearTable();
    void addPacketToTable(const PacketData &data);


private:
    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QTableWidget *snifferTable;

    QGridLayout *buttonsLayout;
    QPushButton *startButton;
    QPushButton *stopButton;
    QPushButton *clearButton;

    QHBoxLayout *hLayout;
    QComboBox *netIfaces;
    QComboBox *protocolFilter;

    PacketSniffer *sniffer;
    QThread *snifferThread;

};
#endif // MAINWINDOW_H
