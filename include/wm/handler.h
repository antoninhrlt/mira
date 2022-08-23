// This file is part of "mira"
// Under the MIT License
// Copyright (c) 2022 Antonin Hérault

#ifndef MIRA_HANDLER
#define MIRA_HANDLER

#include "x11.h"

#include "wm/wm.h"

void init_handler(WM* wm);
/// Updates the `event` attribute by the caught next event on display
void update_handler(WM* wm);
/// Calls the right `on_...` function according to the retrieved event
void handle(WM* wm);

void on_keypress(WM* wm, XKeyEvent event);
void on_button_press(WM* wm, XButtonEvent event);
void on_button_release(WM* wm);
void on_motion_notify(WM* wm);
void on_map_request(WM* wm, XMapRequestEvent event);
void on_configure_request(WM* wm, XConfigureRequestEvent event);
void on_configure_notify(WM* wm, XConfigureEvent event);
void on_destroy_notify(WM* wm, XDestroyWindowEvent event);

static int on_xerror(XDisplay* display, XErrorEvent* event);

#endif // MIRA_HANDLER
