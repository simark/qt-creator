/****************************************************************************
**
** Copyright (C) 2018 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
****************************************************************************/

#pragma once

#include <utils/smallstringvector.h>

namespace ClangBackEnd {

class SymbolIndexerTask;

class SymbolIndexerTaskQueueInterface
{
public:
    SymbolIndexerTaskQueueInterface() = default;
    SymbolIndexerTaskQueueInterface(const SymbolIndexerTaskQueueInterface &) = delete;
    SymbolIndexerTaskQueueInterface &operator=(const SymbolIndexerTaskQueueInterface &) = delete;

    virtual void addOrUpdateTasks(std::vector<SymbolIndexerTask> &&tasks) = 0
    /* [[expects: std::is_sorted(tasks)]] */;
    virtual void removeTasks(const std::vector<int> &projectPartIds) = 0
    /* [[expects: std::is_sorted(projectPartIds)]] */;
    virtual void processTasks() = 0;

protected:
    ~SymbolIndexerTaskQueueInterface() = default;
};
} // namespace ClangBackEnd
