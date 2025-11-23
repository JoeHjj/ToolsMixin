#include "BasicToolRole.h"
#include <QDebug>


BasicToolRole::BasicToolRole()
{

}

void BasicToolRole::OnActionTriggered(bool isChecked)
{
    qDebug() << "###############BasicToolRole##########"<<__FUNCTION__<<isChecked;
}
