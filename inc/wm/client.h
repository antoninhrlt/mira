// This file is part of "mirade"
// Under the MIT License
// Copyright (c) 2022 Antonin Hérault

#ifndef MIRADE_WM_CLIENT
#define MIRADE_WM_CLIENT

#include <stdbool.h>

#include <X11/Xlib.h>

#define MAX_CLIENTS 1024

#define WINDOW_BORDER_WIDTH 1
#define WINDOW_BORDER_COLOR 0xffffff
#define WINDOW_BG_COLOR 0xff0000

/**
 * A client is an easy way to manage an X window
*/
typedef struct client {
    long id;
    Window window;
    bool is_old; // if it was created before the wm run
} Client;

Client new_client(Window window, bool is_old);
void free_client(Client* client);

/**
 * Manager for the all clients
*/
typedef struct clients {
    Client* clients;
    size_t length;
} Clients;

Clients new_clients();
void free_clients(Clients* clients);
void add_client(Clients* clients, Client client);

/**
 * Retrieves a client from an array of `Client` by its identifier
 * @param id The client's id looking for
 * @returns A pointer on the client found / `NULL` when not found or when the 
 * client found is null 
*/
Client* get_client_by_id(Clients clients, long id);

#endif // MIRADE_WM_CLIENT
