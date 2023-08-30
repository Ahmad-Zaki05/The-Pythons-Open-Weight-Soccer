# Untitled - By: Zaki - Tue Aug 29 2023

import sensor, image, time, math
from pyb import UART

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 2000)
sensor.set_auto_gain(False)
sensor.set_auto_whitebal(False)
sensor.set_vflip(True)

orangeThreshold = [(27, 37, 12, 46, -1, 22), (23, 38, 10, 45, 3, 32)] # (44, 88, 13, 71, -9, 45), (29, 58, 37, 72, 12, 57), (23, 81, 30, 75, -1, 72),

uart = UART(3, 115200)

camcy = 109
camcx = 121

clock = time.clock()

while(True):
    clock.tick()
    img = sensor.snapshot()

    orangeBlobs = img.find_blobs(orangeThreshold, pixels_threshold=50, area_threshold=100, merge=True)

    if orangeBlobs:
        ballBlob = max(orangeBlobs, key=lambda bL: bL.area())
        img.draw_edges(ballBlob.min_corners(), color=(255, 0, 0))
#        ratio = (ballBlob.cy() - camcy) / (ballBlob.cx() - camcx)
#        print(ballBlob.cy() - camcy)
#        print(ballBlob.cx() - camcx)
#        print(ratio)
        print(math.atan2((ballBlob.cy() - camcy), (ballBlob.cx() - camcx)) * 180 / math.pi + 180)

#    print(clock.fps())
