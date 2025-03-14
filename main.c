#include <stdio.h>
#include <ffmpeg/libavutil/avutil.h>

void print_avutil_version()
{
    printf("FFmpeg avutil version: %s\n", av_version_info());
}

int main(int, char **)
{
    print_avutil_version();
}