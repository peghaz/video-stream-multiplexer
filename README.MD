HOW TO: Use the executable `build/multiplex-streams` with a JSON config file in the form of `config/streams.json` to run the program.

1. Clone the repository
2. Run the commands:

```bash
$ mkdir build
$ cd build
$ cmake ..
$ cmake --build .
```

3. You can now run the executable as:

```bash
$ ./multiplex-streams ../config/streams.json
```

4. An example video stream configuration is:

```json
{
  "stream_port": 6666,
  "video_path": "data/2022-02-13.mp4",
  "video_width": 1280,
  "video_height": 720,
  "enable_audio": true
}
```

### Audio Streaming

Audio streaming is supported via the `enable_audio` option in the JSON config:

- **`"enable_audio": true`** — Streams both video and audio. The video file is demuxed using `qtdemux`, with video encoded via H.264 (`x264enc`) and audio encoded via Opus (`opusenc`). Both are payloaded over RTP for RTSP delivery.
- **`"enable_audio": false`** (or omitted) — Streams video only (default behavior).

> **Note:** Audio streaming requires the input file to be in a container format with an audio track (e.g., `.mp4` with AAC audio). Files without an audio track will fail if `enable_audio` is set to `true`.

Dependencies:
On Fedora/OpenSUSE/Rocky Linux/RedHat Enterprise Linux, you can install the dependencies with:

```bash
sudo dnf install cmake gcc gstreamer1-devel gstreamer1-plugins-base-devel gstreamer1-plugins-good-devel gstreamer1-plugins-bad-free-devel gstreamer1-plugins-ugly-devel gstreamer1-libav-devel gstreamer1-rtsp-devel gstreamer1-rtsp-server-devel ffmpeg ffmpeg-devel
```
