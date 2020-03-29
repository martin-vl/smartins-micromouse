
baseFilePath = "input/proto-start.proto"
endFilePath = "input/proto-end.proto"
exportFilePath = "../protos/maze.proto"

mzSquares = 16
mzSqSize = 0.18


mzArray = [\
  [ 3,10,10, 2,10,10,10,10,10,10,10,10,10, 2,10, 6],\
  [ 1,10, 2,12, 3,10,10,10, 2,10, 2,10,10, 8,10, 4],\
  [ 5, 3,12,11, 8,10, 6, 3, 8, 2, 8, 2,10, 2,10, 4],\
  [ 1,12, 3,10,10, 2, 8, 8,10, 8, 2, 8,10, 9,10,12],\
  [ 5, 3, 8, 6, 3, 8, 6, 3, 6, 3, 0,10, 2, 2,10, 6],\
  [ 5, 1,14, 1, 8,10, 0,12, 9, 4, 5, 7, 5, 5,15, 5],\
  [ 5, 5,11, 4, 7, 3, 8,14,11, 8, 4,13, 5, 5,15, 5],\
  [ 5, 9, 2, 8, 0, 8, 6, 3, 6, 7, 9, 2, 8, 0,10, 4],\
  [ 5, 7, 9, 2, 8, 2,12, 9, 8, 4, 7, 9, 6, 9, 2,12],\
  [ 1,12,11, 0,14, 1,14, 3,10, 4, 9, 2, 8, 2, 8, 6],\
  [ 1, 6, 7, 9, 2, 8, 2, 8, 2,12, 3, 8, 6, 9, 2,12],\
  [ 5, 1, 4, 7, 9, 2, 8, 2, 8,14, 9, 2, 8, 6, 9, 6],\
  [ 5, 5, 9, 4,11, 8,10, 8,14,11,10, 8,10, 8, 6, 5],\
  [ 5, 5, 3,12,11,10, 6, 7, 7, 7, 7,11, 6, 7, 9, 4],\
  [ 5, 5, 1,10, 2,10, 0, 0, 0, 0, 8, 2, 8, 0, 2,12],\
  [13, 9,12,11,12,11,12,13,13,13,11,12,11,12, 9,14]]

print("Generating Maze")

# Open files
baseFile = open(baseFilePath,'r')
endFile = open(endFilePath,'r')
exportFile = open(exportFilePath,'w')

# Get base part
exportFile.write(baseFile.read())
baseFile.close()

# place all poles
for i in range(mzSquares+1):
  for j in range(mzSquares+1):
    offsetX = round((i) * mzSqSize - mzSquares * mzSqSize / 2, 4)
    offsetZ = round((j) * mzSqSize - mzSquares * mzSqSize / 2, 4)
    exportFile.write("\n      mazePole {\n        translation " + str(offsetX) + " 0.025 " + str(offsetZ) + "\n        name \"pole-" + str(i) + "-" + str(j) + "\"\n      }")

# place walls
for i in range(mzSquares):
  offsetX = round((i + 0.5) * mzSqSize - mzSquares * mzSqSize / 2, 4)
  offsetZ = -round(mzSquares * mzSqSize / 2, 4)
  rotationY = 0 #1.5708
  exportFile.write("\n      mazeWall {\n        translation " + str(offsetX) + " 0.025 " + str(offsetZ) + "\n        rotation 0 1 0 " + str(rotationY) + "\n        name \"wall-" + str(i) + "-0\"\n      }")

  offsetX = -round(mzSquares * mzSqSize / 2, 4)
  offsetZ = round((i + 0.5) * mzSqSize - mzSquares * mzSqSize / 2, 4)
  rotationY = 1.5708
  exportFile.write("\n      mazeWall {\n        translation " + str(offsetX) + " 0.025 " + str(offsetZ) + "\n        rotation 0 1 0 " + str(rotationY) + "\n        name \"wall-0-" + str(i+1) + "\"\n      }")

for i in range(mzSquares):
  for j in range(mzSquares):
    sqNum = mzArray[mzSquares-i-1][j]
    if(sqNum & (1 << 1) !=0):
      offsetX = round((i + 1) * mzSqSize - mzSquares * mzSqSize / 2, 4)
      offsetZ = round((j + 0.5) * mzSqSize - mzSquares * mzSqSize / 2, 4)
      rotationY = 1.5708
      exportFile.write("\n      mazeWall {\n        translation " + str(offsetX) + " 0.025 " + str(offsetZ) + "\n        rotation 0 1 0 " + str(rotationY) + "\n        name \"wallA-" + str(i+1) + "-" + str(j+1) + "\"\n      }")

    if(sqNum & (1 << 2) !=0):
      offsetX = round((i + 0.5) * mzSqSize - mzSquares * mzSqSize / 2, 4)
      offsetZ = round((j + 1) * mzSqSize - mzSquares * mzSqSize / 2, 4)
      rotationY = 0
      exportFile.write("\n      mazeWall {\n        translation " + str(offsetX) + " 0.025 " + str(offsetZ) + "\n        rotation 0 1 0 " + str(rotationY) + "\n        name \"wallB-" + str(i+1) + "-" + str(j+1) + "\"\n      }")

# Add end part
exportFile.write(endFile.read())
endFile.close()

# Close file
exportFile.close()