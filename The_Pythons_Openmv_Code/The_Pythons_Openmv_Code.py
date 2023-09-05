import sensor, image, time, math
from pyb import UART
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 2000)
sensor.set_auto_gain(False)
sensor.set_auto_whitebal(False)
sensor.set_vflip(True)
orangeThreshold = [(20, 72, 37, 78, 26, 63), (29, 60, 12, 60, 23, 43)]
uart = UART(3, 115200)
camcy = 113
camcx = 119
clock = time.clock()
while(True):
    clock.tick()
    img = sensor.snapshot()
    orangeBlobs = img.find_blobs(orangeThreshold, pixels_threshold=20, area_threshold=20, merge=True)
    if orangeBlobs:
        ballBlob = max(orangeBlobs, key=lambda bL: bL.area())
        img.draw_edges(ballBlob.min_corners(), color=(255, 255, 255))
        angle = (math.atan2((ballBlob.cy() - camcy), (ballBlob.cx() - camcx)) * 180 / math.pi) + 180
        uart.write(str(int(angle)) + "\n")
        print(angle)
    else:
        uart.write("S\n")
