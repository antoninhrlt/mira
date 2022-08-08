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

    ClientsMap clients = new_clients_map();

    WM wm = {display, root, clients};
    return wm;
}

void free_wm(WM* wm) {
    XCloseDisplay(wm->display);
    free_clients_map(wm->clients);
}

void run_wm(WM* wm) {
    check_wm(wm);
    XSetErrorHandler(on_XError);
    XGrabServer(wm->display);

    Window returned_root;
    Window returned_parent;
    Window *top_level_windows;
    u_int n_top_level_window;
    
    XQueryTree(
        wm->display,
        wm->root,
        &returned_root,
        &returned_parent,
        &top_level_windows,
        &n_top_level_window
    );

    // --> should be : returned_root == _root 
    for (u_int i = 0; i < n_top_level_window; i += 1) {
        wm_frame(wm, top_level_windows[i], true);
    }

    XFree(top_level_windows);
    XUngrabServer(wm->display);

    while (true) {
        XEvent event;
        XNextEvent(wm->display, &event);
        
        switch (event.type) {
            case CreateNotify:
                on_create_notify(event.xcreatewindow);
                break;
            default:
                break;
        }
    }
}

void check_wm(WM* wm) {
    XSetErrorHandler(on_wm_detected);
    XSelectInput(
        wm->display,
        wm->root,
        SubstructureRedirectMask | SubstructureNotifyMask  
    );
    XSync(wm->display, false);
}

void wm_frame(WM* wm, Window window, bool is_created_before_wm) {
    const int BORDER_WIDTH = 3;
    const long BORDER_COLOR = 0xff0000;
    const long BG_COLOR = 0x0000ff;

    XWindowAttributes window_attributes;
    XGetWindowAttributes(wm->display, window, &window_attributes);

    if (is_created_before_wm) {
        if (
            window_attributes.override_redirect || 
            window_attributes.map_state != IsViewable
        ) {
            return;
        }
    }

    const Window frame = XCreateSimpleWindow(
        wm->display,
        wm->root,
        window_attributes.x,
        window_attributes.y,
        window_attributes.width,
        window_attributes.height,
        BORDER_WIDTH,
        BORDER_COLOR,
        BG_COLOR
    );

    XSelectInput(
        wm->display,
        frame,
        SubstructureRedirectMask | SubstructureNotifyMask
    );

    XAddToSaveSet(wm->display, window);
    XReparentWindow(
        wm->display,
        window,
        frame,
        0,
        0
    );

    XMapWindow(wm->display, frame);
    
    // Saves frame handler
    Window* retrieve_client = get_client_from_map(wm->clients, window);
    *retrieve_client = frame;

    // Closes window by ALT + F4
    XGrabKey(
        wm->display,
        XKeysymToKeycode(wm->display, XK_F4),
        Mod1Mask,
        window,
        false,
        GrabModeAsync,
        GrabModeAsync
    );

    // Switches to another window by ALT + TAB
    XGrabKey(
        wm->display,
        XKeysymToKeycode(wm->display, XK_Tab),
        Mod1Mask,
        window,
        false,
        GrabModeAsync,
        GrabModeAsync
    );
}

void wm_unframe(WM* wm, Window window) {
    const Window* frame = get_client_from_map(wm->clients, window);
    XUnmapWindow(wm->display, *frame);

    XReparentWindow(
        wm->display,
        window,
        wm->root,
        0,
        0
    );

    XRemoveFromSaveSet(wm->display, window);
    XDestroyWindow(wm->display, *frame);
    erase_client_from_map(wm->clients, window);
}