import sys
import matplotlib.pyplot as plt
import numpy as np
from matplotlib.font_manager import FontProperties


def main():

	spline = False
	if len(sys.argv) > 1:
	    spline = True
	if spline == True:
		f_x = open("splinex.txt", "r")
		f_y = open("spliney.txt", "r")
	else:
		f_x = open("lagrangex.txt", "r")
		f_y = open("lagrangey.txt", "r")
	def_input=[]
	x = []
	approx_y = []
	for val in f_x.read().split():
		x.append(float(val))
	f_x.close()

	for val in f_y.read().split():
		approx_y.append(float(val))
	f_y.close()

	with open("input4.txt", "r") as filestream:
		for line in filestream:
			currentline = line.split(",")
			def_input.append(float(currentline[1]))
	plt.figure()
	plt.plot(x,def_input,"orange",label="Input")
	plt.plot(x, approx_y,"blue",label = "Spline Interpolation" if spline else "Lagrange Interpolation")
	plt.ylabel('y')
	plt.xlabel('x')
	plt.legend(bbox_to_anchor=(1.1,1.05))
	ax = plt.gca()
	ax.set_ylim([0,1000])
	plt.show()

main()