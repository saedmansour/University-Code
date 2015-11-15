from time import clock
from alpha_beta_ver2 import INFINITY
#_____________________________
class timeLimit():
    def time_over(self,time,start,safe):
        time_pass=clock() -start
        if(time > time_pass+safe):
            return 0
        else:
            return 1
#______________________________
TIE = 'Tie'
WHITE = 'W'
BLACK = 'B'
EMPTY = ' '
def getConnective(state,player):                    
         max_W=0
         max_B=0
         for row, row_data in enumerate(state.board):
             for col, cell in enumerate(row_data):
                 if cell == WHITE:
                     component = state._getConnectiveComponent(row, col, WHITE)
                     white_wins = (len(component) ) *1.0
                     if(white_wins > max_W):
                         max_W=white_wins         
                 if cell == BLACK:
                     component = state._getConnectiveComponent(row, col, BLACK)
                     black_wins = (len(component) ) *1.0
                     if(black_wins > max_B):
                         max_B=black_wins
         if(player==BLACK):
             return max_B-max_W  
         else:
             return max_W-max_B 
#_______________---
class steps():
    def getBestStep(self,successors,time,safe):
        for action, state in successors:
            return (action,state)
    def getBestStepState(self,successor,time,safe):
        for state in successor:
            return state
#___________________________________________________
class maxDepth():
    def stopDepth(self,state):
        return 1
#___________________________________________________
class cutting():
    def decreaseSuccessors(self,successors):
        return successors
    def decreaseSuccessorsState(self,successors):
        return successors
###############  any time steps ##################################################
#___________________________________________________
class stepsAnyTime():
    def getBestStep(self,successors,player,time=INFINITY,safe=0):
        #count clock
        start_time=clock()
        #
        maxN=-INFINITY
        max_s=(None,None)
        for action, state in successors:
            temp=getConnective(state,player) 
            if(temp>maxN):
                maxN=temp
                max_s=(action,state)
            if(timeLimit().time_over(time, start_time, safe) ):
                return max_s
        return max_s
            
    def getBestStepState(self,successor,player,time=INFINITY,safe=0):
        #count clock
        start_time=clock()
        #
        maxN=-INFINITY
        for  state in successor:
            temp=getConnective(state,player) 
            if(temp>=maxN):
                maxN=temp
                max_s=state
            if(timeLimit().time_over(time, start_time, safe) ):
                return max_s
        return max_s
#___________________________________________________
class maxDepthAnyTime():
    def stopDepth(self,state,time=INFINITY,safe=0):
        return 1
#___________________________________________________
class cuttingAnyTime():
    def decreaseSuccessors(self,successors,time=INFINITY,safe=0):
        #count clock
        start_time=clock()
        #
        for state,action in successors:
            return successors
            state=state
            if(timeLimit().time_over(time, start_time, safe) ):
                return successors
        return successors
    def decreaseSuccessorsState(self,successors,time=INFINITY,safe=0):
        #count clock
        start_time=clock()
        #
        for state in successors:
            return successors
            state=state
            if(timeLimit().time_over(time, start_time, safe) ):
                return successors
        return successors
#___________________________________________________
