#include "packetsniffer.h"
#include <netinet/ether.h>
#include <netinet/ip.h>
#include <netinet/ip6.h>
#include <netinet/udp.h>
#include <netinet/tcp.h>
#include <netinet/ip_icmp.h>

PacketSniffer::PacketSniffer(QObject *parent)
    : QObject(parent), capturing(false), pcapHandle(nullptr)
{
    connect(this, &PacketSniffer::showWarningMessage, this, &PacketSniffer::onShowWarningMessage);
}

PacketSniffer::~PacketSniffer() {}

void PacketSniffer::setInterface(const QString &iface) {
    ifaceName = iface;
}

void PacketSniffer::setFilter(const QString &filter) {
    this->filter = filter;
}

void PacketSniffer::onShowWarningMessage(const QString &message) {
    QMessageBox::warning(nullptr, "Warning", message);
}

void PacketSniffer::startCapture() {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcapHandle = pcap_open_live(ifaceName.toUtf8().constData(), BUFSIZ, 1, 1000, errbuf);

    if (!pcapHandle) {
        emit showWarningMessage(QString("Failed to open device: %1").arg(errbuf));
        return;
    }

    if (!filter.isEmpty() && !applyFilter()) {
        pcap_close(pcapHandle);
        return;
    }

    capturing = true;
    pcap_loop(pcapHandle, 0, processPacket, reinterpret_cast<u_char *>(this));

    pcap_close(pcapHandle);
    pcapHandle = nullptr;
}

bool PacketSniffer::applyFilter() {
    struct bpf_program bpfProgram;
    if (pcap_compile(pcapHandle, &bpfProgram, filter.toUtf8().constData(), 0, PCAP_NETMASK_UNKNOWN) == -1) {
        emit showWarningMessage(QString("Failed to compile filter: %1").arg(pcap_geterr(pcapHandle)));
        return false;
    }

    if (pcap_setfilter(pcapHandle, &bpfProgram) == -1) {
        emit showWarningMessage(QString("Failed to compile filter: %1").arg(pcap_geterr(pcapHandle)));
        pcap_freecode(&bpfProgram);
        return false;
    }

    pcap_freecode(&bpfProgram);
    return true;
}

void PacketSniffer::stopCapture() {
    capturing = false;
    if (pcapHandle) {
        pcap_breakloop(pcapHandle);
    }
}

void PacketSniffer::processPacket(u_char *userData, const struct pcap_pkthdr *header, const u_char *packet) {
    auto *sniffer = reinterpret_cast<PacketSniffer *>(userData);
    PacketData packetData;
    packetData.time = QDateTime::currentDateTime().toString("hh:mm:ss");

    const auto *ethHeader = reinterpret_cast<const struct ether_header *>(packet);
    uint16_t ethertype = ntohs(ethHeader->ether_type);

    if (ethertype == ETHERTYPE_IP) {
        sniffer->processIPv4(packet, packetData);
    } else if (ethertype == ETHERTYPE_IPV6) {
        sniffer->processIPv6(packet, packetData);
    } else if (ethertype == ETHERTYPE_ARP) {
        sniffer->processARP(packet, packetData);
    }

    packetData.length = QString::number(header->len);
    emit sniffer->packetCaptured(packetData);
}

void PacketSniffer::processIPv4(const u_char *packet, PacketData &packetData) {
    const auto *ipHeader = reinterpret_cast<const struct ip *>(packet + sizeof(struct ether_header));
    char srcIp[INET_ADDRSTRLEN], dstIp[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &ipHeader->ip_src, srcIp, INET_ADDRSTRLEN);
    inet_ntop(AF_INET, &ipHeader->ip_dst, dstIp, INET_ADDRSTRLEN);

    packetData.source = QString(srcIp);
    packetData.dest = QString(dstIp);
    packetData.protocol = protocolToString(ipHeader->ip_p);
}

void PacketSniffer::processIPv6(const u_char *packet, PacketData &packetData) {
    const auto *ipv6Header = reinterpret_cast<const struct ip6_hdr *>(packet + sizeof(struct ether_header));
    char srcIp[INET6_ADDRSTRLEN], dstIp[INET6_ADDRSTRLEN];
    inet_ntop(AF_INET6, &ipv6Header->ip6_src, srcIp, INET6_ADDRSTRLEN);
    inet_ntop(AF_INET6, &ipv6Header->ip6_dst, dstIp, INET6_ADDRSTRLEN);

    packetData.source = QString(srcIp);
    packetData.dest = QString(dstIp);
    packetData.protocol = protocolToString(ipv6Header->ip6_nxt);
}

void PacketSniffer::processARP(const u_char *packet, PacketData &packetData) {
    const auto *arpHeader = reinterpret_cast<const struct ether_arp *>(packet + sizeof(struct ether_header));
    packetData.source = macToString(arpHeader->arp_sha);
    packetData.dest = macToString(arpHeader->arp_tha);
    packetData.protocol = "ARP";
}

QString PacketSniffer::macToString(const unsigned char *mac) {
    return QString("%1:%2:%3:%4:%5:%6").arg(mac[0], 2, 16, QChar('0'))
        .arg(mac[1], 2, 16, QChar('0'))
        .arg(mac[2], 2, 16, QChar('0'))
        .arg(mac[3], 2, 16, QChar('0'))
        .arg(mac[4], 2, 16, QChar('0'))
        .arg(mac[5], 2, 16, QChar('0'));
}

QString PacketSniffer::protocolToString(int protocol) {
    switch (protocol) {
    case IPPROTO_TCP: return "TCP";
    case IPPROTO_UDP: return "UDP";
    case IPPROTO_ICMP: return "ICMP";
    case IPPROTO_ICMPV6: return "ICMPv6";
    default: return "Other";
    }
}
