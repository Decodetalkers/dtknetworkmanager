// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dipv4config.h"
#include "dipv4config_p.h"

DNETWORKMANAGER_BEGIN_NAMESPACE

DIPv4ConfigPrivate::DIPv4ConfigPrivate(const quint64 id, DIPv4Config *parent)
    : q_ptr(parent)
    , m_ipv4(new DIPv4ConfigInterface("/org/freedesktop/NetworkManager/IP4Config/" + QByteArray::number(id), this))
{
}

DIPv4Config::DIPv4Config(const quint64 id, QObject *parent)
    : QObject(parent)
    , d_ptr(new DIPv4ConfigPrivate(id, this))
{
    Q_D(const DIPv4Config);
    connect(d->m_ipv4, &DIPv4ConfigInterface::addressDataChanged, this, &DIPv4Config::addressDataChanged);

    connect(d->m_ipv4, &DIPv4ConfigInterface::nameserverDataChanged, this, &DIPv4Config::nameserverDataChanged);

    connect(d->m_ipv4, &DIPv4ConfigInterface::gatewayChanged, this, [this](const QString &gateway) {
        emit this->gatewayChanged(QHostAddress(gateway));
    });
}

QList<Config> DIPv4Config::addressData() const
{
    Q_D(const DIPv4Config);
    return d->m_ipv4->addressData();
}

QList<Config> DIPv4Config::nameserverData() const
{
    Q_D(const DIPv4Config);
    return d->m_ipv4->nameserverData();
}

QHostAddress DIPv4Config::gateway() const
{
    Q_D(const DIPv4Config);
    return QHostAddress(d->m_ipv4->gateway());
}

DNETWORKMANAGER_END_NAMESPACE
