// This file is part of "mira"
// Under the MIT License
// Copyright (c) 2022 Antonin Hérault

#include <assert.h>
#include <stdbool.h>

#include "x11.h"

#include "wm/structs.h"
#include "wm/wm.h"

WM new_wm(void) {
    Display* display = xopen_display(NULL);
    XWindowAttributes window_attrs;
    Handler handler = new_handler(NULL);

    WM wm = { display, window_attrs, handler };
    wm.handler.wm = wm;

    return wm;
}

void free_wm(WM* self) {
    xclose_display(self->display);
    self = (WM*) NULL;
}

void run_wm(WM* self) {
    while (true) {
        update_handler(&wm->handler);
        handle(&wm->handler);
    }
}

void raise_window(WM* self, XWindow window) {

}
