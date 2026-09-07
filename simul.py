from PIL import Image , ImageDraw , ImageFont
import os

width , height = 648 , 480
image = Image.new('1', (width, height), 255)
draw  = ImageDraw.Draw(image)

font = ImageFont.truetype("arial.ttf", 20)


with open("data.txt","r") as file:
    text_to_display = file.read().strip()

draw.text((50,15), text_to_display , fill= 0 , font = font )

output_path = "preview.png"
image.save(output_path)
os.startfile(output_path)