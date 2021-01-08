/****************************************************************************
**
** Copyright (C) 2021 Evgeny Shtanov <shtanov_evgenii@mail.ru>
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the QtSerialBus module.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "model4view.h"

Model4view::Model4view(QObject *parent) : QAbstractTableModel (parent)
{

}

Model4view::~Model4view()
{

}

bool Model4view::insertRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent)
    Q_UNUSED(count)

    beginInsertRows(parent, row, row);

    endInsertRows();

    return true;
}

bool Model4view::removeRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent)
    Q_UNUSED(count)

    beginRemoveRows(parent, row, row);

    endRemoveRows();

    return true;
}

QVariant Model4view::headerData(int section, Qt::Orientation orientation, int role) const
{
    if ((role == Qt::DisplayRole) && (orientation == Qt::Horizontal))
    {
        switch (section) {
        case 0:
            return "Timestamp";
        case 1:
            return "Flags";
        case 2:
            return "CAN-ID   DLC  Data";
        }
    }

    return QVariant();
}

QVariant Model4view::data(const QModelIndex &index, int role) const
{
    if (! (role == Qt::DisplayRole || role == Qt::EditRole))
        return QVariant();

    int row = index.row();
    int column = index.column();

    switch (column) {
    case 0:
        return m_framesQ[row][0];
    case 1:
        return m_framesQ[row][1];
    case 2:
        return m_framesQ[row][2];
    }

    return QVariant();
}

int Model4view::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return m_framesQ.size();
}

int Model4view::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return 3;
}

void Model4view::insertFrame(const QStringList & list)
{
    insertRow(m_framesQ.size());

    m_framesQ.enqueue(list);

    if (m_qLimit < rowCount()) {
        removeFirstRow();
    }
}

void Model4view::removeFirstRow()
{
    if (rowCount()) {
        removeRow(0);

        m_framesQ.dequeue();
    }
}

void Model4view::deletAll()
{
    while (rowCount()) {
        removeFirstRow();
    }
}
