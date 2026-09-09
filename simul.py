from PIL import Image , ImageDraw , ImageFont
import os

width , height = 648 , 480
image = Image.new('RGB', (width, height), (255,255,255))
draw  = ImageDraw.Draw(image)

ttile_font = ImageFont.truetype("arial.ttf", 36)
body_font = ImageFont.truetype("arial.ttf",24)

draw.rectangle([20,20,width-20,height-20],outline=0, width=3)

heading = "DAILY DASHBOARD"

box = draw.textbbox((0,0),heading,font=ttile_font)
text_width = box[2] -box[0]
heading_x = (width - text_width) // 2

draw.text((heading_x , 40), heading,fill="BLACK", font=ttile_font)

draw.line([40,95,width-40,95],fill=0,width=2)

with open("data.txt","r") as file:
    text_to_display = file.read().strip()

y_pos = 125
for line in text_to_display.split('\n'):
    line = line.strip()
    if line.startswith('!'):
        actual_text = line[1:].strip()

        #tb = draw.textbbox((0,0), actual_text , font=body_font)
        # draw.text((50,y_pos), line , fill= 0 , font = body_font )

        #tw = tb[2]-tb[0]
        #th = tb[3]-tb[1]

        #draw.rectangle([45,y_pos-2, 55+tw+10,y_pos+th+6],fill='RED')
        draw.text((50,y_pos), actual_text, fill="RED", font=body_font)

    else:
        draw.text((50 ,y_pos),line, fill= "BLACK", font=body_font)

    y_pos += 35
output_path = "preview.png"
image.save(output_path)
os.startfile(output_path)