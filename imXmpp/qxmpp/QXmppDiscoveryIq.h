/*
 * Copyright (C) 2008-2010 The QXmpp developers
 *
 * Author:
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

#ifndef QXMPPDISCOVERY_H
#define QXMPPDISCOVERY_H

#include "QXmppElement.h"
#include "QXmppDataForm.h"
#include "QXmppIq.h"

class QDomElement;

class QXmppDiscoveryIq : public QXmppIq
{
public:
    class Identity
    {
    public:
        QString category() const;
        void setCategory(const QString &category);

        QString language() const;
        void setLanguage(const QString &language);

        QString name() const;
        void setName(const QString &name);

        QString type() const;
        void setType(const QString &type);

    private:
        QString m_category;
        QString m_language;
        QString m_name;
        QString m_type;
    };

    class Item
    {
    public:
        QString jid() const;
        void setJid(const QString &jid);

        QString name() const;
        void setName(const QString &name);

        QString node() const;
        void setNode(const QString &node);

    private:
        QString m_jid;
        QString m_name;
        QString m_node;
    };

    enum QueryType {
        InfoQuery,
        ItemsQuery,
    };

    QStringList features() const;
    void setFeatures(const QStringList &features);

    QList<QXmppDiscoveryIq::Identity> identities() const;
    void setIdentities(const QList<QXmppDiscoveryIq::Identity> &identities);

    QList<QXmppDiscoveryIq::Item> items() const;
    void setItems(const QList<QXmppDiscoveryIq::Item> &items);

    QXmppDataForm form() const;
    void setForm(const QXmppDataForm &form);

    QString queryNode() const;
    void setQueryNode(const QString &node);

    enum QueryType queryType() const;
    void setQueryType(enum QueryType type);

    QByteArray verificationString() const;

    static bool isDiscoveryIq(const QDomElement &element);

protected:
    /// \cond
    void parseElementFromChild(const QDomElement &element);
    void toXmlElementFromChild(QXmlStreamWriter *writer) const;
    /// \endcond

private:
    QStringList m_features;
    QList<QXmppDiscoveryIq::Identity> m_identities;
    QList<QXmppDiscoveryIq::Item> m_items;
    QXmppDataForm m_form;
    QString m_queryNode;
    enum QueryType m_queryType;
};

#endif
