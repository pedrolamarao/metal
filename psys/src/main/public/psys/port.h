// Copyright (C) 2021 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#pragma once

namespace ps
{
  //! I/O port

  template <template <unsigned> typename P, unsigned S>
  concept is_port = requires (P<S> x)
  {
    typename P<S>::address_type;
    typename P<S>::data_type;
    P<S> { typename P<S>::address_type {} };
    typename P<S>::data_type { x.read() };
    x.write( typename P<S>::data_type {} );
  };
}