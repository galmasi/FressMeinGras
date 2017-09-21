#!/usr/bin/env python

import Tkinter
import serial
import math

cos_list=[]
sine_list=[]

for i in range(-2,3):
    cos_list.append(math.cos(math.pi*i/5))
    sine_list.append(math.sin(math.pi*i/5))
    
print cos_list         


def redraw_canvas (ser, w, taglist):
    global canvas_height
    global radius
    l = ser.readline()
    values=l.split()

    for i in range(0,5):
        dist=float(values[i])*radius/400.0
        x0=dist*cos_list[i]-5
        y0=canvas_height/2-dist*sine_list[i]-5
        x1=dist*cos_list[i]+5
        y1=canvas_height/2-dist*sine_list[i]+5
        w.coords(taglist[i],x0,y0,x1,y1)
    
    w.update()
    w.update_idletasks()
    w.after(100, redraw_canvas, ser, w, taglist)


# open serial connection
ser = serial.Serial('/dev/ttyUSB0')

# create the canvas
root = Tkinter.Tk()
canvas_width=400
canvas_height=400
radius=200
w = Tkinter.Canvas(root, width=canvas_width, height=canvas_height, bg='gray')
w.pack(fill=Tkinter.BOTH)


taglist=[]
for i in range(0,5):
    x0=0
    y0=canvas_height/2
    x1=x0+radius*cos_list[i]
    y1=y0+radius*sine_list[i]
    taglist.append(w.create_line(x0,y0,x1,y1))

taglist=[]
for i in range(0,5):
    x0=radius*cos_list[i]-5
    y0=canvas_height/2+radius*sine_list[i]-5
    x1=radius*cos_list[i]+5
    y1=canvas_height/2+radius*sine_list[i]+5
    tag=w.create_oval(x0,y0,x1,y1,fill='red')
    taglist.append(tag)
#    print w.coords(tag)

w.after_idle(redraw_canvas, ser, w, taglist)


    
Tkinter.mainloop()
