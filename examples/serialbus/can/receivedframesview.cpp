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

#include <QClipboard>
#include <QKeyEvent>
#include <QApplication>
#include "common.h"
#include "receivedframesview.h"

ReceivedFramesView::ReceivedFramesView(QWidget *parent)
 : QTableView(parent)
{
    setColumnWidth(0, 80);
    setColumnWidth(1, 150);
    setColumnWidth(2, 25);
    setColumnWidth(3, 50);
    setColumnWidth(4, 25);
    setColumnWidth(5, 175);
}

void ReceivedFramesView::keyPressEvent(QKeyEvent *event) {
    if (event->matches(QKeySequence::Copy)) {
        copyRow();
    } else if (event->matches(QKeySequence::SelectAll)) {
        selectAll();
    }
}

void ReceivedFramesView::copyRow() {
    QClipboard *clipboard = QApplication::clipboard();

    const QModelIndexList ilist = selectedIndexes();

    QString strRow = "";

    foreach (const QModelIndex ind, ilist) {
        if (ind.column() == ReceivedFramesModelColumns::DLC)
            strRow += "[" + ind.data().toString() + "] ";
        else
            strRow += ind.data().toString() + " ";

        if (ind.column() == model()->columnCount() - 1)
            strRow += '\n';
    }

    clipboard->setText(strRow);

    QString tmp_str = clipboard->text();
}