// This file is part of "mirawm"
// Under the MIT License
// Copyright (c) mirade-org, Antonin Hérault

module;

#include <X11/Xlib.h>
#include <cstring>
#include "utils.hpp"

export module notify;

import utils;

export void create_notification(const char *message) {
    Display *display;
    Window window;
    int screen;

    display = XOpenDisplay(nullptr);
    if (display == nullptr) {
        todo();
        return;
    }
    
    screen = DefaultScreen(display);
    window = XCreateSimpleWindow(
        display,
        RootWindow(display, screen),
        10,
        10,
        100,
        100,
        1,
        BlackPixel(display, screen),
        WhitePixel(display, screen)
    );

    XSelectInput(display, window, ExposureMask | KeyPressMask);
    XMapWindow(display, window);

    bool running = true;

    XEvent event;
    while (running) {
        XNextEvent(display, &event);

        match (event.type) {
            with (Expose,
                XDrawString(
                    display, 
                    window, 
                    DefaultGC(display, screen), 
                    10, 
                    50, 
                    message, 
                    strlen(message)
                );
            );
            with (KeyPress,
                running = false;
            );

            default:
                break;
        }
    }
}
