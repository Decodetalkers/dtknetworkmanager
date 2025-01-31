// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DNMUTILS_H
#define DNMUTILS_H

#include "dnetworkmanager_global.h"
#include "dnetworkmanagertypes.h"
#include <QDBusObjectPath>
#include <QHostAddress>

DNETWORKMANAGER_BEGIN_NAMESPACE

inline quint64 getIdFromObjectPath(const QDBusObjectPath &path)
{
    const auto &strId = path.path().split("/").last();
    bool ok;
    auto intId = strId.toLongLong(&ok);
    return ok ? intId : 0;
}

inline const char *enumToProxyType(const ProxyType type)
{
    switch (type) {
        case ProxyType::ProxyTypeHTTP:
            return "http";
        case ProxyType::ProxyTypeSocks4:
            return "socks4";
        case ProxyType::ProxyTypeSocks5:
            return "socks5";
    }
    Q_UNREACHABLE();
}

inline ProxyType proxyTypeToEnum(const QString &type)
{
    if (type == "http")
        return ProxyType::ProxyTypeHTTP;
    else if (type == "socks4")
        return ProxyType::ProxyTypeSocks4;
    else if (type == "socks5")
        return ProxyType::ProxyTypeSocks5;
    Q_UNREACHABLE();
}

inline SystemProxyMethod proxyMethodToEnum(const QString &method)
{
    if (method == "auto")
        return SystemProxyMethod::SystemProxyMethodAuto;
    else if (method == "manual")
        return SystemProxyMethod::SystemProxyMethodManual;
    else if (method == "none")
        return SystemProxyMethod::SystemProxyMethodNone;
    Q_UNREACHABLE();
}

inline const char *enumToProxyMethod(const SystemProxyMethod method)
{
    switch (method) {
        case SystemProxyMethod::SystemProxyMethodAuto:
            return "auto";
        case SystemProxyMethod::SystemProxyMethodManual:
            return "manual";
        case SystemProxyMethod::SystemProxyMethodNone:
            return "none";
    }
    Q_UNREACHABLE();
}

inline QString macAddressToString(const QByteArray &ba)
{
    QStringList mac;
    for (auto i : ba)
        mac << QString("%1").arg((quint8)i, 2, 16, QLatin1Char('0')).toUpper();
    return mac.join(":");
}

inline QByteArray stringToMacAddress(const QString &s)
{
    const QStringList macStringList = s.split(':');
    QByteArray ba;
    if (!s.isEmpty()) {
        ba.resize(6);
        int i = 0;

        for (const QString &macPart : macStringList) {
            ba[i++] = static_cast<char>(macPart.toUInt(nullptr, 16));
        }
    }
    return ba;
}

inline QHostAddress ipv6AddressToHostAddress(const QByteArray &address)
{
    Q_IPV6ADDR tmp;
    for (int i = 0; i < 16; ++i)
        tmp[i] = address[i];
    QHostAddress hostaddress(tmp);
    Q_ASSERT(hostaddress.protocol() == QAbstractSocket::IPv6Protocol);

    return hostaddress;
}

inline QByteArray HostAddressToipv6Address(const QHostAddress &address)
{
    Q_IPV6ADDR tmp = address.toIPv6Address();
    QByteArray assembledAddress;
    assembledAddress.reserve(16);
    for (int i = 0; i < 16; ++i)
        assembledAddress.push_back(static_cast<char>(tmp[i]));

    return assembledAddress;
}

DNETWORKMANAGER_END_NAMESPACE

#endif
