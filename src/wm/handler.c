// This file is part of "mirade"
// Under the MIT License
// Copyright (c) 2022 Antonin Hérault

#include "wm/handler.h"
#include "wm/manager.h"

static int on_XError(Display* display, XErrorEvent* event) {
    char error_text[ERROR_MAX_LENGTH];
    XGetErrorText(display, event->error_code, error_text, ERROR_MAX_LENGTH);

    // TODO : Print that error to the user
    return 0;
}

static int on_wm_detected(Display* _display, XErrorEvent* _event) {
    // TODO
    return 0;
}

void on_create_notify(const XCreateWindowEvent event) {}

void on_destroy_notify(const XDestroyWindowEvent event) {}

void on_reparent_notify(const XReparentEvent event) {}

void on_configure_notify(const XConfigureEvent event) {}

void on_map_notify(const XMapEvent event) {}

void on_unmap_notify(WM* wm, const XUnmapEvent event) {
    // Ignores reparented pre-existing window
    if (event.event == wm->root) {
        return;
    }

    wm_unframe(wm, event.window);
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

void on_map_request(WM* wm, const XMapRequestEvent event) {
    wm_frame(event.window, false);
    XMapWindow(wm->display, event.window);
}

void on_button_press(const XButtonPressedEvent event);

void on_button_release(WM* wm, const XButtonReleasedEvent event) {
    const Window frame = wm->clients[event.window];

    Window returned_root;
    int x = 0;
    int y = 0;
    u_int width = 0;
    u_int height = 0;
    u_int border_width = 0;
    u_int depth = 0;

    XGetGeometry(
        wm->display,
        frame,
        &returned_root,
        &x,
        &y,
        &width,
        &height,
        &border_width,
        &depth
    );

    // Places the window at the top, over all the others
    XRaiseWindow(wm->display, frame);
}

void on_key_press(WM* wm, const XKeyPressedEvent event) {
    // Closes a window when ALT + F4 pressed
    if (
        (event.state & Mod1Mask) &&
        (event.keycode == XKeysymToKeycode(wm->display, XK_F4))
    ) {
        // Terrible way to kill a window
        // TODO : Safe kill alternative when it's possible
        XKillClient(wm->display, event.window);
        return;
    }
    
    // // Switches to another window when ALT + TAB pressed
    // if (
    //     (event.state & Mod1Mask) &&
    //     (event.keycode == XKeysymToKeycode(wm->display, XK_Tab))
    // ) {
    //     auto i = wm->clients.find(event.window);
    //     ++i;
    //     if (i == wm->clients.end()) {
    //         i = wm->clients.begin();
    //     }

    //     XRaiseWindow(wm->display, i->second);
    //     XSetInputFocus(
    //         wm->display, 
    //         i->first, 
    //         RevertToPointerRoot, 
    //         CurrentTime
    //     );

    //     return;
    // }

    // Others...
}

void on_key_release(const XKeyReleasedEvent event) {}
