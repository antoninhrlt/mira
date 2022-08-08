#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "wm/client.h"
#include "wm/handler.h"
#include "wm/wm.h"

int main(void) {
    WM wm = new_wm();
    run_wm(&wm);
    free_wm(&wm);

    return 0;
}

WM new_wm(void) {
    Display* display = XOpenDisplay(NULL);
    assert(display != NULL);

    Window root = DefaultRootWindow(display);
    Clients clients = new_clients();

    WM wm = { display, root, clients };
    return wm;
}

void free_wm(WM* wm) {
    XCloseDisplay(wm->display);
    wm->root = (Window) NULL;
    free_clients(&wm->clients);
}

void run_wm(WM* wm) {
    // Checks for already-running WM on the system
    XSetErrorHandler(&  on_wm_detected);
    XSelectInput(
        wm->display,
        wm->root,
        SubstructureRedirectMask | SubstructureNotifyMask
    );

    XSync(wm->display, false);

    // Sets the default error handler
    XSetErrorHandler(&on_x_error);

    // Frames already-running windows from the display 
    wm_frame_old_windows(wm);
    
    // Runs
    while (true) {
        // Retrieves event
        XEvent event;
        XNextEvent(wm->display, &event);

        handle(wm, event);
    }
}

void wm_frame_old_windows(WM* wm) {
    XGrabServer(wm->display);

    Window returned_root;
    Window returned_parent;
    Window* top_level_windows;
    unsigned int length_top_level_windows;

    XQueryTree(
        wm->display, 
        wm->root, 
        &returned_root,
        &returned_parent,
        &top_level_windows,
        &length_top_level_windows
    );

    for (size_t i = 0; i < length_top_level_windows; ++i) {
        Client old_window = new_client(top_level_windows[i], true);
        wm_frame_window(wm, old_window);
    }

    XFree(top_level_windows);
    XUngrabServer(wm->display);
}

void wm_frame_window(WM* wm, Client client) {
    // Retrieves window attributes
    XWindowAttributes window_attributes;
    XGetWindowAttributes(wm->display, client.window, &window_attributes);

    if (client.is_old) {
        if (
            window_attributes.override_redirect || 
            window_attributes.map_state != IsViewable
        ) {
            return;
        }
    }

    // Creates the window's frame
    const Window frame = XCreateSimpleWindow(
        wm->display,
        wm->root,
        window_attributes.x,
        window_attributes.y,
        window_attributes.width,
        window_attributes.height,
        WINDOW_BORDER_WIDTH,
        WINDOW_BORDER_COLOR,
        WINDOW_BG_COLOR
    );

    XSelectInput(
        wm->display, 
        frame, 
        SubstructureRedirectMask | SubstructureNotifyMask
    );

    XAddToSaveSet(wm->display, client.window);
    XReparentWindow(wm->display, client.window, frame, 0, 0);
    XMapWindow(wm->display, frame);

    // Saves client
    add_client(&wm->clients, client);

    // TODO : XGrabKey() for moving and switching
}

void wm_unframe_window(WM* wm, long client_id) {
    Client* client = get_client_by_id(wm->clients, client_id);
    const Window window = client->window;

    XUnmapWindow(wm->display, window);

    XReparentWindow(
        wm->display,
        window,
        wm->root,
        0,
        0
    );

    XRemoveFromSaveSet(wm->display, window);
    XDestroyWindow(wm->display, window);
    
    free_client(client);
}