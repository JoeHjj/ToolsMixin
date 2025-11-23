#pragma once

class MultiCheckableToolRole
{
public:
    MultiCheckableToolRole();
    void OnActionTriggered(bool isChecked);
    bool KeepChecked();
};
