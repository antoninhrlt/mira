// This file is part of "mira"
// Under the MIT License
// Copyright (c) 2022 Antonin Hérault

#ifndef MIRA_WM
#define MIRA_WM

#include "x11.h"

#include "wm/client.h"

typedef struct {
    XDisplay* display;
    /// The current retrieved event in the displaying loop
    XWindowAttributes window_attrs;
    XEvent event;
    XButtonEvent button_event;

    Client* head_client;
    Client* current_client;
} WM;

WM new_wm(void);
void free_wm(WM* self);

/// Creates a loop handling the event then let `handler` manages
void run_wm(WM* self);
/// Shows the window over the others
void raise_window(WM* self, XWindow window);
void add_window(WM* self, XWindow window);
void remove_window(WM* self, XWindow window);

void tile(WM* self);
void update_current_client(WM* self);

#endif // MIRA_WM
