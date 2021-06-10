from python_webex.v1.Bot import Bot

bot = Bot()
# bot send msg to rood_id with no message and a picture to webex
bot.send_message(room_id='Y2lzY29zcGFyazovL3VzL1JPT00vMDhkMjNkZjAtYjg1MS0xMWViLWExMGQtMjFiNWI5ZDg1NjFi', text='', files=['https://www.visualbuilding.co.uk/images/2D/fireescapeplan.jpg'])
# bot send msg "Fire Hazard! Evacuate immediately!" to webex
bot.send_message(room_id='Y2lzY29zcGFyazovL3VzL1JPT00vMDhkMjNkZjAtYjg1MS0xMWViLWExMGQtMjFiNWI5ZDg1NjFi', text='Fire Hazard! Evacuate immediately!')
