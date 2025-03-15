#include <parse_config.h>
#include <single_stream.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    StreamConfigList *config_list = parse_stream_configs_from_json("config/streams.json");
    StreamConfig *config_0 = get_stream_config(config_list, 0);
    print_stream_config(config_0);
    // const char *input_file = "data/2022-02-13.mp4";
    // int port = 2122;
    // int width = 600;
    // int height = 400;

    return 0;
    // return initialize_single_stream(input_file, port, height, width, argc, argv);
}
