/*
 * File: reference_vm
 * Created:
 * January 29, 2020
 * Author: Andrew Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
 *
 * Copyright &copy; 2020 Christi Crucifixi, LLC. All rights reserved.
 */

#include "reference_vm.h"
#include <stdlib.h>

static const uintptr_t STACK = 0;
static const size_t STACK_SIZE = 1024;
static const uintptr_t DATA = STACK_SIZE;

