// This file is part of "mira"
// Under the MIT License
// Copyright (c) 2022 Antonin Hérault

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#include "x11.h"

#include "wm/client.h"
#include "wm/handler.h"
#include "wm/wm.h"

WM new_wm(void) {
    Display* display = xopen_display(NULL);

    WM wm = { display };
    return wm;
}

void free_wm(WM* self) {
    xclose_display(self->display);
    self = (WM*) NULL;
}

void run_wm(WM* self) {
    init_handler(self);
    
    while (true) {
        update_handler(self);
        handle(self);
    }
}

void add_window(WM* self, XWindow window) {
    // Thanks https://github.com/pyknite/catwm/blob/master/catwm.c#L143

    Client* client = (Client*) malloc(sizeof(Client));
    client->window = window;

    if (self->head_client == (Client*) NULL) {
        client->next_client = (Client*) NULL;
        client->previous_client = (Client*) NULL;
        self->head_client = client;
        
        self->current_client = client;
        return;
    }

    Client* t = self->head_client; 
    for (; t->next_client; t = t->next_client);

    client->next_client = (Client*) NULL;
    client->previous_client = t;
    
    t->next_client = client;
    self->current_client = client;
}

void remove_window(WM* self, XWindow window) {
    Client* client = self->head_client;
    
    // CHANGE THIS UGLY CODE
    for (; client ; client = client->next_client) {
        if (client->window != window) {
            continue;
        }

        // Previous and next clients are null
        if (
            client->previous_client == NULL 
            && client->next_client == NULL
        ) {
            free_client(self->head_client);
            self->current_client = NULL;
            break;
        }

        // Previous client is null
        if (client->previous_client == NULL) {
            self->head_client = client->next_client;
            client->next_client->previous_client = NULL;
            self->current_client = client->next_client;
            
            free_client(client);
            break;
        } 
    
        // Next client
        if (client->next_client == NULL) {
            client->previous_client->next_client = NULL;
            self->current_client = client->previous_client;
            
            free_client(client);
            break;
        }

        // Nothing is null
        client->previous_client->next_client = client->next_client;
        client->next_client->previous_client = client->previous_client;
        self->current_client = client->previous_client;

        free_client(client);
        break;
    }
}

void tile_current_window(WM* self) {
    if (self->head_client == NULL) {
        return;
    }

    Client* client = self->head_client;
    for (; client; client = client->next_client) {
        if (self->current_client == client) {
            xmove_resize_window(
                self->display,
                client->window,
                0,
                0,
                xdisplay_width(self->display, xdefault_screen(self->display)) 
                    - WINDOW_BORDER_WIDTH * 2,
                xdisplay_height(self->display, xdefault_screen(self->display)) 
                    - WINDOW_BORDER_WIDTH * 2
            );
            return;
        }
    }
}

void update_current_client(WM* self) {
    Client* client = self->head_client;

    for (; client; client = client->next_client) {        
        xset_window_border_width(
            self->display, 
            client->window, 
            WINDOW_BORDER_WIDTH
        );

        // Client is not the current client, sets it unfocused
        xset_window_border(
            self->display,
            client->window,
            WINDOW_BORDER_UNFOCUSED
        );

        // Defines the properties for the current client
        if (self->current_client == client) {
            xset_window_border(
                self->display, 
                client->window, 
                WINDOW_BORDER_FOCUSED
            );

            xset_input_focus(
                self->display, 
                client->window, 
                RevertToParent, 
                CurrentTime
            );

            xraise_window(self->display, client->window);
            
            continue;
        }
    }
}
