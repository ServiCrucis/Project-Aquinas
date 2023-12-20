/*
 * Module: StateholdSource
 * File: StateholdSource.h
 * Created:
 * October 26, 2023
 * Author: Andrew Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
 * License: See LICENSE.txt
 */

#ifndef PROJECT_AQUINAS_STATEHOLDSOURCE_H
#define PROJECT_AQUINAS_STATEHOLDSOURCE_H

#include "platform.h"

typedef struct {
    void *(*draw)(machine_workeld stateholds_quantity, machine_workeld potential_states_quantity, machine_workeld *actual_states_quantity);
    void (*yield)(void *statehold);
} StateholdSource;

#endif //PROJECT_AQUINAS_STATEHOLDSOURCE_H
