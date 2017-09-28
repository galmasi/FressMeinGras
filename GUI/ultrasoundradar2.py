#!/usr/bin/env python

import Tkinter
import serial
import math

def redraw_canvas (ser, w, taglist):
    # canvas dimensions
    global canvas_height
    global canvas_width

    # the canvas radius of the circle on which we plot (pixels)
    global canvas_radius

    l = ser.readline()
    values=l.split()

    for i in range(0,5):

        # center point
        centerx=canvas_width/2
        centery=canvas_height/2

        # local angle in radians
        angle = (i-2)*math.pi/5 + float(values[0])*math.pi/180.0

        # direction vector endpoint
        
        dirx = centerx + canvas_radius * math.cos(angle)
        diry = centery + canvas_radius * math.sin(angle)

        # local distance in units relative to radius
        distance = float(values[i+1])/400.0 * canvas_radius
        
        # distance endpoint
        distx = centerx + distance * math.cos(angle)
        disty = centerx + distance * math.sin(angle)

        # adjust tags 
        w.coords(taglist[i],centerx,centery,dirx,diry)
        w.coords(taglist[i+5],distx-5,disty-5,distx+5,disty+5)
        
    w.update()
    w.update_idletasks()
    w.after(100, redraw_canvas, ser, w, taglist)


# open serial connection
ser = serial.Serial('/dev/ttyUSB0')

# create the canvas
root = Tkinter.Tk()
canvas_width=400
canvas_height=400
canvas_radius=200

w = Tkinter.Canvas(root, width=canvas_width, height=canvas_height, bg='gray')
w.pack(fill=Tkinter.BOTH)

# create canvas objects with dummy coordinates
taglist=[]
centerx=canvas_width/2
centery=canvas_height/2    

for i in range(0,5):
    taglist.append(w.create_line(centerx,centery,centerx+1,centery+1))

for i in range(0,5):
    taglist.append(w.create_oval(centerx,centery,centerx+1,centery+1,fill='red'))

w.after_idle(redraw_canvas, ser, w, taglist)


    
Tkinter.mainloop()
