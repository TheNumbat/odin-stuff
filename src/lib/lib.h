#pragma once

#include "basic.h"

// order matters!

#include "alloc_before.h"
#include "string_before.h"
#include "reflect.h"
#include "printf_before.h"
#include "log.h"
#include "alloc_after.h"
#include "string_after.h"

#include "vec.h"
#include "array.h"
#include "stack.h"
// #include "queue.h"

#include "printf_after.h"
