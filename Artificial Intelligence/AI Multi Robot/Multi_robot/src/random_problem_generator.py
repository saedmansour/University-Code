###############################################################################
####### IMPORT
from random import *



###############################################################################
class ProblemGenerator():
    
    def genereateHard(self):
        boardWidth  = randint(7,25)
        boardHeight = randint(7,25)
        robotsNum   = randint(1,6)
        #leave 5 spots clear (for dirt at least)
        obstaclesNum= randint(7,max(int((boardWidth*boardHeight-robotsNum-5)*0.1), 8))
        dirtsNum    = randint(1,max(int((boardWidth*boardHeight-robotsNum-obstaclesNum)*0.1),2))
        
        spots = set()
        while len(spots) < (dirtsNum + robotsNum+obstaclesNum):
            xCoordinate = randint(0,boardWidth-1)
            yCoordinate = randint(0,boardHeight-1)
            spots.add((xCoordinate, yCoordinate))
        
        code =  "MultiRobotState(" + str(boardWidth) + "," + str(boardHeight)
        code += ",tuple(["
        for i in xrange(0,robotsNum):
            code += str(spots.pop())
            code +=","
        code += "])"
        code += ",frozenset(["
        for i in xrange(0,dirtsNum):
            code += str(spots.pop())
            code += ","
        code += "])"
        code += ",frozenset(["
        for i in xrange(0,obstaclesNum):
            code += str(spots.pop())
            code += ","
        code += "])"
        code += ")"
        return code
    
    
    def genereateEasy(self):
        boardWidth  = randint(7,25)
        boardHeight = randint(7,25)
        robotsNum   = randint(1,5)
        #dirtsNum    = randint(1,boardWidth*boardHeight-robotsNum)
        dirtsNum = randint(1,int((boardWidth*boardHeight-robotsNum)*0.1))
        
        spots = set()
        while len(spots) < (dirtsNum + robotsNum):
            xCoordinate = randint(0,boardWidth-1)
            yCoordinate = randint(0,boardHeight-1)
            spots.add((xCoordinate, yCoordinate))
        
        code =  "MultiRobotState(" + str(boardWidth) + "," + str(boardHeight)
        code += ",tuple(["
        for i in xrange(0,robotsNum):
            code += str(spots.pop())
            code +=","
        code += "])"
        code += ",frozenset(["
        for i in xrange(0,dirtsNum):
            code += str(spots.pop())
            code += ","
        code += "])"
        code += ",frozenset())"
        return code 
         
        
        
###############################################################################
####### TEST

generator = ProblemGenerator()
for i in xrange(0,100):
    code = "self.easyProblem["+ str(i) + "] = " + generator.genereateEasy()
    #code = "problem["+ str(i) + "] = " + generator.genereateHard()
    print code 
