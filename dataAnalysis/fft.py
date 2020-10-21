
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np
from scipy.fftpack import fft
import tkinter as tk
from tkinter import filedialog
import time
import serialPort

sport = serialPort.SerialPort('COM6', 500000, '/gyro')

bufforSize=100
fig = plt.figure()
ax = fig.add_subplot(1, 1, 1)
xs = []
ys = []

def animate(i, xVs, yVs):
    #values = sport.getLineData()
    values = sport.getLineData()
    xVs.append(values[0])
    yVs.append(values[1])
    if(len(xVs)>bufforSize):
        xVs = xVs[len(xVs)-bufforSize:len(xVs)-1]
        yVs = yVs[len(yVs)-bufforSize:len(yVs)-1]
    ax.clear()
    ax.plot(xs,ys)

ani = animation.FuncAnimation(fig, animate, fargs=(xs, ys), interval=1)
plt.show()
"""try:
    while True:
        values = sport.getLineData()
        xVals.append(values[0])
        yVals.append(values[1])
        plotter.livePlot(xVals,yVals)
        #print(sport.getLineData())

except KeyboardInterrupt:
    sport.internalSerial.close()
    pass
"""
"""
def plot(arr1,arr2,name1,name2):
    plt.plot(arr1,arr2)
    plt.xlabel(name1)
    plt.ylabel(name2)
    plt.show()

#Prompt user for file
root = tk.Tk()
root.withdraw()
file_path = filedialog.askopenfilename(filetypes=[("Two Column CSV","*.csv")])
print(file_path)
 
#Load Data (assumes two column array
t, x, y, z = np.genfromtxt(file_path,delimiter=',', unpack=True)
 
#Determine variables
N = np.int(np.prod(t.shape))#length of the array
T=0
for i in range(1,len(t)):
    T += t[i]-t[i-1]

T /= len(t)
Fs = 1000000/T  #sample rate (Hz)

print("# Samples:",N)
print(Fs)

plot(t/1000, x, "Time", "X")"""



"""
#Plot Data
tic = time.clock()
plt.figure(1)  
plt.plot(t, x)
plt.xlabel('Time (seconds)')
plt.ylabel('Accel (g)')
plt.title(file_path)
plt.grid()
toc = time.clock()
print("Plot Time:",toc-tic)
 
#Compute RMS and Plot
tic = time.clock()
w = np.int(np.floor(Fs)) #width of the window for computing RMS
steps = np.int_(np.floor(N/w)) #Number of steps for RMS
t_RMS = np.zeros((steps,1)) #Create array for RMS time values
x_RMS = np.zeros((steps,1)) #Create array for RMS values
for i in range (0, steps):
    t_RMS[i] = np.mean(t[(i*w):((i+1)*w)])
    x_RMS[i] = np.sqrt(np.mean(x[(i*w):((i+1)*w)]**2))
plt.figure(2)  
plt.plot(t_RMS, x_RMS)
plt.xlabel('Time (seconds)')
plt.ylabel('RMS Accel (g)')
plt.title('RMS - ' + file_path)
plt.grid()
toc = time.clock()
print("RMS Time:",toc-tic)
 
#Compute and Plot FFT
tic = time.clock()
plt.figure(3)  
xf = np.linspace(0.0, 1.0/(2.0*T), N/2)
yf = fft(x)
plt.plot(xf, 2.0/N * np.abs(yf[0:np.int(N/2)]))
plt.grid()
plt.xlabel('Frequency (Hz)')
plt.ylabel('Accel (g)')
plt.title('FFT - ' + file_path)
toc = time.clock()
print("FFT Time:",toc-tic)
plt.show()
"""