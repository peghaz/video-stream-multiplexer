import json
import os
from pathlib import Path

INITIAL_PORT = 6666
NUM_STREAMS = 50
WORK_DIR = Path(".")

VIDEO_SOURCE = WORK_DIR / "data" / "2022-02-13.mp4"
CONFIG_FILE = WORK_DIR / "config" / "streams.json"

VIDEO_HEIGHT = 720
VIDEO_WIDTH = 1280

if __name__ == "__main__":
    config_file = open(str(CONFIG_FILE), "w")
    configs = []
    for i in range(NUM_STREAMS):
        config = {
            "stream_port": INITIAL_PORT + i,
            "video_path": str(VIDEO_SOURCE),
            "video_width": VIDEO_WIDTH,
            "video_height": VIDEO_HEIGHT
        }
        configs.append(config)

    # Write the config file
    json.dump(configs, config_file, indent=4)
    config_file.close()
