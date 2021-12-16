#!/usr/bin/env python

# Image Processing Node to track the Horse
# Libraries
import rospy
import numpy as np
import cv2
from std_msgs.msg import String
from sensor_msgs.msg import Image
from cv_bridge import CvBridge, CvBridgeError
from nav_msgs.msg import Odometry
import sys
import csv
import math

bridge = CvBridge()
myfile=open('/home/halil/SimulationResults/simulation.csv','a')
myfile.write(str('Sequence Number')+","+str('Time')+","+str('x1')+","+str('y1')+","+str('x2')+","+str('y2')+","+str('Horse visible')+","+str('Horse complete')+","+str('Horse Movement'))
myfile.write("\n")

def horseCallback(msg):   
  global vx
  vx = msg.twist.twist.linear.x
  print(vx) 

# Callback each Frame from the Iris Camera
def imageCallback(rosImage):
  global bridge
  global hV 
  global hC
  global move
  global count 

  if 1.00000 < vx < 1.78000:
    move = 1
  elif 4.00000 < vx < 4.44500:
    move = 2
  elif 5.9620 < vx < 6:
    move = 3
  elif 9.8 < vx:
    move = 4
  
  timestamp =rosImage.header.stamp.to_sec()

  # Conversion from ROS to OpenCV
  try:
    img = bridge.imgmsg_to_cv2(rosImage, "bgr8")
  except CvBridgeError as e:
      print(e)
  
  # Thresholding the Image
  ret, thresholdImage = cv2.threshold(img, 128, 255, cv2.THRESH_BINARY_INV)

  # Indexing 
  index = thresholdImage.nonzero()
  
  empty = np.all(index)
  
  # Get array with the pixels of the Horse 
  if empty:  
    x1 = -1
    y1 = -1
    x2 = -1
    y2 = -1

    hV = 0
    hC = 0

    myfile.write(str(count)+","+str(timestamp)+","+str(x1)+","+str(y1)+","+str(x2)+","+str(y2)+","+str(hV)+","+str(hC)+","+str(move))
    myfile.write("\n")
  else:
    # Get Coordinates 
    x1 = np.min(index[0])
    y1 = np.min(index[1])
    x2 = np.max(index[0])
    y2 = np.max(index[1])
    # Check Horse in FOV 
    if x1 == 0 or y1 == 0:
      hV = 1
      hC = 0
      
      myfile.write(str(count)+","+str(timestamp)+","+str(x1)+","+str(y1)+","+str(x2)+","+str(y2)+","+str(hV)+","+str(hC)+","+str(move))
      myfile.write("\n")
    elif x2 == 799 or y2 == 799:
      hV = 1
      hC = 0
      
      myfile.write(str(count)+","+str(timestamp)+","+str(x1)+","+str(y1)+","+str(x2)+","+str(y2)+","+str(hV)+","+str(hC)+","+str(move))
      myfile.write("\n")    
    else:
      hV = 1
      hC = 1

      myfile.write(str(count)+","+str(timestamp)+","+str(x1)+","+str(y1)+","+str(x2)+","+str(y2)+","+str(hV)+","+str(hC)+","+str(move))
      myfile.write("\n")
  
  count += 1
  cv2.waitKey(3)

# Main Function  
def main(args):
  
  global count 
  count = 0
  rospy.init_node('imageProcessing', anonymous=True)
  # Subscriber
  while not rospy.is_shutdown():
    horse_sub = rospy.Subscriber("/odom", Odometry, horseCallback)
    image_sub = rospy.Subscriber("/iris/camera_red_iris/image_raw",Image, imageCallback)
    rospy.spin()
  
  #try:
  #  rospy.spin()
  #except KeyboardInterrupt:
  #  print("Shutting down")
  #cv2.destroyAllWindows()

if __name__ == '__main__':
    main(sys.argv)