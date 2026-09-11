#include "udp_targets_loader.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>

QString UdpTargetsLoader::load(const QByteArray &jsonData, QVector<UdpTarget> *targets)
{
    if (!targets)
        return "UdpTargetsLoader: targets pointer is null";

    targets->clear();

    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(jsonData, &parseError);
    if (parseError.error != QJsonParseError::NoError)
        return QString("JSON parse error: %1").arg(parseError.errorString());

    QJsonObject root = doc.object();
    QJsonArray udpArray = root["udp"].toArray();

    targets->reserve(udpArray.size());
    for (const QJsonValue &val : udpArray) {
        QJsonObject obj = val.toObject();

        UdpTarget target;
        target.address = obj["address"].toString();
        target.sourcePort = static_cast<quint16>(obj["source_port"].toInt());
        target.destPort = static_cast<quint16>(obj["dest_port"].toInt());

        targets->push_back(target);
    }

    return {}; // OK
}
