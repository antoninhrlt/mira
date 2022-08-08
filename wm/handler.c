// This file is part of "mirade"
// Under the MIT License
// Copyright (c) 2022 Antonin Hérault

#include "wm/handler.h"
#include "wm/wm.h"

void handle(WM* wm, XEvent event) {
    switch (event.type) {
        case CreateNotify:
            on_create_notify(event.xcreatewindow);
            break;
        case DestroyNotify:
            on_destroy_notify(event.xdestroywindow);
            break;

        case ReparentNotify:
            on_reparent_notify(event.xreparent);
            break;

        case MapNotify:
            on_map_notify(event.xmap);
            break;
        case MapRequest:
            on_map_request(wm, event.xmaprequest);
            break;

        case UnmapNotify:
            on_unmap_notify(wm, event.xunmap);
            break;

        case ConfigureNotify:
            on_configure_notify(event.xconfigure);
            break;
        case ConfigureRequest:
            on_configure_request(wm, event.xconfigurerequest);
            break;

        default:
            break;
    }
}

void on_create_notify(const XCreateWindowEvent event) {

}

void on_destroy_notify(const XDestroyWindowEvent event) {
    
}

void on_reparent_notify(const XReparentEvent event) {

}

void on_map_notify(const XMapEvent event) {
    
}

void on_map_request(WM* wm, const XMapRequestEvent event) {
    Client client = new_client(event.window, false);
    wm_frame_window(wm, client);
}

void on_unmap_notify(WM* wm, const XUnmapEvent event) {
    if (event.event == wm->root) {
        return;
    }

    wm_unframe_window(wm, event.window);
}

void on_configure_notify(const XConfigureEvent event) {

}

void on_configure_request(WM* wm, const XConfigureRequestEvent event) {
        // Setup configurations
    XWindowChanges changes;
    changes.x = event.x;
    changes.y = event.y;
    changes.width = event.width;
    changes.height = event.height;
    changes.border_width = event.border_width;
    changes.sibling = event.above;
    changes.stack_mode = event.detail;

    // Configures the window from retrieved configurations
    XConfigureWindow(
        wm->display, 
        event.window, 
        event.value_mask, 
        &changes
    );
}
