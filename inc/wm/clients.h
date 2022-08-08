// This file is part of "mirade"
// Under the MIT License
// Copyright (c) 2022 Antonin Hérault

#ifndef MIRADE_WM_CLIENTS
#define MIRADE_WM_CLIENTS

#define MAX_CLIENTS 1024

#include <X11/Xlib.h>

/**
 * @brief Easy windows manager, created to replace the 
 * `unordered_map<Window, Window>` type of C++.
 * 
 * @note Clients are window objects 
*/
struct clients_map {
    Window* clients;
    size_t length;
};

typedef struct clients_map* ClientsMap;

/**
 * @brief Creates a new `ClientsMap` object with clients array initialized
 * @returns An instance of `ClientsMap`
*/
ClientsMap new_clients_map(void);

/**
 * @brief Frees `clients_map` by freeing the clients array. 
 * Resets the length.
*/
void free_clients_map(ClientsMap clients_map);

/**
 * @brief Adds a client to `clients_map`. Increases the length by 1.
 * @todo Optimizes to use `NULL` spaces in `[0..length]`
*/
void add_client_to_map(ClientsMap clients_map, Window to_add);

/**
 * @brief Retrieves a stored client thanks to a same structure of this client
 * @details Walks through the clients until the exact same object has been found
 * @returns A pointer to founded window or `NULL` when not found 
*/
Window* get_client_from_map(ClientsMap clients_map, Window requested_client);

Window* get_client_by_index_from_map(ClientsMap clients_map, size_t i);
size_t get_client_index_from_map(ClientsMap clients_map, Window requested_client);

/**
 * @brief Erases a client from the map thanks to a same structure of this client
 * @details Walks through the clients until the exact same object has been found,
 * then set it as `NULL`.
 * The length is not decreased !
*/
void erase_client_from_map(ClientsMap clients_map, Window client_to_erase);

#endif // MIRADE_WM_CLIENTS
