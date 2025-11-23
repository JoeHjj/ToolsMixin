#pragma once

#include "ITool.h"
#include <QDebug>
#include <QPushButton>

template <class... Args>
class Tool : public ITool, public Args...
{
public:

    template<class T>
    void connectByType(T) {
        connect(this, &Tool::toggled, this,[&](bool isChecked){
            T::OnActionTriggered(isChecked);
        });
    }

    template<class T, class... Types>
    void  connectByType(T t, Types... types)
    {
        connectByType<T>(t);
        connectByType<Types...>(types...);
    }

    template<class... Types>
    void  connectByType(Types...)
    {
    }

    void  connectByType()
    {
        connect(this, &Tool::toggled, this,&Tool::OnActionTriggered);
    }

    Tool()
    {
        connect(this, &Tool::toggled, this,&Tool::OnActionTriggered);
        connectByType<Args...>(Args()...);
    }

    void OnActionTriggered(bool val) override
    {
        qDebug() << "##############Tool###########"<<__FUNCTION__<< val;
    }

    template<typename T,
             std::enable_if_t
             <
                 std::is_base_of_v
                 <
                     ITool, T
                 >, bool
              > = false
            >
    T* As()
    {
        return dynamic_cast<T*>(this);
    }
    template<typename V,
             std::enable_if_t
             <
                 std::is_base_of_v
                 <
                     QPushButton, V
                     >, bool
                 > = false
             >

    V* As()
    {
        return dynamic_cast<V*>(this);
    }


    template<typename T, typename... Ts>
    using enable_if_all = std::enable_if_t<std::conjunction_v<std::is_same<T, Ts>...>>;

    template<typename T, typename... Ts>
    using enable_if_any = std::enable_if_t<std::disjunction_v<std::is_same<T, Ts>...>>;

    template<typename... Ts, typename = enable_if_any<QDebug*, Ts...>>
    void f(Ts... values)
    {
    }

    template<
            typename T, typename =
                 std::enable_if_t
                 <
                     std::is_base_of_v
                     <ITool, T>
                 >
             >

    T* As2()
    {
        return dynamic_cast<T*>(this);
    }

    bool isCheckable() override{return false;};
    bool isChecked()override{return false;};

private:
    std::tuple<Args...> arguments;
};
