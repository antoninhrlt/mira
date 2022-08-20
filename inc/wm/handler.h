// This file is part of "mira"
// Under the MIT License
// Copyright (c) 2022 Antonin Hérault

#ifndef MIRA_HANDLER
#define MIRA_HANDLER

#include "x11.h"

#include "wm/wm.h"

/// Updates the `event` attribute by the caught next event on display
void update_handler(WM* wm);
/// Calls the right `on_...` function according to the retrieved event
void handle(WM* wm);

void on_keypress(WM* wm);

#endif // MIRA_HANDLER
