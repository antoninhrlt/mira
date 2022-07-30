// This file is part of "mirade"
// Under the MIT License
// Copyright (c) 2022 Antonin Hérault

#include <assert.h>
#include <stdbool.h>

#include "wm/handler.h"
#include "wm/manager.h"

WM new_wm(void) {
    Display* display = XOpenDisplay(NULL);
    assert(display != NULL);

    Window root = DefaultRootWindow(display);

    return WM {display, root, NULL};
}

void free_wm(WM* wm) {
    XCloseDisplay(wm->display);
}

void run_wm(WM* wm) {
    check_wm(wm);
    XSetErrorHandler(on_XError);
    XGrabServer(wm->display);
}

void check_wm(WM* wm) {

}

void wm_frame(Window window, bool is_created_before_wm) {

}

void wm_unframe(Window window) {

}