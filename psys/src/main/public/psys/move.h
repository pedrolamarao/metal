// Copyright (C) 2021 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#pragma once

namespace ps
{
  template < class T >
  struct remove_reference;

  template<class T> struct remove_reference      {typedef T type;};
  template<class T> struct remove_reference<T&>  {typedef T type;};
  template<class T> struct remove_reference<T&&> {typedef T type;};

  template < class T >
  constexpr
  auto move ( T&& t ) noexcept -> typename remove_reference<T>::type&&
  {
    return static_cast<typename remove_reference<T>::type&&>(t);
  }
}