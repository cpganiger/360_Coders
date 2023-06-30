/**
 * @file mqtt_link.h
 * @author 360_Coders
 * @brief Functions for MQTT Communication 
 * @version 0.1
 * @date 2023-06-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef MQTT_LINK_H
#define MQTT_LINK_H

#include "MQTTClient.h"

#if !defined(_WIN32)
#include <unistd.h>
#else
#include <windows.h>
#endif

#define QOS 1
#define TIMEOUT 10000L

#define ADDRESS "tcp://broker.hivemq.com:1883"
#define CLIENTID "Linux_App"
#define TOPIC "360_coders"
#define TOPIC_PACKET "360_coders_packets"

class mqtt_link{
    char* address;
    char* device_id;
    MQTTClient_deliveryToken deliveredtoken;
    MQTTClient client;
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    MQTTClient_deliveryToken token;
    int rc;

public:

    mqtt_link();
    ~mqtt_link();

    topic_arrived();
    status_t listen_to_topic(char* topic_name);

};

#endif