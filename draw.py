from mpl_toolkits.mplot3d import axes3d
import numpy as np
import matplotlib.pyplot as plt
import sys


def drawFromLevel(level_data,old_dimensions,dimensions,new_dimensions,plt):
	fixed_dimension = int(level_data[0])
	if(len(dimensions) == 0):
		line_points = [[],[]]
		left_dim = [[],[]]
		right_dim = [[],[]]	
		if level_data[1] != 'N':
			for j in range(2):
				old_dim = old_dimensions[0][j]
				if j == fixed_dimension:
					line_points[j] = [int(level_data[1]),int(level_data[1])]
					left_dim[j] = [old_dim[0],int(level_data[1])]
					right_dim[j] = [int(level_data[1]),old_dim[1]]
				else:
					line_points[j] = [old_dim[0],old_dim[1]]
					left_dim[j] = line_points[j]
					right_dim[j] = line_points[j]
			dimensions.append(line_points)
			new_dimensions.append(left_dim)
			new_dimensions.append(right_dim)
			plt.plot(line_points[0],line_points[1])
		else:
			new_dimensions.append([])
		
	
	else:
		for i in range(1,len(level_data)):
			line_points = [[],[]]
			left_dim = [[],[]]
			right_dim = [[],[]]		
			if level_data[i] != 'N':
				for j in range(2):
					old_dim = old_dimensions[int((i-1)/2)][j]
					dim = dimensions[i-1][j]
					if j == fixed_dimension:
						line_points[j] = [int(level_data[i]),int(level_data[i])]
						left_dim[j] = [old_dim[0],int(level_data[i])]
						right_dim[j] = [int(level_data[i]),old_dim[1]]
					else:	
						line_points[j] = [dim[0],dim[1]]
						left_dim[j] = line_points[j]
						right_dim[j] = line_points[j]

				new_dimensions.append(left_dim)
				new_dimensions.append(right_dim)
				plt.plot(line_points[0],line_points[1])
			else:
				new_dimensions.append([])
		
	old_dimensions[:] = dimensions
	dimensions[:] = new_dimensions
	new_dimensions[:] = []
	
	return 




positions = []
f = open(sys.argv[1], "r")
line = f.readline()
arr = line.split(" ")
points = int(arr[0])

for i in range(int(arr[1])):
	positions.append([])

if int(arr[1]) == 2:
	fig = plt.figure()
	ax = fig.add_subplot(111)
	maxX = 10
	maxY = 10
	for i in range(points):
		line = f.readline()
		arr = line.split(" ")
		positions[0].append(int(arr[0]))
		positions[1].append(int(arr[1]))

	ax.set_xlim(0, maxX)
	ax.set_ylim(0, maxY)
	plt.scatter(positions[0], positions[1])
	
	tree = open("tree.txt", "r")
	old_dimensions = [[[0,maxX],[0,maxY]]]
	dimensions = []
	new_dimensions = []
	for level in tree:
		level_data = level.split(" ")
		level_data.pop()
		drawFromLevel(level_data,old_dimensions,dimensions,new_dimensions,plt)
	plt.show()

elif int(arr[1]) == 3:
	fig = plt.figure()
	ax = fig.add_subplot(111,projection = '3d')
	for i in range(points):
		line = f.readline()
		arr = line.split(" ")
		positions[0].append(int(arr[0]))
		positions[1].append(int(arr[1]))
		positions[2].append(int(arr[2]))

	positions[0] = np.array(positions[0])
	positions[1] = np.array(positions[1])
	positions[2] = np.array(positions[2])
	ax.scatter(positions[0],positions[1],positions[2])
	plt.show()

else:
	print("cant draw that many dimensions")