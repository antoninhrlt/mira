// This file is part of "mirade"
// Under the MIT License
// Copyright (c) 2022 Antonin Hérault

#ifndef MIRADE_WM
#define MIRADE_WM

#include <X11/Xlib.h>

#include "wm/client.h"

typedef struct wm {
    Display* display;
    Window root;
    Clients clients;
} WM;

/**
 * Creates a new WM object with attributes set.
 * @returns WM object with attributes set.
*/
WM new_wm(void);

/**
 * Closes the X display and free other elements.
 * @param wm Object to free.
*/
void free_wm(WM* wm);

/**
 * Loops till infinite and gets event. Does some useful work before starting the 
 * WM.
 * @param wm Object to be run.
*/
void run_wm(WM* wm);

/**
 * Frames already-running windows from the initial display 
*/
void wm_frame_old_windows(WM* wm);

/**
 * @param window Client
 * @param is_old If it was created before the WM run
*/
void wm_frame_window(WM* wm, Client client);

/**
 * Unframes already-running windows from the initial display 
*/
void wm_unframe_windows(WM* wm, long client_id);

#endif // MIRADE_WM
