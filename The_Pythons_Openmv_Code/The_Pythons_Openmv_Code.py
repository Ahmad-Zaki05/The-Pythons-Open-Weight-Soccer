import sensor, image, time, math
from pyb import UART
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 2000)
sensor.set_auto_gain(False)
sensor.set_auto_whitebal(False)
sensor.set_vflip(True)
#orangeThreshold = [(53, 100, -13, 65, 34, 74), (49, 88, 27, 71, 17, 52)]#(36, 88, 29, 71, -6, 52)
orangeThreshold = [(36, 88, 29, 71, -6, 52)]#(49, 88, 27, 71, 17, 52)
uart = UART(3, 115200)
camcy = 127
camcx = 152
dribcx = 151
dribcy = 53
clock = time.clock()
while(True):
    clock.tick()
    img = sensor.snapshot()
    img.draw_circle(camcx, camcy, 50, color=(0,0,0), thickness=1, fill=True)
    img.draw_circle(camcx, camcy, 140, color=(0,0,0), thickness=55, fill=False)
    img.draw_circle(camcx, camcy, 190, color=(0,0,0), thickness=50, fill=False)#temporary
    img.draw_cross(dribcx, dribcy)
    orangeBlobs = img.find_blobs(orangeThreshold, pixels_threshold=17, area_threshold=17, merge=True)
    if orangeBlobs:
        ballBlob = max(orangeBlobs, key=lambda bL: bL.area())
        img.draw_edges(ballBlob.min_corners(), color=(255, 255, 255))
        dribAngle = (math.atan2((ballBlob.cy() - dribcy), (ballBlob.cx() - dribcx)) * 180 / math.pi) + 180
        cAngle = (math.atan2((ballBlob.cy() - camcy), (ballBlob.cx() - camcx)) * 180 / math.pi) + 180
        bRadius = (math.sqrt(((ballBlob.cy() - camcy) * (ballBlob.cy() - camcy)) + ((ballBlob.cx() - camcx) * (ballBlob.cx() - camcx))))
        print("bRadius: ", bRadius)

        if (cAngle >= 80 and cAngle <= 100):
            uart.write("B" + str(int(cAngle)) + "\n")
        elif(cAngle >= 0 and cAngle <= 90 and bRadius < 75):
            uart.write("B" + str(int(270 + cAngle)) + "\n")
        elif(cAngle >= 90 and cAngle <= 180 and bRadius < 75):
            uart.write("B" + str(int(90 + cAngle)) + "\n")
        elif(cAngle >= 180 and cAngle <= 270 and bRadius < 75):
            uart.write("B" + str(int(cAngle + 90)) + "\n")
        elif(cAngle >= 270 and cAngle <= 360 and bRadius < 75):
            uart.write("B" + str(int(cAngle - 90)) + "\n")
        elif(cAngle >= 225 and cAngle <= 270):
            uart.write("B" + str(int(cAngle+45)) + "\n")
        elif(cAngle >= 270 and cAngle <= 315):
            uart.write("B" + str(int(cAngle-45)) + "\n")
        else:
            uart.write("B" + str(int(dribAngle)) + "\n")
        print("dribAngle: ", dribAngle)
    else:
        uart.write("S\n")
