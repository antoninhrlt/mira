// This file is part of "mira"
// Under the MIT License
// Copyright (c) 2022 Antonin Hérault

#ifndef MIRA_CLIENT
#define MIRA_CLIENT

#include "x11.h"

typedef struct wm WM;

#define WINDOW_BORDER_WIDTH 2
#define WINDOW_BORDER_FOCUSED   0xe600ff
#define WINDOW_BORDER_UNFOCUSED 0xf6a2ff

typedef struct client   Client;
struct client {
    Client* next_client;
    Client* previous_client;

    Window window;
};

Client new_client(XWindow window);
void free_client(Client* self);

void set_client_defaults(Client* self, WM* wm);
void tile_client(Client* self, WM* wm);
void update_clients(WM* wm);
void kill_client(Client* self, WM* wm);

#endif // MIRA_CLIENT
