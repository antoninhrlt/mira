// This file is part of "mira"
// Under the MIT License
// Copyright (c) 2022 Antonin Hérault

#ifndef MIRA_WM
#define MIRA_WM

#include "x11.h"

#include "wm/client.h"

typedef struct wm {
    XDisplay* display;
    /// The current retrieved event in the displaying loop
    XWindowAttributes window_attrs;
    XEvent event;
    XButtonEvent button_event;

    Client* head_client;
    Client* current_client;

    XGraphicsContext graphics_ctx;
} WM;

WM new_wm(void);
void free_wm(WM* self);

/// Creates a loop handling the event then let `handler` manages
void run_wm(WM* self);
/// Shows the window over the others
void add_window(WM* self, XWindow window);
void remove_window(WM* self, XWindow window);
void switch_between_windows(WM* self, XWindow window);

#endif // MIRA_WM
