#include <single_stream.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    const char *input_file = "data/2022-02-13.mp4";
    int port = 2121;
    int width = 600;
    int height = 400;

    return initialize_single_stream(input_file, port, height, width, argc, argv);
}
