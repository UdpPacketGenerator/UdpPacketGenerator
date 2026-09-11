#pragma once

#include <QByteArray>
#include <QString>
#include <QVector>

struct UdpTarget
{
    QString address;
    quint16 sourcePort = 0;
    quint16 destPort = 0;
};

class UdpTargetsLoader
{
public:
    // Извлекает массив "udp" из JSON-шаблона.
    // Пустой или отсутствующий "udp" — не ошибка: targets остаётся пустым.
    // Непустая строка результата — ошибка парсинга/валидации.
    static QString load(const QByteArray &jsonData, QVector<UdpTarget> *targets);
};
