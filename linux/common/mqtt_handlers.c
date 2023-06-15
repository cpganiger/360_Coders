#include "mqtt_handlers.h"
#include "packetiser.h"

MQTTClient_deliveryToken deliveredtoken;
MQTTClient client;
MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
MQTTClient_message pubmsg = MQTTClient_message_initializer;
MQTTClient_deliveryToken token;
int rc;

packet_t rx_packet;
packet_t tx_packet;

void delivered(void *context, MQTTClient_deliveryToken dt)
{
    printf("Message with token value %d delivery confirmed\n", dt);
    deliveredtoken = dt;
}

int msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message)
{
    printf("Message arrived\n");
    printf("     topic: %s\n", topicName);
    printf("   message: %.*s\n", message->payloadlen, (char *)message->payload);

    memcpy((uint8_t *)&rx_packet, message->payload, message->payloadlen);
    printf("RecievedPacket: \n");
    display_packet(&rx_packet);

    // process_packet(&rx_packet);
    status_t crc_status = verify_crc(&tx_packet);

    printf("Verify status: %s\n", (crc_status) ? "Not Matching" : "Matching");

    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);
    return 1;
}

void connlost(void *context, char *cause)
{
    printf("\nConnection lost\n");
    printf("     cause: %s\n", cause);
}

void exit_app()
{
destroy_exit:
    MQTTClient_destroy(&client);
}

void init_mqtt()
{
    if ((rc = MQTTClient_create(&client, ADDRESS, CLIENTID,
                                MQTTCLIENT_PERSISTENCE_NONE, NULL)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to create client, return code %d\n", rc);
        rc = EXIT_FAILURE;
        //goto exit;
        exit_app();
    }
    printf("Created Client\n");
    if ((rc = MQTTClient_setCallbacks(client, NULL, connlost, msgarrvd, delivered)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to set callbacks, return code %d\n", rc);
        rc = EXIT_FAILURE;
        //goto destroy_exit;
        exit_app();
    }
    printf("Callbakcsare set\n");

    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;
    if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to connect, return code %d\n", rc);
        rc = EXIT_FAILURE;
        exit_app();
        //goto destroy_exit;
    }
    printf("Connected to MQTT Broker\n");
}

status_t subscribe_to_topic(char* topic_to_subsrcibe)
{
    if ((rc = MQTTClient_subscribe(client, TOPIC_PACKET, QOS)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to subscribe, return code %d\n", rc);
        rc = EXIT_FAILURE;
        return ERROR;
    }
}

int user_app()
{

    printf("Subscribing to topic %s\nfor client %s using QoS%d\n", TOPIC_PACKET,
           CLIENTID,
           QOS);

    if ((rc = MQTTClient_subscribe(client, TOPIC_PACKET, QOS)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to subscribe, return code %d\n", rc);
        rc = EXIT_FAILURE;
    }

    while (1)
    {
        pubmsg.qos = QOS;
        pubmsg.retained = 0;
        deliveredtoken = 0;
        memset((uint8_t *)&tx_packet, '\0', MAX_PACKET_LENGTH);

        tx_packet.headers.type = 0xAA;
        tx_packet.headers.id = 0x55;
        tx_packet.headers.timestamp = time(NULL);
        // printf("packet_header.timestamp = %ld, size = %d\n", tx_packet.headers.timestamp, sizeof(tx_packet.headers.timestamp));

        uint8_t input_data[4] = {0xDE, 0xAD, 0XBE, 0XEF};
        tx_packet.headers.data_length = 4;

        pubmsg.payload = &tx_packet;
        pubmsg.payloadlen = MAX_PACKET_LENGTH;

        printf("App main,Headers %x,  %x, %d, %ld\n", tx_packet.headers.id,
               tx_packet.headers.type,
               tx_packet.headers.data_length,
               tx_packet.headers.timestamp);

        packetiser(&tx_packet, input_data, 4);

        display_packet(&tx_packet);
#if 1
        if ((rc = MQTTClient_publishMessage(client, TOPIC_PACKET, &pubmsg, &token)) != MQTTCLIENT_SUCCESS)
        {
            printf("Failed to publish message, return code %d\n", rc);
            rc = EXIT_FAILURE;
        }
        else
        {
            printf("Waiting for publication of %s\n"
                   "on topic %s for client with ClientID: %s\n",
                   (char *)pubmsg.payload, TOPIC, CLIENTID);
            while (deliveredtoken != token)
            {
#if defined(_WIN32)
                Sleep(100);
#else

                sleep(10);
#endif
            }
        }
#endif
    }
    if ((rc = MQTTClient_disconnect(client, 10000)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to disconnect, return code %d\n", rc);
        rc = EXIT_FAILURE;
    }
    exit_app();
exit:
    return rc;
}



