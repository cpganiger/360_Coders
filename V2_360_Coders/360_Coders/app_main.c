#include "app_main.h"

int user_app()
{
    send_test_packets();

    pause();
}

int main(int argc, char *argv[])
{

    init_mqtt();
    if(SUCCESS == listen_to_topic(MY_TOPIC_NAME))
    {
        printf("Listening to %s Topic", MY_TOPIC_NAME);
    }

    timed_activity_init();

    while (1)
    {
        user_app();
    }
    
    exit_app();
}
