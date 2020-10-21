import numpy as np
import matplotlib.pyplot as plt

class Plotting():

    bufforSize = 1000
    fig = None
    screen = None
    ax = None

    def __init__(self):
        pass

    def singlePlot(self, arr1,arr2,name1,name2):
        plt.plot(arr1,arr2)
        plt.xlabel(name1)
        plt.ylabel(name2)
        plt.show()


    def initLivePlot(self, maxBuffor):
        self.bufforSize = maxBuffor
        self.fig = plt.figure()
        self.ax = self.fig.add_subplot(1,1,1)

    def livePlot(self, dataX, dataY):
        
        plt.plot(dataX, dataY)
        plt.show()
