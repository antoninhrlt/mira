// This file is part of "mira"
// Under the MIT License
// Copyright (c) 2022 Antonin Hérault

#include <stdbool.h>

#include "x11.h"

#include "wm/client.h"
#include "wm/tiling.h"
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

Client* client_from_window(XWindow window, WM* wm) {
    Client* client = wm->head_client;

    for (; client; client = client->next_client) {
        if (client->window == window) {
            return client;
        }
    }

    return NULL;
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

void tile_client(Client* self, WM* wm, TilingMode tiling_mode) {
    if (wm->head_client == NULL) {
        return;
    }

    int x = 0;
    int y = 0;
    int width = 0;
    int height = 0;

    const int DISPLAY_WIDTH = xdisplay_width(wm->display, xdefault_screen(wm->display));
    const int DISPLAY_HEIGHT = xdisplay_height(wm->display, xdefault_screen(wm->display));

    switch (tiling_mode) {
        case Full:
            width = DISPLAY_WIDTH - WINDOW_BORDER_WIDTH * 2;
            height = DISPLAY_HEIGHT - WINDOW_BORDER_WIDTH * 2;
            break;
        case LeftHalf:
            width = DISPLAY_WIDTH / 2 - WINDOW_BORDER_WIDTH * 2;
            height = DISPLAY_HEIGHT - WINDOW_BORDER_WIDTH * 2;
            break;
        case RightHalf:
            x = DISPLAY_WIDTH / 2;
            width = DISPLAY_WIDTH / 2 - WINDOW_BORDER_WIDTH * 2;
            height = DISPLAY_HEIGHT - WINDOW_BORDER_WIDTH * 2;
            break;
        case BottomHalf:
            y = DISPLAY_HEIGHT / 2;
            width = DISPLAY_WIDTH - WINDOW_BORDER_WIDTH * 2;
            height = DISPLAY_HEIGHT / 2 - WINDOW_BORDER_WIDTH * 2;
            break;
        default:
            break;
    }

    xmove_resize_window(
        wm->display,
        self->window,
        x,
        y,
        width,
        height
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
