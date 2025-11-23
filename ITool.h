#pragma once

#include <QAction>

class ITool: public QAction
{
    Q_OBJECT

public:
    virtual bool isCheckable() = 0;
    virtual bool isChecked() = 0;
    virtual void OnActionTriggered(bool val) = 0;
};
