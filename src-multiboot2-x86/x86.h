// Copyright (C) 2012 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#pragma once

//! Loads the global descriptor table
//!
//! @see x86::load_global_descriptor_table

void load_global_descriptor_table ();

//! Loads the interrupt descriptor table
//!
//! @see x86::load_interrupt_descriptor_table

void load_interrupt_descriptor_table ();
