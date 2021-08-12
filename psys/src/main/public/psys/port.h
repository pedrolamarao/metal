// Copyright (C) 2021 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#pragma once

namespace ps
{
  template <template <typename> typename T, typename I>
  concept is_port = requires (T<I> x, I y)
  {
    y = x.read();
    x.write(y);
  };
}