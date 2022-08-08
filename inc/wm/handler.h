// This file is part of "mirade"
// Under the MIT License
// Copyright (c) 2022 Antonin Hérault

#ifndef MIRADE_WM_HANDLER
#define MIRADE_WM_HANDLER

#include <stdlib.h>

#include <X11/Xlib.h>

#include "wm/client.h"
#include "wm/wm.h"

#define ERROR_MAX_LENGTH   2048

/**
 * @brief Handles the errors thrown by X11
 * @note Set as `static` because the function's address is given to X11
 * @param display A window manager's member
 * @param event The error given by X11
*/
static int on_x_error(Display* display, XErrorEvent* event) {
    char error_text[ERROR_MAX_LENGTH];
    XGetErrorText(display, event->error_code, error_text, ERROR_MAX_LENGTH);

    // TODO : Print that error to the user
    exit(1);
    return 0;
}

/**
 * @brief Determines if a window manager is already running on the system
 * @param display A window manager's member
 * @param event The error given by X11
*/
static int on_wm_detected(Display* _display, XErrorEvent* _event) {
    // TODO
    exit(2);
    return 0;
}

/**
 * Call a function according to the event's type
*/
void handle(WM* wm, XEvent event);

void on_create_notify(const XCreateWindowEvent event);
void on_destroy_notify(const XDestroyWindowEvent event);
void on_reparent_notify(const XReparentEvent event);
void on_map_notify(const XMapEvent event);
void on_map_request(WM* wm, const XMapRequestEvent event);
void on_unmap_notify(WM* wm, const XUnmapEvent event);
void on_configure_notify(const XConfigureEvent event);
void on_configure_request(WM* wm, const XConfigureRequestEvent event);

#endif // MIRADE_WM_HANDLER
