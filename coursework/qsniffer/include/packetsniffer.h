#ifndef PACKETSNIFFER_H
#define PACKETSNIFFER_H

#include "packetdata.h"
#include <pcap.h>
#include <QObject>
#include <QString>
#include <QDateTime>
#include <QMessageBox>

class PacketSniffer : public QObject {
    Q_OBJECT

public:
    explicit PacketSniffer(QObject *parent = nullptr);
    ~PacketSniffer();
    void setInterface(const QString &iface);
    void setFilter(const QString &filter);

public slots:
    void startCapture();
    void stopCapture();
    void onShowWarningMessage(const QString &message);
signals:
    void packetCaptured(const PacketData &packet);
    void showWarningMessage(const QString &message);

private:
    bool applyFilter();
    static void processPacket(u_char *userData, const struct pcap_pkthdr *header, const u_char *packet);
    void processIPv4(const u_char *packet, PacketData &packetData);
    void processIPv6(const u_char *packet, PacketData &packetData);
    void processARP(const u_char *packet, PacketData &packetData);
    QString macToString(const unsigned char *mac);
    QString protocolToString(int protocol);

private:
    bool capturing;
    QString ifaceName;
    QString filter;
    pcap_t *pcapHandle;

};

#endif // PACKETCAPTURE_H
