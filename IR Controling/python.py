'''

Author : @Ziad-Sakr
Des    : Python Code For Controlling mouse that take signals from Arduino

'''
#Download These Libraries

import serial
import mouse



arduino = serial.Serial("COM6",9600)  #Change The "COM" To Yours



while True:

    HexData=arduino.readline().rstrip().decode()
    print(HexData)
    
    #This Hex values changing From TV Remote To another one so change it according to Yours

    if HexData == "E718FF00":                #Left Click
        mouse.click('left')
    elif HexData == "E817FF00":              #Right Click
        mouse.click('right')
    elif HexData == "F906FF00":              #Middle Click
        mouse.click('middle')
    elif HexData == "F807FF00":              #Move Right
        mouse.move(33,0,0,duration=0.1)
    elif HexData == "B847FF00":              #Move Left
        mouse.move(-33,0,0, duration=0.1)
    elif HexData == "E51AFF00":              #Move Up
        mouse.move(0,-33,0, duration=0.1)
    elif HexData == "B748FF00":              #Move Down
        mouse.move(0,33,0, duration=0.1)
