// This file is part of "mira"
// Under the MIT License
// Copyright (c) 2022 Antonin Hérault

#ifndef MIRA_CLIENT
#define MIRA_CLIENT

#include "x11.h"

#define WINDOW_BORDER_WIDTH 2
#define WINDOW_BORDER_FOCUSED   0x610e68
#define WINDOW_BORDER_UNFOCUSED 0x2C0730

typedef struct client   Client;
struct client {
    Client* next_client;
    Client* previous_client;

    Window window;
};

Client new_client(XWindow window);
void free_client(Client* self);

#endif // MIRA_CLIENT