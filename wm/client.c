// This file is part of "mirade"
// Under the MIT License
// Copyright (c) 2022 Antonin Hérault

#include <stdlib.h>

#include "wm/client.h"

Client new_client(Window window, bool is_old) {    
    Client client = { window /* id */, window, is_old };
    return client;
}

void free_client(Client* client) {
    client->window = (Window) NULL;
}

Clients new_clients() {
    Client* array = malloc(sizeof(Client) * MAX_CLIENTS);
    Clients clients = { array, 0 };
    return clients;
}

void free_clients(Clients* clients) {
    free(clients->clients);
    clients->length = 0;
}

void add_client(Clients* clients, Client client) {
    clients->clients[clients->length] = client;
    ++clients->length;
}

Client* get_client_by_id(Clients clients, long id) {
    for (size_t i = 0; i < clients.length; ++i) {
        // Client found, returns an reference on it
        if (clients.clients[i].id == id) {
            return &clients.clients[i];
        }
    }

    return NULL;
}