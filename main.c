/*
 * main.c
 *
 * Created: 2012-01-10 17:44:56
 *  Author: kodie
 */ 

#include "local_config.h"

#if APP == SENDER_APP
#include "sender.c"
#else
#include "receiver.c"
#endif