// This file is part of "mira"
// Under the MIT License
// Copyright (c) 2022 Antonin Hérault

#include <stdbool.h>

#include "x11.h"

#include "wm/client.h"
#include "wm/wm.h"

Client new_client(XWindow window) {
    Client client = { NULL, NULL, window };
    return client;   
}

void free_client(Client* self) {
    self->next_client = (Client*) NULL;
    self->previous_client = (Client*) NULL;
    self->window = (XWindow) NULL;
    self = (Client*) NULL;
}

void set_client_defaults(Client* self, WM* wm) {
    xset_window_border_width(
        wm->display, 
        self->window, 
        WINDOW_BORDER_WIDTH
    );

    // xset_window_background(
    //     wm->display,
    //     self->window,
    //     BlackPixel(wm->display, xdefault_screen(wm->display))
    // );

    // Client is not the current client, sets it unfocused
    // As begin set as unfocused, but will be set focused by 
    // `update_current_client()`
    xset_window_border(
        wm->display,
        self->window,
        WINDOW_BORDER_UNFOCUSED
    );
}

void tile_client(Client* self, WM* wm) {
    if (wm->head_client == NULL) {
        return;
    }

    // Full-screen
    xmove_resize_window(
        wm->display,
        self->window,
        0,
        0,
        xdisplay_width(wm->display, xdefault_screen(wm->display)) 
            - WINDOW_BORDER_WIDTH * 2,
        xdisplay_height(wm->display, xdefault_screen(wm->display)) 
            - WINDOW_BORDER_WIDTH * 2
    );
}

void update_clients(WM* wm) {
    Client* client = wm->head_client;

    for (; client; client = client->next_client) {
        set_client_defaults(client, wm);

        if (client == wm->current_client) {
            // Defines specific properties for the current client
            xset_window_border(
                wm->display, 
                client->window, 
                WINDOW_BORDER_FOCUSED
            );

            xset_input_focus(
                wm->display, 
                client->window, 
                RevertToParent, 
                CurrentTime
            );

            // Shows it over the others
            xraise_window(wm->display, client->window);
        }
    }
}

void kill_client(Client* self, WM* wm) {
    if (self == NULL) {
        return;
    }

    XEvent kill_event;
    kill_event.type = ClientMessage;
    kill_event.xclient.window = wm->current_client->window;
    kill_event.xclient.message_type = xinter_atom(
        wm->display, 
        "WM_PROTOCOLS", 
        True
    );
    kill_event.xclient.format = 32;
    kill_event.xclient.data.l[0] = xinter_atom(
        wm->display, 
        "WM_DELETE_WINDOW", 
        True
    );
    kill_event.xclient.data.l[1] = CurrentTime;

    xsend_event(
        wm->display, 
        wm->current_client->window, 
        False, 
        NoEventMask, 
        &kill_event
    );
}
