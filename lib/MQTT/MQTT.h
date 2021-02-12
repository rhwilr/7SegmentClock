#pragma once
#include "State.h"

void initMQTT(State *SegmentClock, const char * server, uint16_t port, const char *id, const char *user, const char *pass);

void loopMQTT();