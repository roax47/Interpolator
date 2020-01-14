import sys
import matplotlib.pyplot as plt
import numpy as np
from matplotlib.font_manager import FontProperties

def main():
    f_input = open("input.txt")

    #input_y=f_input.read().splitlines()
    with open("splinex.txt") as my_file:
        x = my_file.readlines()
    with open("spliney.txt") as my_file:
        approx_y = my_file.readlines()
    plt.figure()
    plt.plot(x,approx_y)
    #ax= plt.gca()
    #ax.set_ylim([-200,3000])
	
	
main()