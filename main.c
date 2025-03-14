#include <stdio.h>
#include <ffmpeg/libavutil/avutil.h>
#include <gst/gst.h>

void print_avutil_version()
{
    printf("FFmpeg avutil version: %s\n", av_version_info());
}

int main(int argc, char **argv)
{

    gst_init(&argc, &argv);

    const gchar *nano_str;
    guint major, minor, micro, nano;

    gst_version(&major, &minor, &micro, &nano);
    nano_str = (nano == 1) ? "(CVS)" : (nano == 2) ? "(Prerelease)"
                                                   : "";

    g_print("GStreamer version: %d.%d.%d %s\n", major, minor, micro, nano_str);
    print_avutil_version();
}