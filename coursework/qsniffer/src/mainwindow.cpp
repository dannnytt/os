#include "mainwindow.h"
#include <QLabel>
#include <QHeaderView>
#include <QListView>
#include <QMessageBox>
#include <pcap.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      sniffer(nullptr),
      snifferThread(nullptr)
{
    /*Параметры окна*/
    this->resize(1000, 800);
    this->setMinimumSize(800, 600);

    /*Настройка центрального виджета*/
    centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);
    mainLayout = new QVBoxLayout(centralWidget);

    /*Создание и настройка combo box для выбора интерфейса*/
    QLabel *ifaceLabel = new QLabel("Interface:", this);
    hLayout = new QHBoxLayout;
    hLayout->addWidget(ifaceLabel);

    netIfaces = new QComboBox(this);
    netIfaces->addItems(getAllNetIfaces());
    hLayout->addWidget(netIfaces);

    /*Создание и настройка combo box для выбора фильтра*/
    QLabel *filterLabel = new QLabel("Filter:", this);
    hLayout->addWidget(filterLabel);

    protocolFilter = new QComboBox(this);
    protocolFilter->addItems({
        "None",
        "tcp",
        "udp",
        "icmp",
        "arp"
    });

    hLayout->addWidget(protocolFilter);
    mainLayout->addLayout(hLayout);
    hLayout->addStretch();


    /*Настройка таблицы для отображения пакетов*/
    snifferTable = new QTableWidget(this);
    snifferTable->setColumnCount(5);
    snifferTable->setHorizontalHeaderLabels({
        "Time",
        "Source IP",
        "Destination IP",
        "Protocol",
        "Length"
    });
    snifferTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    snifferTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mainLayout->addWidget(snifferTable);

    /*Настройка кнопок*/
    buttonsLayout = new QGridLayout;
    startButton = new QPushButton("Start", this);
    stopButton = new QPushButton("Stop", this);
    clearButton = new QPushButton("Clear", this);
    buttonsLayout->addWidget(stopButton, 0, 0);
    buttonsLayout->addWidget(startButton, 0, 1);
    buttonsLayout->addWidget(clearButton, 1, 0, 1, 2);
    mainLayout->addLayout(buttonsLayout);

    connect(startButton, &QPushButton::clicked, this, &MainWindow::startSniffing);
    connect(stopButton, &QPushButton::clicked, this, &MainWindow::stopSniffing);
    connect(clearButton, &QPushButton::clicked, this, &MainWindow::clearTable);

}

MainWindow::~MainWindow() {}

QStringList MainWindow::getAllNetIfaces() {
    QStringList ifaceList;
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_if_t *interfaces;

    if (pcap_findalldevs(&interfaces, errbuf) == -1) {
        QMessageBox::warning(this, "Warning", QString("Error getting devices: %1").arg(errbuf));
        return ifaceList;
    }

    for (pcap_if_t *dev = interfaces; dev; dev = dev->next) {
        ifaceList.append(dev->name);
    }

    pcap_freealldevs(interfaces);
    return ifaceList;
}

void MainWindow::startSniffing() {

    startButton->setEnabled(false);
    stopButton->setEnabled(true);
    clearButton->setEnabled(false);

    sniffer = new PacketSniffer;
    sniffer->setInterface(netIfaces->currentText());

    sniffer->setFilter(protocolFilter->currentText() == "None" ? "" : protocolFilter->currentText());

    snifferThread = new QThread(this);
    snifferThread->start();

    sniffer->moveToThread(snifferThread);

    connect(snifferThread, &QThread::started, sniffer, &PacketSniffer::startCapture);
    connect(sniffer, &PacketSniffer::packetCaptured, this, &MainWindow::addPacketToTable);
    connect(sniffer, &PacketSniffer::destroyed, snifferThread, &QThread::quit);
    connect(snifferThread, &QThread::finished, snifferThread, &QThread::deleteLater);
}

void MainWindow::stopSniffing() {
    stopButton->setEnabled(false);
    startButton->setEnabled(true);
    clearButton->setEnabled(true);

    if (sniffer) {
        sniffer->stopCapture();
    }

    if (snifferThread) {
        snifferThread->quit();
        snifferThread->wait();

        delete snifferThread;
        snifferThread = nullptr;
    }

    delete sniffer;
    sniffer = nullptr;
}

void MainWindow::clearTable() {
    snifferTable->setRowCount(0);
    clearButton->setEnabled(false);
}

void MainWindow::addPacketToTable(const PacketData &packet) {
    int row = snifferTable->rowCount();
    snifferTable->insertRow(row);
    snifferTable->setItem(row, 0, new QTableWidgetItem(packet.time));
    snifferTable->setItem(row, 1, new QTableWidgetItem(packet.source));
    snifferTable->setItem(row, 2, new QTableWidgetItem(packet.dest));
    snifferTable->setItem(row, 3, new QTableWidgetItem(packet.protocol));
    snifferTable->setItem(row, 4, new QTableWidgetItem(packet.length));

    clearButton->setEnabled(true);
}
