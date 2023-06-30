#include "app_main.h"

static packet_t heart_beat_packet;

void heart_beat_sender(int signo)
{
    alarm(5);
    printf("Timer active\n");
    //test_packet_sender();
    test_packet1();

}

void timed_activity_init()
{
    alarm(5);
    signal(SIGALRM, heart_beat_sender);
}