/**
 * @file app_main.h
 * @author your name (you@domain.com)
 * @brief Application entry point
 * @version 0.1
 * @date 2023-06-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef APP_MAIN_H
#define APP_MAIN_H

#include "packetiser.h"
#include "mqtt_handlers.h"

#include "unistd.h"
#include "signal.h"

#define ADDRESS "tcp://broker.hivemq.com:1883"
#define CLIENTID "Linux_App"
#define TOPIC "360_coders"
#define MY_TOPIC_NAME "360_coders"

void timed_activity_init();


#endif