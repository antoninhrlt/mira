// This file is part of "mirade"
// Under the MIT License
// Copyright (c) 2022 Antonin Hérault

#ifndef MIRADE_WM_HANDLER
#define MIRADE_WM_HANDLER

/**
 * There are two kinds of handle functions, "on...notify" and "on...request".
 * 
 * In common cases, the function will require the window manager object given as
 * parameter to have an access on the different attributes.
*/

#include <stdbool.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "wm/manager.h"

#define ERROR_MAX_LENGTH   2048

/**
 * @brief Handles the errors thrown by X11
 * @note Set as `static` because the function's address is given to X11
 * @param display A window manager's member
 * @param event The error given by X11
*/
static int on_XError(Display* display, XErrorEvent* event);

/**
 * @brief Determines if a window manager is already running on the system
 * @param display A window manager's member
 * @param event The error given by X11
*/
static int on_wm_detected(Display* _display, XErrorEvent* _event);

void on_create_notify(const XCreateWindowEvent event);

void on_destroy_notify(const XDestroyWindowEvent event);

void on_reparent_notify(const XReparentEvent event);

void on_configure_notify(const XConfigureEvent event);

void on_map_notify(const XMapEvent event);

/**
 * @brief Unframes a window, ignores reparented pre-existing window
 * @param manager Pointer on the window manager to use its members
 * @param event The `window` attribute is the window to detach
*/
void on_unmap_notify(WM* manager, const XUnmapEvent event);

/**
 * @brief Configures a window as it's requested in `event`
 * @param manager Pointer on the window manager to use its members
 * @param event Contains all the information for the window configuration
*/
void on_configure_request(WM* manager, const XConfigureRequestEvent event);

/**
 * @brief Maps a window to the display
 * @param manager Pointer on the window manager to use its members
 * @param event The `window` attribute is the window to attach
*/
void on_map_request(WM* manager, const XMapRequestEvent event);

void on_button_press(const XButtonPressedEvent event);

/**
 * @brief Places the selected window at the top, over all the others
 * @param manager Pointer on the window manager to use its members
 * @param event The `window` attribute is the selected window
*/
void on_button_release(WM* manager, const XButtonReleasedEvent event);

/**
 * @brief Checks what key/s was/were pressed to call the right functions
 * @param manager Pointer on the window manager to use its members
 * @param event Contains all the mouse and keyboard information and status
*/
void on_key_press(WM* manager, const XKeyPressedEvent event);

void on_key_release(const XKeyReleasedEvent event);

#endif // MIRADE_WM_HANDLER
