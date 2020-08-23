## Example builder and uploader

This project can be used to try out any of the self-contained examples in the
`examples/` parent folder of this project.

If you enter `pio run` on the command line, it will compile all the examples,
with output ending in something like this:

```text
[...]
================================== [SUMMARY] ===================================
Environment adc     	[SUCCESS]
Environment blink   	[SUCCESS]
[...]
Environment spiflash	[SUCCESS]
Environment systick 	[SUCCESS]
======================== [SUCCESS] Took 25.72 seconds ==========================
```

To build a single example, specify its environment name as follows:

```text
pio run -e blink
```

To upload, adjust the settings in the `[common]` section at the top of
`platformio.ini` to match your setup and ports:

```text
[common]
upload_protocol = blackmagic
upload_port = /dev/cu.usbmodemC2D77DD1
```

Then start the build and upload as follows:

```text
pio run -t upload -e blink
```

JeeH can also be used from the GUI version of PlatformIO, i.e. Atom or VSCode.
