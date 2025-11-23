#include "SomeTypeToolRole.h"
#include <QDebug>


SomeTypeToolRole::SomeTypeToolRole()
{

}

void SomeTypeToolRole::OnActionTriggered(bool isChecked)
{
    qDebug() << "###############SomeTypeToolRole##########"<<__FUNCTION__<<isChecked;
}
