// This file is part of "mirade"
// Under the MIT License
// Copyright (c) 2022 Antonin Hérault

#include <stdlib.h>
#include <assert.h>

#include "wm/clients.h"

ClientsMap new_clients_map(void) {
    Window* clients = malloc(sizeof(Window) * MAX_CLIENTS);
    
    ClientsMap clients_map = { clients, 0 };
    return clients_map;
}

void free_clients_map(ClientsMap clients_map) {
    free(clients_map.clients);
    clients_map.length = 0;
}

void add_client_to_map(ClientsMap clients_map, Window to_add) {
    assert(clients_map.length != MAX_CLIENTS -1);
    ++clients_map.length;
    clients_map.clients[clients_map.length] = to_add; 
}

Window* get_client_from_map(ClientsMap clients_map, Window requested_client) {
    assert(requested_client != (Window) NULL);

    size_t i = get_client_index_from_map(clients_map, requested_client);
    if (i == ERR_INDEX_CLIENT) {
        return NULL;
    }
    
    return &clients_map.clients[i];
}

Window* get_client_by_index_from_map(ClientsMap clients_map, size_t i) {
    assert(i != ERR_INDEX_CLIENT && i < clients_map.length);
    return &clients_map.clients[i];
}

size_t get_client_index_from_map(ClientsMap clients_map, Window requested_client) {
    size_t i = 0;
    for (; i < clients_map.length; ++i) {
        if (clients_map.clients[i] == requested_client) {
            return i;
        }
    }

    return ERR_INDEX_CLIENT;
}

void erase_client_from_map(ClientsMap clients_map, Window client_to_erase) {
    assert(client_to_erase != (Window) NULL);

    for (size_t i = 0; i < clients_map.length; ++i) {
        if (clients_map.clients[i] == client_to_erase) {
            clients_map.clients[1] = (Window) NULL;
            break;
        }
    }
}
