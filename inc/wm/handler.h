// This file is part of "mira"
// Under the MIT License
// Copyright (c) 2022 Antonin Hérault

#ifndef MIRA_HANDLER
#define MIRA_HANDLER

#include "x11.h"

#include "wm/structs.h"

Handler new_handler(WM* wm);
void free_handler(Handler* self);

/// Updates the `event` attribute by the caught next event on display
void update_handler(Handler* self);
/// Calls the right `on_...` function according to the retrieved event
void handle(Handler* self);

void on_keypress(Handler* self);

#endif // MIRA_HANDLER
