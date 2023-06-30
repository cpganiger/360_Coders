#include "app_main.h"

void test_devices_in_network()
{

}

int user_app()
{
    //send_heart_beat(); time interval
    pause();
    handle_requests();
}

int main(int argc, char *argv[])
{
#if ENABLE_MQTT
    init_mqtt();
    if(SUCCESS == listen_to_topic(MY_TOPIC_NAME))
    {
        printf("Listening to %s Topic", MY_TOPIC_NAME);
    }
#endif
    timed_activity_init();

    while (1)
    {
        user_app();
    }
    
    exit_app();
}
