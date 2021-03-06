/*
 * Copyright (C) 2008-2010 The QXmpp developers
 *
 * Authors:
 *  Manjeet Dahiya
 *  Jeremy Lainé
 *
 * Source:
 *  http://code.google.com/p/qxmpp
 *
 * This file is a part of QXmpp library.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 */


#include "QXmppRosterManager.h"
#include "QXmppUtils.h"
#include "QXmppRosterIq.h"
#include "QXmppPresence.h"
#include "QXmppStream.h"

QXmppRosterManager::QXmppRosterManager(QXmppStream* stream, QObject *parent)
    : QObject(parent),
    m_stream(stream),
    m_isRosterReceived(false)
{
    bool check = QObject::connect(m_stream, SIGNAL(xmppConnected()),
        this, SLOT(connected()));
    Q_ASSERT(check);

    check = QObject::connect(m_stream, SIGNAL(disconnected()),
        this, SLOT(disconnected()));
    Q_ASSERT(check);

    check = QObject::connect(m_stream, SIGNAL(presenceReceived(const QXmppPresence&)),
        this, SLOT(presenceReceived(const QXmppPresence&)));
    Q_ASSERT(check);

    check = QObject::connect(m_stream, SIGNAL(rosterIqReceived(const QXmppRosterIq&)), 
        this, SLOT(rosterIqReceived(const QXmppRosterIq&)));
    Q_ASSERT(check);
}

QXmppRosterManager::~QXmppRosterManager()
{

}

/// Upon XMPP connection, request the roster.
///
void QXmppRosterManager::connected()
{
    QXmppRosterIq roster;
    roster.setType(QXmppIq::Get);
    roster.setFrom(m_stream->configuration().jid());
    m_rosterReqId = roster.id();
    m_stream->sendPacket(roster);
}

void QXmppRosterManager::disconnected()
{
    m_entries = QMap<QString, QXmppRosterIq::Item>();
    m_presences = QMap<QString, QMap<QString, QXmppPresence> >();
    m_isRosterReceived = false;
}

void QXmppRosterManager::presenceReceived(const QXmppPresence& presence)
{
    QString jid = presence.from();
    QString bareJid = jidToBareJid(jid);
    QString resource = jidToResource(jid);

    if (bareJid.isEmpty())
        return;

    switch(presence.type())
    {
    case QXmppPresence::Available:
        m_presences[bareJid][resource] = presence;
        emit presenceChanged(bareJid, resource);
        break;
    case QXmppPresence::Unavailable:
        m_presences[bareJid].remove(resource);
        emit presenceChanged(bareJid, resource);
        break;
    case QXmppPresence::Subscribe:
        if (m_stream->configuration().autoAcceptSubscriptions())
        {
            QXmppPresence presence;
            presence.setTo(jid);
            presence.setType(QXmppPresence::Subscribed);
            m_stream->sendPacket(presence);
        }
        break;
    default:
        break;
    }
}

void QXmppRosterManager::rosterIqReceived(const QXmppRosterIq& rosterIq)
{
    bool isInitial = (m_rosterReqId == rosterIq.id());

    switch(rosterIq.type())
    {
    case QXmppIq::Set:
        {
            // send result iq
            QXmppIq returnIq(QXmppIq::Result);
            returnIq.setId(rosterIq.id());
            m_stream->sendPacket(returnIq);

            // store updated entries and notify changes
            const QList<QXmppRosterIq::Item> items = rosterIq.items();
            for (int i = 0; i < items.count(); i++)
            {
                QString bareJid = items.at(i).bareJid();
                m_entries[bareJid] = items.at(i);
                emit rosterChanged(bareJid);
            }

            // when contact subscribes user...user sends 'subscribed' presence 
            // then after recieving following iq user requests contact for subscription
            
            // check the "from" is newly added in the roster...and remove this ask thing...and do this for all items
            QXmppRosterIq::Item item = items.at(0);
            if (!item.bareJid().isEmpty() &&
                item.subscriptionType() == QXmppRosterIq::Item::From &&
                item.subscriptionStatus().isEmpty())
            {
                QXmppPresence presence;
                presence.setTo(item.bareJid());
                presence.setType(QXmppPresence::Subscribe);
                m_stream->sendPacket(presence);
            }
        }
        break;
    case QXmppIq::Result:
        {
            QList<QXmppRosterIq::Item> items = rosterIq.items();
            for(int i = 0; i < items.count(); ++i)
            {
                QString bareJid = items.at(i).bareJid();
                m_entries[bareJid] = items.at(i);
                if (!isInitial)
                    emit rosterChanged(bareJid);
            }
            if (isInitial)
            {
                m_isRosterReceived = true;
                emit rosterReceived();
            }
            break;
        }
    default:
        break;
    }
}

