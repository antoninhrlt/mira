// This file is part of "mira"
// Under the MIT License
// Copyright (c) 2022 Antonin Hérault

/// Review for the X11 header file to get better names following this project's
/// naming convention

#ifndef MIRA_X11
#define MIRA_X11

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#define XDisplay    Display
#define XWindow Window

#define xopen_display   XOpenDisplay
#define xclose_display  XCloseDisplay
#define xnext_event XNextEvent
#define xraise_window   XRaiseWindow
#define xcreate_simple_window   XCreateSimpleWindow
#define xkeysym_to_keycode  XKeysymToKeycode
#define xgrab_button    XGrabButton
#define xdefault_root_window    DefaultRootWindow
#define xget_window_attributes  XGetWindowAttributes
#define xmove_resize_window XMoveResizeWindow
#define xconfigure_window   XConfigureWindow
#define xdisplay_width  XDisplayWidth
#define xdisplay_height XDisplayHeight
#define xdefault_screen  DefaultScreen
#define xset_window_border  XSetWindowBorder
#define xset_window_border_width    XSetWindowBorderWidth
#define xset_window_border  XSetWindowBorder
#define xset_input_focus    XSetInputFocus
#define xmap_window XMapWindow
#define xroot_window    XRootWindow
#define xselect_input   XSelectInput
#define xset_window_background  XSetWindowBackground
#define xset_error_handler  XSetErrorHandler
#define xget_error_text XGetErrorText
#define xgrab_key   XGrabKey
#define xinter_atom XInternAtom
#define xsend_event XSendEvent

const char* xrequest_code_to_string(unsigned char request_code);

#endif // MIRA_X11
