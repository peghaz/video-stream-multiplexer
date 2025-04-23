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
  "video_height": 720
}
```

Dependencies:
On Fedora/OpenSUSE/Rocky Linux/RedHat Enterprise Linux, you can install the dependencies with:

```bash
sudo dnf install cmake gcc gstreamer1-devel gstreamer1-plugins-base-devel gstreamer1-plugins-good-devel gstreamer1-plugins-bad-free-devel gstreamer1-plugins-ugly-devel gstreamer1-libav-devel gstreamer1-rtsp-devel gstreamer1-rtsp-server-devel ffmpeg ffmpeg-devel
```
