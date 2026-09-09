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

# print("e ink pins config")

# while True:
#     with open("data.txt", "r") as file:
#         text_to_display = file.read().strip()
#         print("Read from file" , text_to_display)

#         y_pos = 50 
#         for line in text_to_display.split("\n"):
#             canvas.text(line , 50 , y_pos , 0)
#             y_pos += 30


width = 648
height = 480

while True:

    with open("data.txt","r") as file:
        text_to_display = file.read().strip()
        canvas.fill(1)

        canvas.rect(20,20,width-40,height-40,0)
        canvas.rect(21,21,width-42,height-42,0)

        heading = "DAILY DASHBOARD"

        heading_x = (width - (len(heading)*8))//2
        canvas.text(heading,heading_x,40,0)

        canvas.hline(40,70,width-80,0)

        y_pos = 100

        for line in text_to_display.split('\n'):
            line = line.strip()
            # canvas.text(line.strip(), 50 , y_pos, 0)
            # y_pos += 20

            if line.startswith('!'):
                actual_text = line[1:].strip()
                text_width = len(actual_text) * 8

                canvas.fill_rect(45,y_pos-2,text_width+10 , 12 ,0)
                canvas.text(actual_text,50,y_pos,1)
            else:
                canvas.text(line,50,y_pos,0)

            y_pos += 20


    time.sleep(5)