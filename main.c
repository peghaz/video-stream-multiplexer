#include <multi_stream.h>

int main(int argc, char *argv[])
{
    StreamConfigList *config_list = parse_stream_configs_from_json("config/streams.json");
    initialize_multiple_streams(config_list);
    return 0;
}
