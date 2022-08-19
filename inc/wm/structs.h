// This file is part of "mira"
// Under the MIT License
// Copyright (c) 2022 Antonin Hérault

#ifndef MIRA_STRUCTS
#define MIRA_STRUCTS

#include "x11.h"

/// This file is used for two different structures but that need each other 
/// (A needs B and B needs A). With header files, it becomes very complicated to 
/// manipulate these files without troubles. Putting them into one another 
/// header is the easier way to do that.

typedef struct WM WM;

typedef struct {
    WM* wm;
    XEvent event;
} Handler;

struct WM {
    XDisplay* display;
    /// The current retrieved event in the displaying loop
    XWindowAttributes window_attrs;
    Handler handler;
};

#endif // MIRA_STRUCTS
