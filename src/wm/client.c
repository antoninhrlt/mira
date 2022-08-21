// This file is part of "mira"
// Under the MIT License
// Copyright (c) 2022 Antonin Hérault

#include "x11.h"

#include "wm/client.h"

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
