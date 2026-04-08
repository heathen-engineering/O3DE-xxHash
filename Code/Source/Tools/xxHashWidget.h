
#pragma once

#if !defined(Q_MOC_RUN)
#include <AzToolsFramework/API/ToolsApplicationAPI.h>

#include <QWidget>
#endif

namespace xxHash
{
    class xxHashWidget
        : public QWidget
    {
        Q_OBJECT
    public:
        explicit xxHashWidget(QWidget* parent = nullptr);
    };
} 
