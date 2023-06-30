/**
 * @file mqtt_handlers.h
 * @author 360_Coders
 * @brief Functions for MQTT Communication 
 * @version 0.1
 * @date 2023-06-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef MQTT_HANDLERS_H
#define MQTT_HANDLERS_H

#include "MQTTClient.h"

#if !defined(_WIN32)
#include <unistd.h>
#else
#include <windows.h>
#endif

#include "packetiser.h"
#define QOS 1
#define TIMEOUT 10000L

#define ADDRESS "tcp://broker.hivemq.com:1883"
#define CLIENTID "Linux_App"
#define TOPIC "360_coders"
#define TOPIC_PACKET "360_coders"

int user_app();
void init_mqtt();
void exit_app();

#endif