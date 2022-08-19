// This file is part of "mira"
// Under the MIT License
// Copyright (c) 2022 Antonin Hérault

/// Review for the X11 header file to get better names following this project's
/// naming convention

#include <X11/Xlib.h>

#define XDisplay    Display
#define XWindow Window

#define xopen_display   XOpenDisplay
#define xclose_display  XCloseDisplay

#define xnext_event XNextEvent
#define xraise_window   XRaiseWindow
