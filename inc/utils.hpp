// This file is part of "mirawm"
// Under the MIT License
// Copyright (c) mirade-org, Antonin Hérault

#pragma once

#define match(expr) switch (expr)
#define with(what, expr) \
    case what: \
        expr \
        break
