// This file is part of "mira"
// Under the MIT License
// Copyright (c) 2022 Antonin Hérault

#include "x11.h"
#include "wm/wm.h"

int main(void) {
    WM mira_wm = new_wm();
    run_wm(&mira_wm);
    free_wm(&mira_wm);

    return 0;
}

//      </¯¯\>
//  /¯¯¯¯\__/ 
// /\______/  
//  ||   ||  A
