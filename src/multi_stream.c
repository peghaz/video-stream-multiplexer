#include "parse_config.h"
#include "single_stream.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *thread_stream(void *args)
{
    StreamConfig *config = (StreamConfig *)args;
    initialize_single_stream(config);
}

int initialize_multiple_streams(StreamConfigList *config_list)
{
    int num_streams = config_list->num_configs;
    num_streams = 1;

    pthread_t *stream_threads = (pthread_t *)malloc(num_streams * sizeof(pthread_t));

    for (int s = 0; s < num_streams; s++)
    {
        pthread_t thread_s;
        StreamConfig *config = get_stream_config(config_list, s);

        int status = pthread_create(&thread_s, NULL, thread_stream, (void *)config);
        if (status)
        {
            char *format = "Error creating stream [%d] for video %s, port %d, \n";
            fprintf(stderr, format, s, config->video_path, config->stream_port);
            return -1;
        }
        else
        {
            char *format = "Stream [%d] created for video %s, port %d, \n";
            fprintf(stdout, format, s, config->video_path, config->stream_port);
        }

        stream_threads[s] = thread_s;
    }

    for (int s = 0; s < num_streams; s++)
    {
        pthread_join(stream_threads[s], NULL);
    }
    return 0;
}