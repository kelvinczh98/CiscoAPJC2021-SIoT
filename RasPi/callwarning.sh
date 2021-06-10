#!/bin/bash
cd #change directory to home
cd Desktop/botstuff	#change directory to desktop/botstuff
source venv/bin/activate #create environment
export auth_token=MDQ4ODg3ZTEtZjAwMi00NzY4LTkzM2YtNjQxNDBlNWQ3ZmQ3NDQ4NWQ0ZGItYmY3_PF84_ccaf94d0-7bf0-40f3-9fbb-6ee45bcdf6de #set bot token
python /home/pi/Desktop/botstuff/warningmsg.py #run the python script for warning message in webex

