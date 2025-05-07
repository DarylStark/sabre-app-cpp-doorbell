# Sabre - App - Doorbell

This is a doorbell application for a ESP32 microcontroller.

## Set up

To set up the project, make sure you have ESP IDF installed. You can use the dev container defined in this repository to set up the environment. The dev container includes all the necessary tools and libraries to build and flash the project to the ESP32.

First, set the build target to the correct module (ESP32, ESP32-S3, etc):

```bash
idf.py set-target esp32
```

Then, build the project:

```bash
idf.py build
```

To flash the project to the ESP32, connect the ESP32 to your computer and run:

```bash
idf.py -p /dev/ttyUSB0 flash
```

Replace `/dev/ttyUSB0` with the correct port for your ESP32.

To monitor the output of the ESP32, run:

```bash
idf.py -p /dev/ttyUSB0 monitor
```

Replace `/dev/ttyUSB0` with the correct port for your ESP32.
