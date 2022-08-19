// This file is part of "mira"
// Under the MIT License
// Copyright (c) 2022 Antonin Hérault

#include <assert.h>

#include "x11.h"

#include "wm/handler.h"
#include "wm/structs.h"

Handler new_handler(WM* wm) {
    XEvent event;
    Handler handler = { wm, event };
    return handler;
}

void free_handler(Handler* self) {
    self->wm = (WM*) NULL;
    self = (Handler*) NULL;
}

void update_handler(Handler* self) {
    xnext_event(*(self->wm)->display, &self->event);
}

void handle(Handler* self) {
    switch (self->event.type) {
        case KeyPress:
            on_keypress(self);
            break;
        default:
            break;     
    }
}

void on_keypress(Handler* self) {
    assert(self->event.type == KeyPress);

    // Shows up the window under the cursor 
    if (self->event.xkey.subwindow != None) {
        xraise_window(*(self->wm)->display, self->event.xkey.subwindow);
    }
}