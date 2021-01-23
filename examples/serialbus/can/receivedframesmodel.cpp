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
#include <iterator>
#include "receivedframesmodel.h"

static const unsigned int ColumnCount = 3;

ReceivedFramesModel::ReceivedFramesModel(QObject *parent) : QAbstractTableModel(parent)
{

}

bool ReceivedFramesModel::insertRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent)
    Q_UNUSED(count)

    if (m_queueLimit <= (rowCount() + count))
        removeFirstNRows(rowCount() + count - m_queueLimit + 1);

    beginInsertRows(parent, row, row + count - 1);

    for (int i = 0; i < m_framesToInsert.size(); ++i) {
        m_framesQueue.enqueue(m_framesToInsert[i]);
    }

    endInsertRows();

    return true;
}

bool ReceivedFramesModel::removeRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent)
    Q_UNUSED(count)

    beginRemoveRows(parent, row, row + count - 1);

    if (count <= rowCount()) {
        QList<QStringList>::iterator i_start = m_framesQueue.begin() + row;
        QList<QStringList>::iterator i_end = i_start + count;
        m_framesQueue.erase(i_start, i_end);
    }

    endRemoveRows();

    return true;
}

QVariant ReceivedFramesModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if ((role == Qt::DisplayRole) && (orientation == Qt::Horizontal)) {
        switch (section) {
        case Timestamp:
            return tr("Timestamp");
        case Flags:
            return tr("Flags");
        case CanID:
            return tr("CAN-ID   DLC  Data");
        }
    }

    return {};
}

QVariant ReceivedFramesModel::data(const QModelIndex &index, int role) const
{
    if (!(role == Qt::DisplayRole) || m_framesQueue.empty())
        return {};

    const int row = index.row();
    const int column = index.column();

    if (column < columnCount() && row < rowCount())
        return m_framesQueue.at(row).at(column);

    return {};
}

int ReceivedFramesModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return m_framesQueue.size();
}

int ReceivedFramesModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return ColumnCount;
}

void ReceivedFramesModel::appendFrame(const QStringList &slist)
{
    m_framesToInsert = {slist};

    insertRow(m_framesQueue.size());
}

void ReceivedFramesModel::appendFrames(const QVector<QStringList> &slvector)
{
    m_framesToInsert = slvector;

    insertRows(m_framesQueue.size(), slvector.size());
}

void ReceivedFramesModel::removeFirstRow()
{
    if (rowCount()) {
        beginRemoveRows(QModelIndex(), 0, 1);

        m_framesQueue.dequeue();

        endRemoveRows();
    }
}

void ReceivedFramesModel::removeFirstNRows(int N) {
    if (rowCount() >= N) {
        beginRemoveRows(QModelIndex(), 0, N - 1);

        QList<QStringList>::iterator i_start = m_framesQueue.begin();
        QList<QStringList>::iterator i_end = i_start + N;
        m_framesQueue.erase(i_start, i_end);

        endRemoveRows();
    }
}

void ReceivedFramesModel::clear()
{
    removeFirstNRows(m_framesQueue.size());
}
