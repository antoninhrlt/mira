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

void on_unmap_notify(WM* manager, const XUnmapEvent event) {
    // Ignores reparented pre-existing window
    if (event.event == manager->root) {
        return;
    }

    wm_unframe(event.window);
}

void on_configure_request(WM* manager, const XConfigureRequestEvent event) {
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
        manager->display, 
        event.window, 
        event.value_mask, 
        &changes
    );
}

void on_map_request(WM* manager, const XMapRequestEvent event) {
    wm_frame(event.window, false);
    XMapWindow(manager->display, event.window);
}

void on_button_press(const XButtonPressedEvent event);

void on_button_release(WM* manager, const XButtonReleasedEvent event) {
    const Window frame = manager->clients[event.window];

    Window returned_root;
    int x = 0;
    int y = 0;
    u_int width = 0;
    u_int height = 0;
    u_int border_width = 0;
    u_int depth = 0;

    XGetGeometry(
        manager->display,
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
    XRaiseWindow(manager->display, frame);
}

void on_key_press(WM* manager, const XKeyPressedEvent event) {
    // Closes a window when ALT + F4 pressed
    if (
        (event.state & Mod1Mask) &&
        (event.keycode == XKeysymToKeycode(manager->display, XK_F4))
    ) {
        // Terrible way to kill a window
        // TODO : Safe kill alternative when it's possible
        XKillClient(manager->display, event.window);
        return;
    }
    
    // Switches to another window when ALT + TAB pressed
    if (
        (event.state & Mod1Mask) &&
        (event.keycode == XKeysymToKeycode(manager->display, XK_Tab))
    ) {
        auto i = manager->clients.find(event.window);
        ++i;
        if (i == manager->clients.end()) {
            i = manager->clients.begin();
        }

        XRaiseWindow(manager->display, i->second);
        XSetInputFocus(
            manager->display, 
            i->first, 
            RevertToPointerRoot, 
            CurrentTime
        );

        return;
    }

    // Others...
}

void on_key_release(const XKeyReleasedEvent event) {}
