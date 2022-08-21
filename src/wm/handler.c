// This file is part of "mira"
// Under the MIT License
// Copyright (c) 2022 Antonin Hérault

#include <assert.h>
#include <stdbool.h>

#include "x11.h"

#include "wm/handler.h"
#include "wm/wm.h"

void init_handler(WM* wm) {    
    xgrab_button(
        wm->display, 
        1, 
        Mod1Mask, 
        xdefault_root_window(wm->display), 
        True,
        ButtonPressMask | ButtonReleaseMask | PointerMotionMask, 
        GrabModeAsync, 
        GrabModeAsync, 
        None, 
        None
    );
    
    xgrab_button(
        wm->display, 
        3, 
        Mod1Mask, 
        xdefault_root_window(wm->display), 
        True,
        ButtonPressMask | ButtonReleaseMask | PointerMotionMask, 
        GrabModeAsync, 
        GrabModeAsync, 
        None, 
        None
    );

    xselect_input(
        wm->display,
        xroot_window(wm->display, xdefault_screen(wm->display)),
        SubstructureNotifyMask | SubstructureRedirectMask
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
        case MapRequest:
            on_map_request(wm, wm->event.xmaprequest);
            break;
        case ConfigureNotify:
            on_configure_notify(wm, wm->event.xconfigure);
            break;
        case ConfigureRequest:
            on_configure_request(wm, wm->event.xconfigurerequest);
            break;
        case DestroyNotify:
            on_destroy_notify(wm, wm->event.xdestroywindow);
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
    xget_window_attributes(
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

    xmove_resize_window(
        wm->display, 
        wm->button_event.subwindow,
        wm->window_attrs.x + ( wm->button_event.button == 1 ? x_diff : 0 ),
        wm->window_attrs.y + ( wm->button_event.button == 1 ? y_diff : 0 ),
        MAX(1, wm->window_attrs.width + ( wm->button_event.button == 3 ? x_diff : 0 )),
        MAX(1, wm->window_attrs.height + ( wm->button_event.button == 3 ? y_diff : 0 ))
    );
}

void on_map_request(WM* wm, XMapRequestEvent event) {
    Client* client = wm->head_client;

    for (; client; client = client->next_client) {
        if (event.window == client->window) {
            xmap_window(wm->display, event.window);
            return;
        }
    }

    add_window(wm, event.window);
    xmap_window(wm->display, event.window);
    tile(wm);
    update_current_client(wm);
}

void on_configure_request(WM* wm, XConfigureRequestEvent event) {
    XWindowChanges changes;

    changes.x = event.x;
    changes.y = event.y;
    changes.width = event.width;
    changes.height = event.height;
    changes.border_width = event.border_width;
    changes.sibling = event.above;
    changes.stack_mode = event.detail;

    xconfigure_window(wm->display, event.window, event.value_mask, &changes);
}

void on_configure_notify(WM* wm, XConfigureEvent event) {

}

void on_destroy_notify(WM* wm, XDestroyWindowEvent event) {
    Client* client = wm->head_client;
    
    bool is_found = 0;
    for (; client; client = client->next_client) {
        if (event.window == client->window) {
            is_found = true;
            break;
        }
    }

    if (is_found == false) {
        return;
    }

    remove_window(wm, event.window);
    tile(wm);
    update_current_client(wm);
}