/// Function to get all the bareJids present in the roster.
///
/// \return QStringList list of all the bareJids
///

QStringList QXmppRosterManager::getRosterBareJids() const
{
    return m_entries.keys();
}

/// Returns the roster entry of the given bareJid. If the bareJid is not in the
/// database and empty QXmppRosterIq::Item will be returned.
///
/// \param bareJid as a QString
///

QXmppRosterIq::Item QXmppRosterManager::getRosterEntry(
        const QString& bareJid) const
{
    // will return blank entry if bareJid does'nt exist
    if(m_entries.contains(bareJid))
        return m_entries.value(bareJid);
    else
        return QXmppRosterIq::Item();
}

/// [OBSOLETE] Returns all the roster entries in the database.
///
/// \return Map of bareJid and its respective QXmppRosterIq::Item
///
/// \note This function is obsolete, use getRosterBareJids() and
/// getRosterEntry() to get all the roster entries.
///

QMap<QString, QXmppRosterIq::Item>
        QXmppRosterManager::getRosterEntries() const
{
    return m_entries;
}

/// Get all the associated resources with the given bareJid.
///
/// \param bareJid as a QString
/// \return list of associated resources as a QStringList
///

QStringList QXmppRosterManager::getResources(const QString& bareJid) const
{
    if(m_presences.contains(bareJid))
        return m_presences[bareJid].keys();
    else
        return QStringList();
}

/// Get all the presences of all the resources of the given bareJid. A bareJid
/// can have multiple resources and each resource will have a presence
/// associated with it.
///
/// \param bareJid as a QString
/// \return Map of resource and its respective presence QMap<QString, QXmppPresence>
///

QMap<QString, QXmppPresence> QXmppRosterManager::getAllPresencesForBareJid(
        const QString& bareJid) const
{
    if(m_presences.contains(bareJid))
        return m_presences[bareJid];
    else
        return QMap<QString, QXmppPresence>();
}

/// Get the presence of the given resource of the given bareJid.
///
/// \param bareJid as a QString
/// \param resource as a QString
/// \return QXmppPresence
///

QXmppPresence QXmppRosterManager::getPresence(const QString& bareJid,
                                       const QString& resource) const
{
    if(m_presences.contains(bareJid) && m_presences[bareJid].contains(resource))
        return m_presences[bareJid][resource];
    else
        return QXmppPresence();
}

/// [OBSOLETE] Returns all the presence entries in the database.
///
/// \return Map of bareJid and map of resource and its presence that is
/// QMap<QString, QMap<QString, QXmppPresence> >
///
/// \note This function is obsolete, use getRosterBareJids(), getResources()
/// and getPresence() or getAllPresencesForBareJid()
/// to get all the presence entries.

QMap<QString, QMap<QString, QXmppPresence> > QXmppRosterManager::getAllPresences() const
{
    return m_presences;
}

/// Function to check whether the roster has been received or not.
///
/// \return true if roster received else false

bool QXmppRosterManager::isRosterReceived()
{
    return m_isRosterReceived;
}

