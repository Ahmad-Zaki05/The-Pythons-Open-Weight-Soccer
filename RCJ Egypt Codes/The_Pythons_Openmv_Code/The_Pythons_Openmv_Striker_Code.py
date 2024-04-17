import sensor, image, time, math, pyb
from pyb import Pin, UART
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 2000)
sensor.set_auto_gain(False)
sensor.set_auto_whitebal(False)
sensor.set_auto_exposure(False)
sensor.set_vflip(True)
#orangeThreshold = [(45, 70, 27, 90, 1, 63), (35, 71, 14, 76, 55, 71)] # bellel , (51, 74, 18, 81, 2, 62),
#yellowThreshold = [(32, 39, 9, 32, 16, 32), (29, 36, -4, 32, 16, 32)] # bellel
orangeThreshold = [(57, 73, 32, 94, 19, 58), (60, 80, 30, 89, 8, 58)] # elsob7 # (60, 77, 30, 89, 8, 58)
yellowThreshold = [(79, 85, 4, 24, 29, 56), (82, 93, -10, 16, 38, 57)] # elsob7
blueThreshold = [(46, 57, -2, 18, -48, -25), (42, 57, -2, 18, -48, -25)] # elsob7
goalThreshold = []
pin0 = Pin("P0", Pin.IN, Pin.PULL_DOWN)
uart = UART(3, 115200)
camcx = 184
camcy = 127
dribcx = 184
dribcy = 65
flagBall = 0
lastAngle = 0
lastRadius = 0
last_x = 0
ball_min_x = camcx - 4 #153
ball_max_x = camcx + 7 #162
clock = time.clock()
while(True):
    clock.tick()
    img = sensor.snapshot()
    img.draw_circle(camcx, camcy, 60, color=(0,0,0), thickness=1, fill=True)
    img.draw_circle(camcx, camcy, 160, color=(0,0,0), thickness=55, fill=False)
    img.draw_circle(camcx, camcy, 200, color=(0,0,0), thickness=50, fill=False)
    img.draw_cross(dribcx, dribcy)
    print("pin0: ", pin0.value())
    if (pin0.value() == 0):
        goalThreshold = yellowThreshold
    else:
        goalThreshold = blueThreshold
    orangeBlobs = img.find_blobs(orangeThreshold, pixels_threshold=5, area_threshold=5, merge=True)
    goalBlobs = img.find_blobs(goalThreshold, pixels_threshold=20, area_threshold=20, merge=True)
    if orangeBlobs:
        ballBlob = max(orangeBlobs, key=lambda bL: bL.area())
        img.draw_edges(ballBlob.min_corners(), color=(255, 255, 255))
        dribAngle = (math.atan2((ballBlob.cy() - dribcy), (ballBlob.cx() - dribcx)) * 180 / math.pi) + 180
        cAngle = (math.atan2((ballBlob.cy() - camcy), (ballBlob.cx() - camcx)) * 180 / math.pi) + 180
        bRadius = (math.sqrt(((ballBlob.cy() - camcy) * (ballBlob.cy() - camcy)) + ((ballBlob.cx() - camcx) * (ballBlob.cx() - camcx))))
        lastAngle = cAngle
        lastRadius = bRadius
        last_x = ballBlob.cx()
        print("bRadius: ", bRadius)
        if (cAngle >= 80 and cAngle <= 100):
            uart.write("B" + str(int(cAngle)) + "\n")
        elif(cAngle >= 0 and cAngle <= 90 and bRadius < 70):
            uart.write("B" + str(int(270 + cAngle)) + "\n")
        elif(cAngle >= 90 and cAngle <= 180 and bRadius < 70):
            uart.write("B" + str(int(90 + cAngle)) + "\n")
        elif(cAngle >= 180 and cAngle <= 270 and bRadius < 70):
            uart.write("B" + str(int(cAngle + 90)) + "\n")
        elif(cAngle >= 270 and cAngle <= 360 and bRadius < 70):
            uart.write("B" + str(int(cAngle - 90)) + "\n")
        elif(cAngle >= 225 and cAngle <= 270):
            uart.write("B" + str(int(cAngle+45)) + "\n")
        elif(cAngle >= 270 and cAngle <= 315):
            uart.write("B" + str(int(cAngle-45)) + "\n")
        else:
            uart.write("B" + str(int(dribAngle)) + "\n")
        print("dribAngle: ", dribAngle)
    else:
#        uart.write("S\n")
#        print("S")
        if flagBall:
            if goalBlobs:
                goalBlob = max(goalBlobs, key=lambda bL: bL.area())
                img.draw_edges(goalBlob.min_corners(), color=(0, 255, 255))
                goalAngle = (math.atan2((goalBlob.cy() - camcy), (goalBlob.cx() - camcx)) * 180 / math.pi) + 180
                goalRadius = (math.sqrt(((goalBlob.cy() - camcy) * (goalBlob.cy() - camcy)) + ((goalBlob.cx() - camcx) * (goalBlob.cx() - camcx))))
                print("goalAngle: ", goalAngle)
                print("goal radius: ", goalRadius)
#                if(goalRadius < 100):
#                    uart.write("H" + "\n")
#                    print("shooot")
#                else:
                uart.write("B" + str(int(goalAngle)) + "\n") #should be G
        else:
            print("S")
            uart.write("S\n")
    print("last radius: ", lastRadius)
    print("last angle: ", lastAngle)
    print("last x", last_x)
    if(ball_min_x < last_x and ball_max_x > last_x): #lastRadius < 75 and lastAngle > 80 and lastAngle < 100
        flagBall = 1
    else:
        flagBall = 0
