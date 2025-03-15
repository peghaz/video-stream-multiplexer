#ifndef CONFIG_PARSE_H
#define CONFIG_PARSE_H
typedef struct
{
    char *video_path;
    int stream_port;
    int video_width;
    int video_height;
} StreamConfig;

typedef struct
{
    StreamConfig **configs;
    int num_configs;
} StreamConfigList;

StreamConfigList *parse_stream_configs_from_json(const char *filename);
StreamConfig *get_stream_config(StreamConfigList *config_list, int index);
char *print_stream_config(StreamConfig *config);
#endif