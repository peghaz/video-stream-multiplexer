#include <cJSON.h>
#include <parse_config.h>
#include <stdio.h>
#include <stdlib.h>

StreamConfig *get_stream_config(StreamConfigList *config_list, int index)
{
    return config_list->configs[index];
}

char *print_stream_config(StreamConfig *config)
{
    char *config_str = (char *)malloc(100 * sizeof(char));
    if (config_str == NULL)
    {
        perror("Failed to allocate memory for StreamConfig string!");
        return NULL;
    }

    char *format = "{\n\tVideo Path: %s,\n\tStream Port: %d,\n\tVideo Width: %d,\n\tVideo Height: %d\n}";
    sprintf(config_str, format, config->video_path, config->stream_port, config->video_width, config->video_height);
    fprintf(stdout, "%s\n", config_str);
    return config_str;
}

StreamConfig *StreamConfig__new(char *video_path, int stream_port, int video_width, int video_height)
{
    StreamConfig *config = (StreamConfig *)malloc(sizeof(StreamConfig));
    if (config == NULL)
    {
        perror("Failed to allocate memory for StreamConfig!");
        return NULL;
    }

    config->video_path = video_path;
    config->stream_port = stream_port;
    config->video_width = video_width;
    config->video_height = video_height;

    return config;
}

char *read_json_file_to_string(const char *filename);

StreamConfigList *parse_stream_configs_from_json(const char *filename)
{
    char *json_data = read_json_file_to_string(filename);

    if (json_data == NULL)
    {
        printf("Parsing Error: Failed to read JSON data from file: %s\n", filename);
        return NULL;
    }

    cJSON *json_array = cJSON_Parse(json_data);

    if (!cJSON_IsArray(json_array))
    {
        printf("Parsing Error: JSON data is not an array!\n");
        cJSON_Delete(json_array);
        return NULL;
    }

    StreamConfigList *config_list = (StreamConfigList *)malloc(sizeof(StreamConfigList));
    config_list->num_configs = cJSON_GetArraySize(json_array);

    StreamConfig **stream_configs = (StreamConfig **)malloc(config_list->num_configs * sizeof(StreamConfig *));
    int current_config_index = 0;
    cJSON *item;
    cJSON_ArrayForEach(item, json_array)
    {
        cJSON *video_path = cJSON_GetObjectItem(item, "video_path");
        cJSON *stream_port = cJSON_GetObjectItem(item, "stream_port");
        cJSON *video_width = cJSON_GetObjectItem(item, "video_width");
        cJSON *video_height = cJSON_GetObjectItem(item, "video_height");

        StreamConfig *config = StreamConfig__new(video_path->valuestring, stream_port->valueint, video_width->valueint, video_height->valueint);

        stream_configs[current_config_index] = config;
        current_config_index++;
    }

    config_list->configs = stream_configs;
    return config_list;
}

char *read_json_file_to_string(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Failed to open the provided JSON config file!");
        return NULL;
    }

    // Get file length
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    rewind(file);

    // Allocate memory
    char *data_str = (char *)malloc(length + 1);
    if (data_str == NULL)
    {
        perror("Failed to allocate memory for the JSON config file!");
        fclose(file);
        return NULL;
    }

    // Read file content
    fread(data_str, 1, length, file);
    data_str[length] = '\0'; // Null-terminate the string

    fclose(file);
    return data_str;
}