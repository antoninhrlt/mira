// This file is part of "mira"
// Under the MIT License
// Copyright (c) 2022 Antonin Hérault

#ifndef MIRA_WM
#define MIRA_WM

#include "x11.h"

#include "wm/structs.h"

WM new_wm(void);
void free_wm(WM* self);

/// Creates a loop handling the event then let `handler` manages
void run_wm(WM* self);

/// Shows the window over the others
void raise_window(WM* self, XWindow window);

#endif // MIRA_WM
