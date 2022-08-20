// This file is part of "mira"
// Under the MIT License
// Copyright (c) 2022 Antonin Hérault

#include <assert.h>

#include "x11.h"

#include "wm/handler.h"
#include "wm/wm.h"

void update_handler(WM* wm) {
    xnext_event(wm->display, &wm->event);
}

void handle(WM* wm) {
    switch (wm->event.type) {
        case KeyPress:
            on_keypress(wm);
            break;
        default:
            break;     
    }
}

void on_keypress(WM* wm) {
    assert(wm->event.type == KeyPress);

    // Shows up the window under the cursor 
    if (wm->event.xkey.subwindow != None) {
        xraise_window(wm->display, wm->event.xkey.subwindow);
    }
}
