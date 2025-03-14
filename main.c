#include <gst/gst.h>
#include <gst/rtsp-server/rtsp-server.h>
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        g_printerr("Usage: %s <video-file> <port>\n", argv[0]);
        return -1;
    }

    const char *input_file = argv[1];
    const char *port = argv[2];

    gst_init(&argc, &argv);
    // Initialize FFmpeg
    // av_register_all();

    // Verify FFmpeg can open the video
    AVFormatContext *fmt_ctx = NULL;
    if (avformat_open_input(&fmt_ctx, input_file, NULL, NULL) != 0)
    {
        g_printerr("Could not open input file with FFmpeg: %s\n", input_file);
        return -1;
    }
    avformat_close_input(&fmt_ctx);

    // Set up GStreamer RTSP server pipeline
    GstRTSPServer *server = gst_rtsp_server_new();
    gst_rtsp_server_set_service(server, port);
    GstRTSPMountPoints *mounts = gst_rtsp_server_get_mount_points(server);

    // Pipeline: filesrc (file input) → decode → encode → payload → RTSP
    gchar *pipeline_desc = g_strdup_printf(
        "( filesrc location=%s ! decodebin ! x264enc tune=zerolatency bitrate=500 speed-preset=ultrafast ! rtph264pay name=pay0 pt=96 )",
        input_file);

    GstRTSPMediaFactory *factory = gst_rtsp_media_factory_new();
    gst_rtsp_media_factory_set_launch(factory, pipeline_desc);
    gst_rtsp_media_factory_set_shared(factory, TRUE);

    // Attach media to RTSP path "/test"
    gst_rtsp_mount_points_add_factory(mounts, "/test", factory);
    g_object_unref(mounts);
    g_free(pipeline_desc);

    // Start RTSP server
    gst_rtsp_server_attach(server, NULL);
    g_print("RTSP stream ready at rtsp://127.0.0.1:%s/test\n", port);

    // Main loop
    GMainLoop *loop = g_main_loop_new(NULL, FALSE);
    g_main_loop_run(loop);

    return 0;
}
