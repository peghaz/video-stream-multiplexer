#include <multi_stream.h>

int main(int argc, char *argv[])
{
    char *config_path;

    if (argc == 2)
        config_path = argv[1];
    else
        config_path = "config/streams.json";

    StreamConfigList *config_list = parse_stream_configs_from_json(config_path);
    initialize_multiple_streams(config_list);
    return 0;
}