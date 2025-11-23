#pragma once
#include <type_traits>
#include <new>
#include <iostream>
#include <string>

#include <array>
#include <tuple>
#include <vector>
#include <map>
#include <typeinfo>
#include <typeindex>

template<class T>
struct isSameType_t{};

template<class T>
constexpr isSameType_t<std::remove_cv_t<T>> TypeOf{};

template<class T, class U>
constexpr std::is_same<T, U>  operator==( isSameType_t<T>, isSameType_t<U> ) { return {}; }

template<class T, class U>
constexpr std::integral_constant<bool, !(TypeOf<T> == TypeOf<U>)> operator!=( isSameType_t<T>, isSameType_t<U> ) { return {}; }

template <typename T, typename U>
struct is_same : std::false_type {};

template <typename T>
struct is_same<T, T> : std::true_type {};

template <typename T, typename U>
struct is_same_cv : is_same<std::remove_cv_t<T>, std::remove_cv_t<U>> {};

template <typename Derived, typename Base>
Derived* cast(Base* p, std::enable_if_t<std::is_base_of<Base, Derived>::value, int> = 0)
{
    return static_cast<Derived*>(p);
}

template <typename Derived, typename Base>
Derived* cast(Base*, std::enable_if_t<!std::is_base_of<Base, Derived>::value, int> = 0)
{
    return nullptr;
}

template <class A, class B>
inline constexpr
bool is_same_v
= is_same<std::remove_cv_t<A>, std::remove_cv_t<B>>::value;

// Generic identity function
template<typename T, T Value>
struct Identity {
    static constexpr T value = Value;
};

template<auto Value>
struct AnyIdentity {
    static constexpr auto value = Value;
};

template<auto Value>
inline constexpr auto Identity_v = AnyIdentity<Value>::value;


template<typename T>
struct TypeIdentity {
    using type = T;
};

template<typename T>
using Identity_t = typename TypeIdentity<T>::type;

//#################################Integral_constant########################################################

template<typename T, T v>
struct interal_constant {
    static constexpr T value = v;
    using value_type = T;
    using type = interal_constant<T,v>;

    constexpr operator value_type() const noexcept
    {
        return value;
    }

    constexpr value_type operator()() const noexcept
    {
        return value;
    }
};

//#################################bool_constant########################################################
template<bool B>
using bool_constant = interal_constant<bool,B>;
using true_type = bool_constant<true>;
using false_type = bool_constant<false>;

//#################################is_void########################################################
template<typename T>
struct is_void: std::false_type{};

template<>
struct is_void<void>: std::true_type{};

template<typename T>
inline constexpr bool is_void_v = is_void<T>::value;

//#################################remove_const transformation trait########################################################
template<typename T>
struct remove_const : TypeIdentity<T> {};

template<typename T>
struct remove_const <T const> : TypeIdentity<T> {};

template<typename T>
using remove_const_t = typename remove_const<T>::type;

//#################################conditional transformation trait########################################################
template<bool condition, typename T, typename V>
struct conditional : TypeIdentity<T> {};

template<typename T, typename V>
struct conditional<false, T,V> : TypeIdentity<V> {};

template<bool condition, typename T, typename V>
using conditional_t = typename conditional<condition, T, V>::type;

//#################################primary type category########################################################

// is_void
// is_null_pointer
// is_integral
// is_floating_point
// is_array
// is_enum
// is_union
// is_class
// is_function
// is_pointer
// is_lvalue_reference
// is_rvalue_reference
// is_member_object_pointer
// is_member_function_pointer

//#################################is same########################################################
template<typename T1, typename T2>
using is_same_raw = std::is_same<std::remove_cv_t<T1>, std::remove_cv_t<T2>>;

template<typename T1, typename T2>
inline constexpr bool  is_same_raw_v = is_same_raw<T1, T2>::value;

//#################################is pointer########################################################
namespace detail
{
template<typename T>
struct is_pointer_impl : std::false_type{};
template<typename T>
struct is_pointer_impl<T*> : std::true_type{};
}

template<typename T>
using is_pointer = detail::is_pointer_impl<std::remove_cv_t<T>>;

template<typename T>
using is_union = std::bool_constant<__is_union(T)>;

template<typename T>
using is_class = std::bool_constant<__is_class(T)>;

//template<typename T>
//using is_func = std::bool_constant<__is_function(T)>;
///////////////////////////////////////////////////////////////////////////////////////////

namespace detail
{
std::true_type is_nullptr(std::nullptr_t);
std::false_type is_nullptr(...);
}
template<typename T>
using is_null_pointer = decltype (detail::is_nullptr(std::declval<T>()));
///////////////////////////////////////////////////////////////////////////////////////////

namespace detail
{
template<typename T>
std::true_type is_const(TypeIdentity<T const>);
template<typename T>
std::false_type is_const(TypeIdentity<T>);
}
template<typename T>
using is_const = decltype(detail::is_const(std::declval<TypeIdentity<T>>()));
///////////////////////////////////////////////////////////////////////////////////////////

namespace detail
{
template<typename T>
std::true_type canhavepointertomember(int T::*); // not generic
template<typename T>
std::false_type canhavepointertomember(...);
}

template<typename T>
using  canhavepointertomember_ptr = decltype (detail::canhavepointertomember<T>(nullptr)); // generic
///////////////////////////////////////////////////////////////////////////////////////////

namespace detail
{
template<typename T>
std::bool_constant <not std::is_union_v<T>>is_class_or_union(int T::*);
template<typename T>
std::false_type is_class_or_union(...);
}
template<typename T>
using  cis_class = decltype (detail::is_class_or_union<T>(nullptr));


//#################################enable_if########################################################
template<class T,
    typename = std::enable_if_t<std::is_array<T>::value> >
void destroy(T* t) // note: function signature is unmodified
{
    for(std::size_t i = 0; i < std::extent<T>::value; ++i) {
        destroy((*t)[i]);
    }
}

// std::copy(vect.begin(), vect.end(), vect2.begin())
// std::move(vect.begin(), vect.end(), vect2.begin())
// std::copy_backward(vect.begin(), vect.end(), vect2.end())
// std::reverse(vect.begin(), vect.end())
// std::reverse_copy(vect.begin(), vect.end(), vect2.begin())

// rbegin and rend to get it reversed
// cbegin cend // const iterator

namespace detail
{
template<typename T>
struct isChar_helper: false_type{};
template<>
struct isChar_helper<char>: true_type{};
}
template<typename T>
using  isChar = detail::isChar_helper<std::remove_cv_t<T>>;


template <int N>
struct Factorial {
  static const int value = N * Factorial<N - 1>::value;
};

// Specialization of Factorial for base case = 1.
template <>
struct Factorial<1> {
  static const int value = 1;
};

template< int n > struct TMPFib {
  enum {
    val = TMPFib< n-1 >::val + TMPFib< n-2 >::val
  };
};

template<> struct TMPFib< 1 > {
  enum { val = 1 };
};

template<> struct TMPFib< 0 > {
  enum { val = 0 };
};

//constexpr bool wrapper()
//{
//    if (std::is_constant_evaluated())
//    return false;
//    else
//    {
//        return true
//    }
//};

//template<wrapper& condition, int a, int b>
//struct ifElse {
//    enum {
//        val = condition.checked ? a: b
//    };
//};

//template <wrapper& cond, int val, int val2>
//using  condition = typename AnyIdentity<cond.checked?val:val2>::value;

