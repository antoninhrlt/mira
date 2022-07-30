// This file is part of "mirade"
// Under the MIT License
// Copyright (c) 2022 Antonin Hérault

#include "wm/manager.h"

int main(void) {
    WM window_manager = new_wm();
    run_wm(&window_manager);
    free_wm(&window_manager);

    return 0;
}
