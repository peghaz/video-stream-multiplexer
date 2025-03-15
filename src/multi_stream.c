#include "parse_config.h"
#include <pthread.h>
#include <stdio.h>
int initialize_multiple_streams(StreamConfigList *config_list)
{
    int num_streams = config_list->num_configs;
    for (int s = 0; s < num_streams; s++)
    {
        pthread_t thread_s;
        print_stream_config(get_stream_config(config_list, s));
    }
    return 0;
}