#include <gst/gst.h>
#include <gst/rtsp-server/rtsp-server.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <single_stream.h>

int initialize_single_stream(StreamConfig *config)
{
    int gst_argument_count = 1;

    char stream_port_str[10];
    sprintf(stream_port_str, "sid-%d", config->stream_port);

    char *identifier = (char *)malloc(strlen(stream_port_str));
    strcpy(identifier, stream_port_str);
    char **identifiers = (char **)malloc(sizeof(char *));
    identifiers[0] = identifier;

    gst_init(&gst_argument_count, &identifiers);

    // Verify FFmpeg can open the video
    AVFormatContext *fmt_ctx = NULL;
    if (avformat_open_input(&fmt_ctx, config->video_path, NULL, NULL) != 0)
    {
        g_printerr("Could not open input file with FFmpeg: %s\n", config->video_path);
        return -1;
    }
    avformat_close_input(&fmt_ctx);

    // Set up GStreamer RTSP server pipeline
    GstRTSPServer *server = gst_rtsp_server_new();
    gchar *service = g_strdup_printf("%d", config->stream_port);
    gst_rtsp_server_set_service(server, service);
    GstRTSPMountPoints *mounts = gst_rtsp_server_get_mount_points(server);

    // Pipeline: filesrc (file input) → decode → scale → encode → payload → RTSP
    gchar *g_width = g_strdup_printf("%d", config->video_width);
    gchar *g_height = g_strdup_printf("%d", config->video_height);

    gchar *pipeline_desc = g_strdup_printf(
        "( filesrc location=%s ! decodebin ! videoscale ! video/x-raw,width=%s,height=%s ! x264enc tune=zerolatency bitrate=4000 speed-preset=ultrafast ! "
        "rtph264pay name=pay0 pt=96 )",
        config->video_path, g_width, g_height);

    GstRTSPMediaFactory *factory = gst_rtsp_media_factory_new();
    gst_rtsp_media_factory_set_launch(factory, pipeline_desc);
    gst_rtsp_media_factory_set_shared(factory, TRUE);

    // Attach media to RTSP path "/test"
    gst_rtsp_mount_points_add_factory(mounts, "/stream", factory);
    g_object_unref(mounts);
    g_free(pipeline_desc);

    // Start RTSP server
    gst_rtsp_server_attach(server, NULL);
    g_print("RTSP stream ready at rtsp://127.0.0.1:%s/stream\n", service);

    // Main loop
    GMainLoop *loop = g_main_loop_new(NULL, FALSE);
    g_main_loop_run(loop);
    g_main_loop_quit(loop);

    g_free(g_width);
    g_free(g_height);

    return 0;
}