// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dactivevpnconnection.h"
#include "dactivevpnconnection_p.h"

DNETWORKMANAGER_BEGIN_NAMESPACE

DActiveVpnConnectionPrivate::DActiveVpnConnectionPrivate(const quint64 id, DActiveVpnConnection *parent)
    : DActiveConnectionPrivate(id, parent)
    , m_vpn(new DActiveVpnConnectionInterface("/org/freedesktop/NetworkManager/ActiveConnection/" + QByteArray::number(id), this))
{
}

DActiveVpnConnection::DActiveVpnConnection(const quint64 id, QObject *parent)
    : DActiveConnection(id, parent)
{
    Q_D(const DActiveVpnConnection);

    connect(d->m_vpn, &DActiveVpnConnectionInterface::VpnStateChanged, this, [this](const quint32 state, const quint32 reason) {
        emit this->VpnStateChanged(static_cast<NMVpnConnectionState>(state), static_cast<NMActiveConnectionStateReason>(reason));
    });

    connect(d->m_vpn, &DActiveVpnConnectionInterface::bannerChanged, this, &DActiveVpnConnection::bannerChanged);
}

NMVpnConnectionState DActiveVpnConnection::vpnState() const
{
    Q_D(const DActiveVpnConnection);
    return static_cast<NMVpnConnectionState>(d->m_vpn->vpnState());
}

QString DActiveVpnConnection::banner() const
{
    Q_D(const DActiveVpnConnection);
    return d->m_vpn->banner();
}

DNETWORKMANAGER_END_NAMESPACE
