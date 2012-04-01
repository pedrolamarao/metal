// Copyright (C) 2012 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#pragma once

#include <aasgard/x86/gdt.h>

//! Loads global descriptor table
//!
//! @see x86::load_global_descriptor_table

void load_global_descriptor_table ();
