// Copyright (C) 2023 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

module;

#include <pc/pic.h>

export module br.dev.pedrolamarao.metal.pc:pic;

export namespace pc
{
    using ::pc::pic_buffering;
    using ::pc::pic_read;
    using ::pc::pic_mask;
    using ::pc::pic;
    using ::pc::master_pic;
    using ::pc::slave_pic;
}