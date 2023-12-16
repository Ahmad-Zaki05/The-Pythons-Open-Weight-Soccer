import sensor, image, time, math
from pyb import UART
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 2000)
sensor.set_auto_gain(False)
sensor.set_auto_whitebal(False)
sensor.set_vflip(True)
orangeThreshold = [(37, 67, 41, 98, 14, 96), (25, 67, 39, 112, 18, 103), (37, 76, 28, 56, -2, 32)] # (36, 88, 29, 71, -6, 52)
yellowThreshold = [(32, 39, 10, 31, 32, 46), (30, 45, 18, 42, 30, 54)]
uart = UART(3, 115200)
camcy = 122
camcx = 136
dribcx = 132
dribcy = 65
flagBall = 0
lastAngle = 0
lastRadius = 0
clock = time.clock()
while(True):
    clock.tick()
    img = sensor.snapshot()
#    img.draw_circle(camcx, camcy, 50, color=(0,0,0), thickness=1, fill=True)
#    img.draw_circle(camcx, camcy, 140, color=(0,0,0), thickness=55, fill=False)
#    img.draw_circle(camcx, camcy, 190, color=(0,0,0), thickness=50, fill=False)
    img.draw_cross(dribcx, dribcy)
    orangeBlobs = img.find_blobs(orangeThreshold, pixels_threshold=17, area_threshold=17, merge=True)
    yellowBlobs = img.find_blobs(yellowThreshold, pixels_threshold=20, area_threshold=20, merge=True)
    if orangeBlobs:
        ballBlob = max(orangeBlobs, key=lambda bL: bL.area())
        img.draw_edges(ballBlob.min_corners(), color=(255, 255, 255))
        dribAngle = (math.atan2((ballBlob.cy() - dribcy), (ballBlob.cx() - dribcx)) * 180 / math.pi) + 180
        cAngle = (math.atan2((ballBlob.cy() - camcy), (ballBlob.cx() - camcx)) * 180 / math.pi) + 180
        bRadius = (math.sqrt(((ballBlob.cy() - camcy) * (ballBlob.cy() - camcy)) + ((ballBlob.cx() - camcx) * (ballBlob.cx() - camcx))))
        lastAngle = cAngle
        lastRadius = bRadius
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
        if flagBall:
            if yellowBlobs:
                goalBlob = max(yellowBlobs, key=lambda bL: bL.area())
                img.draw_edges(goalBlob.min_corners(), color=(255, 255, 255))
                goalAngle = (math.atan2((goalBlob.cy() - camcy), (goalBlob.cx() - camcx)) * 180 / math.pi) + 180
                goalRadius = (math.sqrt(((goalBlob.cy() - camcy) * (goalBlob.cy() - camcy)) + ((goalBlob.cx() - camcx) * (goalBlob.cx() - camcx))))
                print("goalAngle: ", goalAngle)
                print("goal radius: ", goalRadius)
                if(goalRadius < 100):
                    uart.write("H" + "\n")
                    print("shooot")
                else:
                    uart.write("G" + str(int(goalAngle)) + "\n")
        else:
            print("S")
            uart.write("S\n")
    print("last radius: ", lastRadius)
    print("last angle: ", lastAngle)
    if(lastRadius < 75 and lastAngle > 80 and lastAngle < 100):
        flagBall = 1
    else:
        flagBall = 0
