// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DWIREDDEVICEINTERFACE_H
#define DWIREDDEVICEINTERFACE_H

#include "ddeviceInterface.h"

DNETWORKMANAGER_BEGIN_NAMESPACE

using DTK_CORE_NAMESPACE::DDBusInterface;

class DWiredDeviceInterface : public DDeviceInterface
{
    Q_OBJECT
public:
    explicit DWiredDeviceInterface(const QByteArray &path, QObject *parent = nullptr);
    ~DWiredDeviceInterface() override = default;

    Q_PROPERTY(QString HwAddress READ HwAddress NOTIFY HwAddressChanged)
    Q_PROPERTY(QString permHwAddress READ permHwAddress NOTIFY permHwAddressChanged)
    Q_PROPERTY(quint32 speed READ speed NOTIFY speedChanged)
    Q_PROPERTY(QList<QString> S390Subchannels READ S390Subchannels NOTIFY S390SubchannelsChanged)
    Q_PROPERTY(bool carrier READ carrier NOTIFY carrierChanged)

    QString HwAddress() const;
    QString permHwAddress() const;
    quint32 speed() const;
    QList<QString> S390Subchannels() const;
    bool carrier() const;

signals:
    void HwAddressChanged(const QString &address);
    void permHwAddressChanged(const QString &address);
    void speedChanged(const quint32 speed);
    void S390SubchannelsChanged(const QList<QString> &channels);
    void carrierChanged(const bool carrier);

private:
    DDBusInterface *m_wiredInter{nullptr};
};

DNETWORKMANAGER_END_NAMESPACE

#endif
