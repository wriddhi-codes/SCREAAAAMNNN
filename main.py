import time
import machine 
import gc
import framebuf


screen_buffer = bytearray(38880)
gc.collect()


print(" buffer locked and secured")


canvas = framebuf.FrameBuffer(screen_buffer, 648 , 480 , framebuf.MONO_HLSB)


spi = machine.SPI(1 , baudrate= 20000000 , polarity= 0 , phase = 0 , sck= machine.Pin(18) , mosi= machine.Pin(23))
cs = machine.Pin(5, machine.Pin.OUT)
dc = machine.Pin(17, machine.Pin.OUT)
rst = machine.Pin(16, machine.Pin.OUT)
busy = machine.Pin(4, machine.Pin.IN)

print("e ink pins config")

while True:
    with open("data.txt", "r") as file:
        text_to_display = file.read().strip()
        print("Read from file" , text_to_display)

        y_pos = 50 
        for line in text_to_display.split("\n"):
            canvas.text(line , 50 , y_pos , 0)
            y_pos += 30

        