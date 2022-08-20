// This file is part of "mira"
// Under the MIT License
// Copyright (c) 2022 Antonin Hérault

#include <assert.h>

#include "x11.h"

#include "wm/handler.h"
#include "wm/wm.h"

void init_handler(WM* wm) {
    XGrabKey(
        wm->display, 
        XKeysymToKeycode(wm->display, XStringToKeysym("F1")), 
        Mod1Mask,
        DefaultRootWindow(wm->display), 
        True, 
        GrabModeAsync, 
        GrabModeAsync
    );
    
    XGrabButton(
        wm->display, 
        1, 
        Mod1Mask, 
        DefaultRootWindow(wm->display), 
        True,
        ButtonPressMask | ButtonReleaseMask | PointerMotionMask, 
        GrabModeAsync, 
        GrabModeAsync, 
        None, 
        None
    );
    
    XGrabButton(
        wm->display, 
        3, 
        Mod1Mask, 
        DefaultRootWindow(wm->display), 
        True,
        ButtonPressMask | ButtonReleaseMask | PointerMotionMask, 
        GrabModeAsync, 
        GrabModeAsync, 
        None, 
        None
    );
}

void update_handler(WM* wm) {
    xnext_event(wm->display, &wm->event);
}

void handle(WM* wm) {
    switch (wm->event.type) {
        case KeyPress:
            on_keypress(wm);
            break;
        case ButtonPress:
            on_button_press(wm);
            break;
        case ButtonRelease:
            on_button_release(wm);
            break;
        case MotionNotify:
            on_motion_notify(wm);
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

void on_button_press(WM* wm) {
    // Select the window
    XGetWindowAttributes(
        wm->display, 
        wm->event.xbutton.subwindow,
        &wm->window_attrs
    );

    wm->button_event = wm->event.xbutton;
}

void on_button_release(WM* wm) {
    // Unselect the window
    wm->button_event.subwindow = None;
}

#define MAX(a, b) ((a) > (b) ? (a) : (b))

void on_motion_notify(WM* wm) {
    // Move a window from the cursor's position
    int x_diff = wm->event.xbutton.x_root - wm->button_event.x_root;
    int y_diff = wm->event.xbutton.y_root - wm->button_event.y_root;

    XMoveResizeWindow(
        wm->display, 
        wm->button_event.subwindow,
        wm->window_attrs.x + ( wm->button_event.button == 1 ? x_diff : 0 ),
        wm->window_attrs.y + ( wm->button_event.button == 1 ? y_diff : 0 ),
        MAX(1, wm->window_attrs.width + ( wm->button_event.button == 3 ? x_diff : 0 )),
        MAX(1, wm->window_attrs.height + ( wm->button_event.button == 3 ? y_diff : 0 ))
    );
}
