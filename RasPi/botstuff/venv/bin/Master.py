#!/usr/bin/env python3
import serial
import json
import time
import pymysql
import os
import re
import sys

import subprocess
import RPi.GPIO as GPIO
from time import sleep
from urllib.request import urlopen

#api for thingspeak. Each baseURLx is respective to each field. 

baseURL1 = 'http://api.thingspeak.com/update?api_key=ETE1BCFYY4VMDN1R&field1='
baseURL2 = 'http://api.thingspeak.com/update?api_key=ETE1BCFYY4VMDN1R&field2='
baseURL3 = 'http://api.thingspeak.com/update?api_key=ETE1BCFYY4VMDN1R&field3='
baseURL4 = 'http://api.thingspeak.com/update?api_key=ETE1BCFYY4VMDN1R&field4='
baseURL5 = 'http://api.thingspeak.com/update?api_key=ETE1BCFYY4VMDN1R&field5='
baseURL6 = 'http://api.thingspeak.com/update?api_key=ETE1BCFYY4VMDN1R&field6='


#converting true/false value into 0 and 1. 
def convertTrueFalse(x):
    final = x
    if final == "SAFE":
        result = "0"
        return result
    elif final == "TRUE":
        result= "1"
        return result
        
    
            
            
#function to detect fire or smoke 
def trueOrFalseAlarm(line):
    x = re.search("TRUE", line) #if match with line read from serial if any is true
    if x: #if any is true, run the bash script which sends message to webex server
        cmd = subprocess.Popen(['bash','/home/pi/Desktop/botstuff/callwarning.sh'])
        


#function for parsing values to be used in a json file for other servers. 
def parseJson(x): 
    start_time = time.time()
    #boolean for the first and last value in the json file
    counterStart= True
    counterEnd= False
     
    with open ("data.json",'w') as outfile:
        
              current_time = time.time()
              elapsed_time = current_time - start_time

              #converting first reading from module to json acoording to the heading format
              if counterStart== True:
                    outfile.write("{" + "\n" + '"Users":[\n')
                    json.dump(x.translate({ord('"'): None}) ,outfile)
                    outfile.write("\n" +"," +"\n")
                    counterStart= False

            #if time is less that 10 second, the readings will be inserted into json file
              if elapsed_time < 10:
                    json.dump(x.translate({ord('"'): None}) ,outfile)
                    outfile.write("\n" +"," +"\n")

            #if time is more than 10 second, add the value to the json then change the counterEnd value to True for the last value
              if elapsed_time>10:
                  json.dump(x.translate({ord('"'): None}) ,outfile)
                  outfile.write("\n" +"," +"\n")
                  counterEnd = True
            #break condition and append the last value. Closes the file. 
              if counterEnd == True:
                    json.dump(x.translate({ord('"'): None}) ,outfile)
                    outfile.write ("]" +"}")
                    counterEnd= False
                    counterStart= True
                    outfile.close()

    

#main code
if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=1)
    ser.flush()
   
   #if there is an input, the script will execute in a while true loop
    while True:
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').rstrip()
            trueOrFalseAlarm(line)
            #sorting the values from the output using index manipulation.
            
            zone = line[8]
            humidity= line[23:28]
            temperature= line[45:50]
            heat_index= line[65:70]
            smoke=line[81:85]
            fire= line[95:99]
            #run the function to convert true/false into 0/1
            convertedSmoke= convertTrueFalse(smoke)
            convertedFire= convertTrueFalse(fire)
            print (line)  
            
            #uploading the reading to thingspeak server
            f = urlopen(baseURL1 + str(zone) + baseURL2 + str(humidity) + baseURL3 + str(temperature) + baseURL4 + str(heat_index) + baseURL5 + str(convertedSmoke)+ baseURL6 + str (convertedFire))

            f.read()
            f.close()      

 


            

