#include "OtherToolRole.h"
#include <QDebug>


OtherToolRole::OtherToolRole()
{

}

void OtherToolRole::OnActionTriggered(bool isChecked)
{
    qDebug() << "###############OtherToolRole##########"<<__FUNCTION__<<isChecked;
}
