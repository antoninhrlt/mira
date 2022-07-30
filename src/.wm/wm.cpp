// This file is part of "mirawm"
// Under the MIT License
// Copyright (c) mirade-org, Antonin Hérault

module;

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <map>
#include "utils.hpp"

export module wm;

import handler;
import utils;

/**
 * Main structure for "mirawm"
 * Window manager
*/
export class WM {
    private:
        Display *_display;
        Handler _handler;

    public:
        std::map<Window, Window> _clients;
        Window _root;

    public:
        WM() {
            _display = XOpenDisplay(nullptr);
            if (_display == nullptr) {
                todo();
            }

            _root = DefaultRootWindow(_display);
            _handler = Handler(_display);
        }

        ~WM()  {
            XCloseDisplay(_display);
        }

        void run() {
            _check_wm();
            XSetErrorHandler(&Handler::on_XError);

            XGrabServer(_display);

            Window returned_root;
            Window returned_parent;
            Window *top_level_windows;
            u_int n_top_level_window;
            
            XQueryTree(
                _display,
                _root,
                &returned_root,
                &returned_parent,
                &top_level_windows,
                &n_top_level_window
            );

            // --> should be : returned_root == _root 
            for (u_int i = 0; i < n_top_level_window; i += 1) {
                this->frame(top_level_windows[i], true);
            }

            XFree(top_level_windows);
            XUngrabServer(_display);

            while (true) {
                XEvent event;
                XNextEvent(_display, &event);
                _call_handler(event);
            }
        }

        /**
         * Frame a window on the screen
         * SEE `::unwframe()`
         * 
         * @param created_before_wm If the window was created before the window
         * manager
        */
        void frame(Window window, bool created_before_wm) {
            const int BORDER_WIDTH = 3;
            const long BORDER_COLOR = 0xff0000;
            const long BG_COLOR = 0x0000ff;

            XWindowAttributes window_attributes;
            XGetWindowAttributes(_display, window, &window_attributes);

            if (created_before_wm) {
                if (
                    window_attributes.override_redirect || 
                    window_attributes.map_state != IsViewable
                ) {
                    return;
                }
            }

            const Window frame = XCreateSimpleWindow(
                _display,
                _root,
                window_attributes.x,
                window_attributes.y,
                window_attributes.width,
                window_attributes.height,
                BORDER_WIDTH,
                BORDER_COLOR,
                BG_COLOR
            );

            XSelectInput(
                _display,
                frame,
                SubstructureRedirectMask | SubstructureNotifyMask
            );

            XAddToSaveSet(_display, window);
            XReparentWindow(
                _display,
                window,
                frame,
                0,
                0
            );

            XMapWindow(_display, frame);
            _clients[window] = frame; // save frame handler

            // Close window by ALT + F4
            XGrabKey(
                _display,
                XKeysymToKeycode(_display, XK_F4),
                Mod1Mask,
                window,
                false,
                GrabModeAsync,
                GrabModeAsync
            );

            // Switch to another window by ALT + TAB
            XGrabKey(
                _display,
                XKeysymToKeycode(_display, XK_Tab),
                Mod1Mask,
                window,
                false,
                GrabModeAsync,
                GrabModeAsync
            );
        }

        /**
         * Inverted function for `::frame()`
         * Remove a framed window from the screen
        */
        void unframe(Window window) {
            const Window frame = _clients[window];
            XUnmapWindow(_display, frame);

            XReparentWindow(
                _display,
                window,
                _root,
                0,
                0
            );

            XRemoveFromSaveSet(_display, window);
            XDestroyWindow(_display, frame);
            _clients.erase(window); // remove the previously saved handler 
        }

    private:
        // Check if a window manager is already running on the system
        // Temporarily define the error handler as `Handler::on_wm_detected`
        void _check_wm()  {
            // Detect if a window manager is already defined
            XSetErrorHandler(&Handler::on_wm_detected); // temporary error handler
            XSelectInput(
                _display,
                _root,
                SubstructureRedirectMask | SubstructureNotifyMask
            );
            XSync(_display, false);
        }

        /**
         * Call the correct function (mainly from `Handler`)
        */
        void _call_handler(XEvent event) {
            match (event.type) {
                with (CreateNotify,
                    _handler.on_create_notify(event.xcreatewindow);
                );
                with (DestroyNotify,
                    _handler.on_destroy_notify(event.xdestroywindow);
                );
                with (ReparentNotify,
                    _handler.on_reparent_notify(event.xreparent);
                );
                with (ConfigureNotify,
                    _handler.on_configure_notify(event.xconfigure);
                );
                with (MapNotify,
                    _handler.on_map_notify(event.xmap);
                );
                with (UnmapNotify,
                    _handler.on_unmap_notify(this, event.xunmap);
                );
                
                with (ConfigureRequest,
                    _handler.on_configure_request(event.xconfigurerequest);
                );
                with (MapRequest,
                    _handler.on_map_request(this, event.xmaprequest);
                );

                with (ButtonPress,
                    _handler.on_button_press(event.xbutton);
                );
                with (ButtonRelease,
                    _handler.on_button_release(this, event.xbutton);
                );
                with (KeyPress,
                    _handler.on_key_press(this, event.xkey);
                );
                with (KeyRelease,
                    _handler.on_key_release(event.xkey);
                );

                default: break;
            }
        }
};

 
