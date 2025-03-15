#include <single_stream.h>

int initialize_single_stream(char *input_file, int port, int height, int width, int argc, char *argv[])
{
    gst_init(&argc, &argv);

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

    // Pipeline: filesrc (file input) → decode → scale → encode → payload → RTSP
    gchar *pipeline_desc = g_strdup_printf(
        "( filesrc location=%s ! decodebin ! videoscale ! video/x-raw,width=%s,height=%s ! x264enc tune=zerolatency bitrate=500 speed-preset=ultrafast ! "
        "rtph264pay name=pay0 pt=96 )",
        input_file, width, height);

    GstRTSPMediaFactory *factory = gst_rtsp_media_factory_new();
    gst_rtsp_media_factory_set_launch(factory, pipeline_desc);
    gst_rtsp_media_factory_set_shared(factory, TRUE);

    // Attach media to RTSP path "/test"
    gst_rtsp_mount_points_add_factory(mounts, "/", factory);
    g_object_unref(mounts);
    g_free(pipeline_desc);

    // Start RTSP server
    gst_rtsp_server_attach(server, NULL);
    g_print("RTSP stream ready at rtsp://127.0.0.1:%s/\n", port);

    // Main loop
    GMainLoop *loop = g_main_loop_new(NULL, FALSE);
    g_main_loop_run(loop);

    return 0;
}