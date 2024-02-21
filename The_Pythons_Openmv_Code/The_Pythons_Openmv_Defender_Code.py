import sensor, image, time, math, pyb
from pyb import UART, Pin
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 2000)
sensor.set_auto_gain(False)
sensor.set_auto_whitebal(False)
sensor.set_auto_exposure(False)
sensor.set_vflip(True)
orangeThreshold = [(57, 73, 32, 94, 19, 58), (60, 80, 30, 89, 8, 58), (81, 94, -7, 18, 14, 55)] # elsob7 # (60, 77, 30, 89, 8, 58)
yellowThreshold = [(71, 80, 8, 29, 33, 68), (82, 93, -10, 16, 38, 57)] # elsob7
blueThreshold = [(46, 57, -2, 18, -48, -25), (42, 57, -2, 18, -48, -25), (55, 68, -6, 14, -37, -19)] # elsob7
goalThreshold = []
pin0 = Pin("P0", Pin.IN, Pin.PULL_DOWN)
uart = UART(3, 115200)
camcx = 177
camcy = 141
dribcx = 178
dribcy = 46
flagBall = 0
lastAngle = 0
lastRadius = 0
backflag = 0
frontflag = 0
goalflag = 0
ball_min_x = camcx - 10 #153
ball_max_x = camcx + 10 #162
clock = time.clock()
timer = pyb.millis()
while(True):
    clock.tick()
    img = sensor.snapshot()
    img.draw_circle(camcx, camcy, 50, color=(0,0,0), thickness=1, fill=True)
    img.draw_circle(camcx, camcy, 160, color=(0,0,0), thickness=55, fill=False)
    img.draw_circle(camcx, camcy, 199, color=(0,0,0), thickness=55, fill=False)
    img.draw_cross(dribcx, dribcy)
    orangeBlobs = img.find_blobs(orangeThreshold, pixels_threshold=5, area_threshold=5, merge=True)

    print("pin0: ", pin0.value())
    if (pin0.value() == 0):
        goalThreshold = yellowThreshold
    else:
        goalThreshold = blueThreshold

    uart.write('D')

    goalBlobs = img.find_blobs(goalThreshold, pixels_threshold=20, area_threshold=20, merge=True)
    if goalBlobs:
        goalBlob = max(goalBlobs, key=lambda bL: bL.area())
        img.draw_edges(goalBlob.min_corners(), color=(0, 255, 255))
        goalAngle = (math.atan2((goalBlob.cy() - camcy), (goalBlob.cx() - camcx)) * 180 / math.pi) + 180
        goalRadius = (math.sqrt(((goalBlob.cy() - camcy) * (goalBlob.cy() - camcy)) + ((goalBlob.cx() - camcx) * (goalBlob.cx() - camcx))) * math.sin(goalAngle * math.pi / 180) * -1)
        goalrect = goalBlob.rect()
        goalx = goalrect[0]
        if (camcx < goalx + 5):
            goalflag = -1
        else:
            goalx = goalrect[0] + goalrect[2]
            if (camcx > goalx - 5):
                goalflag = 1
            else:
                goalflag = 0
        print("goalRadius: ", goalRadius)
        if goalRadius > 93: #85
            backflag = 1 #b
            print('b')
        elif goalRadius < 90: #80
            frontflag = 1 #f
            print('f')
        else:
            uart.write('s')
            print('s')
        timer = pyb.millis()
#    else:
#        backflag = 1
    if backflag == 1 or frontflag == 1:
        if backflag == 1:
            uart.write('b')
        else:
            uart.write('s')
        goalBlobs = img.find_blobs(goalThreshold, pixels_threshold=20, area_threshold=20, merge=True)
        if goalBlobs:
            goalBlob = max(goalBlobs, key=lambda bL: bL.area())
            img.draw_edges(goalBlob.min_corners(), color=(0, 255, 255))
            goalAngle = (math.atan2((goalBlob.cy() - camcy), (goalBlob.cx() - camcx)) * 180 / math.pi) + 180
            goalRadius = (math.sqrt(((goalBlob.cy() - camcy) * (goalBlob.cy() - camcy)) + ((goalBlob.cx() - camcx) * (goalBlob.cx() - camcx))) * math.sin(goalAngle * math.pi / 180) * -1)
            if goalRadius < 93: #85
                backflag = 0
            if goalRadius > 90: #80
                frontflag = 0

    if orangeBlobs:
        ballBlob = max(orangeBlobs, key=lambda bL: bL.area())
        img.draw_edges(ballBlob.min_corners(), color=(255, 255, 255))
        dribAngle = (math.atan2((ballBlob.cy() - dribcy), (ballBlob.cx() - dribcx)) * 180 / math.pi) + 180
        cAngle = (math.atan2((ballBlob.cy() - camcy), (ballBlob.cx() - camcx)) * 180 / math.pi) + 180
        bRadius = (math.sqrt(((ballBlob.cy() - camcy) * (ballBlob.cy() - camcy)) + ((ballBlob.cx() - camcx) * (ballBlob.cx() - camcx))))
        lastAngle = cAngle
        lastRadius = bRadius
        print("bRadius: ", bRadius)
        if (goalflag == 1 and ballBlob.cx() >= ball_max_x):
            uart.write("s\n")
        elif (goalflag == -1 and ballBlob.cx() <= ball_min_x):
            uart.write("s\n")
        else:
            uart.write(str(int(cAngle)) + "\n")
        print("dribAngle: ", dribAngle)
    else:
        uart.write("s\n")

