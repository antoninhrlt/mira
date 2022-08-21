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
    
    // Search through all the clients until the right one is found
    for (; client ; client = client->next_client) {
        if (client->window == window) {
            break;
        }
    }

    // Here, the goal is to select the new "current window" because we remove 
    // the current one

    // Previous and next clients are null
    if (
        client->previous_client == NULL 
        && client->next_client == NULL
    ) {
        free_client(self->head_client); // sets null
        self->current_client = NULL;
        return;
    }

    // Previous client is null
    if (client->previous_client == NULL) {
        self->head_client = client->next_client;
        client->next_client->previous_client = NULL;
        self->current_client = client->next_client;
    
    } else if (client->next_client == NULL) {
        client->previous_client->next_client = NULL;
        self->current_client = client->previous_client;
    
    } else {
        client->previous_client->next_client = client->next_client;
        client->next_client->previous_client = client->previous_client;
        self->current_client = client->previous_client;
    }

    free_client(client);
    update_clients(self); // to focus on the new current window
}

