/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
****************************************************************************/

#ifndef KDEPASTE_H
#define KDEPASTE_H

#include "protocol.h"

namespace CodePaster {

class StickyNotesPasteProtocol : public NetworkProtocol
{
    Q_OBJECT
public:
    StickyNotesPasteProtocol();

    QString name() const { return m_name; }

    virtual unsigned capabilities() const;

    virtual void fetch(const QString &id);
    virtual void paste(const QString &text,
                       ContentType ct = Text,
                       int expiryDays = 1,
                       const QString &username = QString(),
                       const QString &comment = QString(),
                       const QString &description = QString());
    virtual void list();



    QString hostUrl() const { return m_hostUrl; }
    void setHostUrl(const QString &hostUrl);

    void setName(const QString &name) { m_name = name; }

public slots:
    void fetchFinished();
    void pasteFinished();
    void listFinished();

protected:
    virtual bool checkConfiguration(QString *errorMessage = 0);

private:
    QString m_hostUrl;
    QString m_name;

    QNetworkReply *m_fetchReply;
    QNetworkReply *m_pasteReply;
    QNetworkReply *m_listReply;

    QString m_fetchId;
    int m_postId;
    bool m_hostChecked;
};

class KdePasteProtocol : public StickyNotesPasteProtocol
{
public:
    KdePasteProtocol()
    {
        setHostUrl(QLatin1String("http://pastebin.kde.org/"));
        setName(QLatin1String("Paste.KDE.Org"));
    }
};

} // namespace CodePaster

#endif // KDEPASTE_H
