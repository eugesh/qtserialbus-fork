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

#include "common.h"
#include "receivedframesview.h"

#include <QAction>
#include <QApplication>
#include <QClipboard>
#include <QKeyEvent>
#include <QMenu>

ReceivedFramesView::ReceivedFramesView(QWidget *parent)
 : QTableView(parent)
{
    this->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(this, &QWidget::customContextMenuRequested,
            this, &ReceivedFramesView::showContextMenu);
}

void ReceivedFramesView::setModel(QAbstractItemModel *model) {
    QTableView::setModel(model);

    setColumnWidth(ReceivedFramesModelColumns::Number, 80);
    setColumnWidth(ReceivedFramesModelColumns::Timestamp, 130);
    setColumnWidth(ReceivedFramesModelColumns::Flags, 25);
    setColumnWidth(ReceivedFramesModelColumns::CanID, 50);
    setColumnWidth(ReceivedFramesModelColumns::DLC, 25);
    setColumnWidth(ReceivedFramesModelColumns::Data, 200);
}

void ReceivedFramesView::keyPressEvent(QKeyEvent *event) {
    if (event->matches(QKeySequence::Copy)) {
        copyRow();
    } else if (event->matches(QKeySequence::SelectAll)) {
        selectAll();
    } else {
        QTableView::keyPressEvent(event);
    }
}

void ReceivedFramesView::showContextMenu(const QPoint &pos) {
    QMenu contextMenu(tr("Context menu"), this);

    QAction action1("Copy", this);
    QAction action2("Select all", this);

    connect(&action1, &QAction::triggered, this, &ReceivedFramesView::copyRow);
    connect(&action2, &QAction::triggered, this, &QAbstractItemView::selectAll);

    if (selectedIndexes().count())
        contextMenu.addAction(&action1);
    contextMenu.addAction(&action2);

    contextMenu.exec(mapToGlobal(pos));
}

void ReceivedFramesView::copyRow() {
    QClipboard *clipboard = QApplication::clipboard();

    const QModelIndexList ilist = selectedIndexes();

    QString strRow;

    for (const QModelIndex &index : ilist) {
        if (index.column() == ReceivedFramesModelColumns::DLC)
            strRow += "[" + index.data().toString() + "] ";
        else
            strRow += index.data().toString() + " ";

        if (index.column() == model()->columnCount() - 1)
            strRow += '\n';
    }

    clipboard->setText(strRow);
}
