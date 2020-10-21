import serial
import io
import time

class SerialPort():
    internalSerial = None
    def __init__(self, portName, baud,cmd):
        self.internalSerial = serial.Serial(portName,baud,timeout=1)
        line = ''
        currentTime = time.time()
        while(line.find('INIT')<0):
            if((time.time()-currentTime)>8):
                break
            line = self.getStringLine()
            if(len(line)>3):
                print(line)
        self.internalSerial.write(str.encode(cmd))

    def getLineData(self):
        values=[]
        line = self.getStringLine()
        splited = line.split(',')
        for text in splited:
            values.append(int(text))
        return values

    def getStringLine(self):
        return str(self.internalSerial.readline())[2:-5]
