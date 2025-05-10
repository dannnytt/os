#ifndef PACKETDATA_H
#define PACKETDATA_H

#include <QString>

struct PacketData {
    QString time;
    QString source;
    QString dest;
    QString protocol;
    QString length;
};

#endif // PACKETDATA_H
