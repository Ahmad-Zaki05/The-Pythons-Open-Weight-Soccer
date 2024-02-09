import sensor, image, time, math, pyb
from pyb import UART
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 2000)
sensor.set_auto_gain(False)
sensor.set_auto_whitebal(False)
sensor.set_vflip(True)
orangeThreshold = [(45, 70, 27, 90, 1, 63), (35, 71, 14, 76, 55, 71)] # bellel , (51, 74, 18, 81, 2, 62),
yellowThreshold = [(32, 39, 9, 32, 16, 32), (29, 36, -4, 32, 16, 32)] # bellel
#orangeThreshold = [(59, 80, 15, 64, 20, 41) , (64, 80, 23, 61, -33, 10)] # elsob7
#yellowThreshold = [(36, 44, 8, 34, 21, 50), (32, 38, 10, 42, 18, 55)] # elsob7
uart = UART(3, 115200)
camcx = 175
camcy = 114
dribcx = 176
dribcy = 62
flagBall = 0
lastAngle = 0
lastRadius = 0
backflag = 0
frontflag = 0
clock = time.clock()
timer = pyb.millis()
while(True):
    clock.tick()
    img = sensor.snapshot()
    img.draw_circle(camcx, camcy, 53, color=(0,0,0), thickness=1, fill=True)
    img.draw_circle(camcx, camcy, 155, color=(0,0,0), thickness=55, fill=False)
    img.draw_circle(camcx, camcy, 185, color=(0,0,0), thickness=50, fill=False)
    img.draw_cross(dribcx, dribcy)
    orangeBlobs = img.find_blobs(orangeThreshold, pixels_threshold=5, area_threshold=5, merge=True)

    uart.write('D')
    if pyb.millis() - timer > 5000:
        yellowBlobs = img.find_blobs(yellowThreshold, pixels_threshold=20, area_threshold=20, merge=True)
        if yellowBlobs:
            goalBlob = max(yellowBlobs, key=lambda bL: bL.area())
            img.draw_edges(goalBlob.min_corners(), color=(0, 255, 255))
            goalAngle = (math.atan2((goalBlob.cy() - camcy), (goalBlob.cx() - camcx)) * 180 / math.pi) + 180
            goalRadius = (math.sqrt(((goalBlob.cy() - camcy) * (goalBlob.cy() - camcy)) + ((goalBlob.cx() - camcx) * (goalBlob.cx() - camcx))) * math.sin(goalAngle * math.pi / 180) * -1)
            print("goalRadius: ", goalRadius)
            if goalRadius > 95:
                backflag = 1 #b
                print('b')
            elif goalRadius < 85:
                frontflag = 1 #f
                print('f')
            else:
                uart.write('s')
                print('s')
            timer = pyb.millis()

#    else:
#        uart.write('s')
    if backflag == 1 or frontflag == 1:
        if backflag == 1:
            uart.write('b')
        else:
            uart.write('f')
        yellowBlobs = img.find_blobs(yellowThreshold, pixels_threshold=20, area_threshold=20, merge=True)
        if yellowBlobs:
            goalBlob = max(yellowBlobs, key=lambda bL: bL.area())
            img.draw_edges(goalBlob.min_corners(), color=(0, 255, 255))
            goalAngle = (math.atan2((goalBlob.cy() - camcy), (goalBlob.cx() - camcx)) * 180 / math.pi) + 180
            goalRadius = (math.sqrt(((goalBlob.cy() - camcy) * (goalBlob.cy() - camcy)) + ((goalBlob.cx() - camcx) * (goalBlob.cx() - camcx))) * math.sin(goalAngle * math.pi / 180) * -1)
            if goalRadius < 95:
                backflag = 0
            if goalRadius > 85:
                frontflag = 0
    else:
        uart.write('s')
    if orangeBlobs:
        ballBlob = max(orangeBlobs, key=lambda bL: bL.area())
        img.draw_edges(ballBlob.min_corners(), color=(255, 255, 255))
        dribAngle = (math.atan2((ballBlob.cy() - dribcy), (ballBlob.cx() - dribcx)) * 180 / math.pi) + 180
        cAngle = (math.atan2((ballBlob.cy() - camcy), (ballBlob.cx() - camcx)) * 180 / math.pi) + 180
        bRadius = (math.sqrt(((ballBlob.cy() - camcy) * (ballBlob.cy() - camcy)) + ((ballBlob.cx() - camcx) * (ballBlob.cx() - camcx))))
        lastAngle = cAngle
        lastRadius = bRadius
        print("bRadius: ", bRadius)
        uart.write(str(int(cAngle)) + "\n")
#        if (cAngle >= 80 and cAngle <= 100):
#            uart.write(str(int(cAngle)) + "\n")
#        elif(cAngle >= 0 and cAngle <= 90 and bRadius < 70):
#            uart.write(str(int(270 + cAngle)) + "\n")
#        elif(cAngle >= 90 and cAngle <= 180 and bRadius < 70):
#            uart.write(str(int(90 + cAngle)) + "\n")
#        elif(cAngle >= 180 and cAngle <= 270 and bRadius < 70):
#            uart.write(str(int(cAngle + 90)) + "\n")
#        elif(cAngle >= 270 and cAngle <= 360 and bRadius < 70):
#            uart.write(str(int(cAngle - 90)) + "\n")
#        elif(cAngle >= 225 and cAngle <= 270):
#            uart.write(str(int(cAngle+45)) + "\n")
#        elif(cAngle >= 270 and cAngle <= 315):
#            uart.write(str(int(cAngle-45)) + "\n")
#        else:
#            uart.write(str(int(dribAngle)) + "\n")
        print("dribAngle: ", dribAngle)
    else:
        uart.write("s\n")

