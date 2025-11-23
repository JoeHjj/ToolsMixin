#include "MultiInsertToolRole.h"
#include <QGuiApplication>
#include <QDebug>

static bool m_isMultiInsert = false;

MultiCheckableToolRole::MultiCheckableToolRole()
{

}
void MultiCheckableToolRole::OnActionTriggered(bool isChecked)
{
    if (isChecked)
    {
        m_isMultiInsert = QGuiApplication::keyboardModifiers().testFlag(Qt::ShiftModifier);
    }
    else
    {
        m_isMultiInsert = false;
    }
    qDebug() << "###############MultiCheckableTool##########"<<__FUNCTION__<<m_isMultiInsert;
}

bool MultiCheckableToolRole::KeepChecked()
{
    return m_isMultiInsert;
}
