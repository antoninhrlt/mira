// This file is part of "mirade"
// Under the MIT License
// Copyright (c) 2022 Antonin Hérault

#ifndef MIRADE_WM_MANAGER
#define MIRADE_WM_MANAGER

#include <stdbool.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "wm/clients.h"

struct wm {
    Display* display;
    Window root;
    ClientsMap clients;
};

typedef struct wm WM;

/**
 * @brief Creates a new window manager object
 * @details Initializes the attributes by opening a display and retrieving the 
 * root window, thanks to X11
*/
WM new_wm(void);

/**
 * @brief Deletes a window manager object by freeing each member
 * @details Closes display thanks to X11
*/
void free_wm(WM* wm);

/**
 * @brief Runner function using all the other window manager functions
*/
void run_wm(WM* wm);

void check_wm(WM* wm);

/**
 * @brief Frames a window on the display
*/
void wm_frame(WM* wm, Window window, bool is_created_before_wm);

/**
 * @brief Unframes a window from the display
*/
void wm_unframe(WM* wm, Window window);

#endif // MIRADE_WM_MANAGER
