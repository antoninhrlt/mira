// This file is part of "mira"
// Under the MIT License
// Copyright (c) 2022 Antonin Hérault

#include <assert.h>
#include <stdbool.h>

#include "x11.h"

#include "wm/handler.h"
#include "wm/wm.h"

WM new_wm(void) {
    Display* display = xopen_display(NULL);
    XWindowAttributes window_attrs;
    XEvent event;

    WM wm = { display, window_attrs, event };
    return wm;
}

void free_wm(WM* self) {
    xclose_display(self->display);
    self = (WM*) NULL;
}

void run_wm(WM* self) {
    while (true) {
        update_handler(self);
        handle(self);
    }
}

void raise_window(WM* self, XWindow window) {

}
