#include "app_main.h"

int main(int argc, char *argv[])
{
    init_mqtt();
    
    while (1)
    {
        user_app();
    }
    
    exit_app();
}
