For Arduino folder:
1. Upload the code to Arduino Uno and connect the sensors accordingly.
2. Connect the Arduino to Rasberry Pi using USB cable.

For RasPi folder:
1. Save the contents in the same directory.
2. For Master.py:
   - Change API key to your own thingspeak API key
   - Change directory accordingly for callwarning.sh and warningmsg.py to send message to webex server
   - Change the serial input accordingly under main code section
3. For botstuff/callwarning.sh:
   - Change bot token to your own token

For Windows folder:
1. Change the IP address depending on the computer's IP that you want to send popup to.


Sample output of Dashboard monitoring:
https://thingspeak.com/channels/1408487
