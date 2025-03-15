#include <single_stream.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 5)
    {
        printf("Usage: %s <video-file> <port> <width> <height>\n", argv[0]);
        return -1;
    }

    const char *input_file = argv[1];
    const char *port = argv[2];
    const char *width = argv[3];
    const char *height = argv[4];

    return initialize_single_stream(input_file, atoi(port), atoi(height), atoi(width), argc, argv);
}
