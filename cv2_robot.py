#cv2_robot.py
#! /usr/bin/python

##################################################################################
#  A proof of concept script for stopping a robot car by showing it a stop sign  #
#  Using cv2 haar cascade method and GPIOZERO.Robot                              #
#  Author Michiel Bontenbal 2020                                                 #
##################################################################################

#instruction: install both this script and 'haar_cascade_stop.xml' in same folder
# start the script. Put the stop sign in front of camera.
# the cv2.rectangle method puts a 'bouncing box' around the stop sign. The closer the car gets, the bigger the area of bouncing box. 
# Play with this parameter to define the moment the car needs to stop.
# end the script by pressing 'q' 

from time import sleep
import cv2
from gpiozero import Robot

robot = Robot(left=(17,22), right=(24,23))

stop_cascade = cv2.CascadeClassifier('haar_cascade_stop.xml')
cap = cv2.VideoCapture(0) #0 is the default camera

robot.forward(speed=0.3)  

nstops = 0
while cap.isOpened():
    ret, img = cap.read() 
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    stopsign = stop_cascade.detectMultiScale(gray, 1.1, 4)

    
    for (x, y, w, h) in stopsign:
        rect = cv2.rectangle(img, (x,y), (x+w, y+h), (255,0,0), 2)
        area = w * h
        print(area)
        sleep(0.05)
        # 30cm = 2000 = 2,5cm => 5cm nodig + hoger
        
        if area > 2000:  #Play with this parameter 
            nstops = nstops + 1
                
    # Display the output
    cv2.imshow('img', img)
    
      
    
    if nstops == 1:
        print("STOP!")
        #img = cv2.putText(img, "Stop",(50,50), cv2.FONT_HERSHEY_SIMPLEX, 1, (0,255,255), 2, cv2.LINE_AA)
        #nstops = 0
        robot.stop()
        sleep(5)
        nstops += 1
        robot.forward(speed=0.3)
    
    if cv2.waitKey(25) & 0xFF == ord('q'): #press q to end script and stop robot
        break

cap.release()
cv2.destroyAllWindows()
robot.stop()
