/*
 * Module: m_context
 * File: m_context.h
 * Created:
 * June 12, 2022
 * Author: Andrew Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
 * License: See LICENSE.txt
 *
 *
 * An m_context construct. Models the BC memory model's memory contexts imperfectly using the C memory model.
 * #Imperfections
 * - restricted to the use of blackbox data types for the representation of the memory context
 * - cannot specify desired address at this time
 */

#ifndef PROJECT_AQUINAS_M_CONTEXT_H
#define PROJECT_AQUINAS_M_CONTEXT_H

#include "platform.h"

typedef void *m_context;

#endif //PROJECT_AQUINAS_M_CONTEXT_H
