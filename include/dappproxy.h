// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DAPPPROXY_H
#define DAPPPROXY_H

#include "dnetworkmanagertypes.h"
#include <DExpected>

DNETWORKMANAGER_BEGIN_NAMESPACE

class DAppProxyPrivate;

using DCORE_NAMESPACE::DExpected;

class DAppProxy : public QObject
{
    Q_OBJECT
public:
    explicit DAppProxy(QObject *parent = nullptr);
    ~DAppProxy() override = default;

    Q_PROPERTY(QByteArray IP READ IP)
    Q_PROPERTY(QByteArray password READ password)
    Q_PROPERTY(ProxyType type READ type)
    Q_PROPERTY(QByteArray user READ user)
    Q_PROPERTY(quint32 port READ port)

    QByteArray IP() const;
    QByteArray password() const;
    ProxyType type() const;
    QByteArray user() const;
    quint32 port() const;

public slots:
    DExpected<void>
    set(const ProxyType type, const QByteArray &ip, const quint32 port, const QByteArray &user, const QByteArray &password) const;

private:
    QScopedPointer<DAppProxyPrivate> d_ptr;
    Q_DECLARE_PRIVATE(DAppProxy)
};

DNETWORKMANAGER_END_NAMESPACE

#endif
