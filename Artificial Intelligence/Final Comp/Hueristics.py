from loa_game_AnyTime import WHITE, BLACK, LinesOfActionState, SpinAction, MoveAction, DIRECTIONS, Direction
from steps import timeLimit
from time import clock
from alpha_beta_ver2 import INFINITY
EMPTY = ' '
class utilityes():
     def __init__(self):
        self.turn=-1

#_______________________anyTIme
     def utilityAnyTime(self, state,player,par,time,safe):
         start_time=clock()
         winner = state.getWinner()
         if winner == player:
            return 1
         if winner is not None:
            return -1
        
         Futility=0
         center=self.centralization(state,player) #(mycenter, enemycenter,utiltity)
         if(timeLimit().time_over(time, start_time, safe)):
             return Futility
         distance=self.getdistance(state,center[0],center[1],player) #(mydistance,enedistance)
         if(timeLimit().time_over(time, start_time, safe)):
             return Futility
         connect=self.getConnective(state, player) #(countB,countW,max_B,max_W,state.blacks,state.whites)
         if(timeLimit().time_over(time, start_time, safe)):
             return Futility
         blockW=par[0]
         centerW=par[1]
         myNumberConnectW=par[2]
         enemyNumberConnectW=par[3]
         myMaxConnectW=par[4]
         enemyMaxConnectW=par[5]
         threatW=par[6]
         materialW=par[7]
         #
         blockS=center[2]
         myCenterS=distance[0]
         enemyCenterS=distance[1]
         myNumberConnectS=connect[0]
         enemyNumberConnectS=connect[1]
         myMaxConnectS=connect[2]
         enemyMaxConnectS=connect[3]
         materialS=abs(connect[5]-connect[4])
         threatS=connect[5]-connect[3]
         #
         
         if(self.turn==-1):
             self.turn=state.turns_left
         Futility=(blockW*blockS)+(centerW*myCenterS)+(myNumberConnectW*myNumberConnectS)+(enemyNumberConnectW*enemyNumberConnectS)
         Futility+=(myMaxConnectW*myMaxConnectS)+(enemyMaxConnectW*enemyMaxConnectS)+(threatW*threatS)+(materialW*materialS)
         return Futility*1.0/(state.size*state.size*state.size*state.size*state.size) 
         
         
#____________________________________________________________________________---             
     def getdistance(self,state,myC,enemyC,player):
         eDistance=0
         myDistance=0
         for row, row_data in enumerate(state.board):
             for col, cell in enumerate(row_data):
                 if cell != EMPTY:
                     if cell != player:
                         eDistance+=abs(row-enemyC[0])+abs(col-enemyC[1])
                     else:
                         myDistance+=abs(row-myC[0])+abs(col-myC[1])
         return (myDistance,eDistance)
#_________________________________________________________   
     def centralization(self,state,player):
         myUtility=0
         myCenter_row=0
         enemyCenter_row=0
         myCenter_col=0
         enemyCenter_col=0
         myCenter=(0,0)
         enemyCenter=(0,0)  
         blocked={}
         i=0
         weight=1
         for row, row_data in enumerate(state.board):
             for col, cell in enumerate(row_data):
                 if cell != EMPTY:
                     if cell != player:
                         enemyCenter_row+=row
                         enemyCenter_col+=col
                         count=0
                         for direction in DIRECTIONS:
                             action, state1 = state._getMoveAction(row, col, direction)
                             if action is not None:  #check blocking
                                count+=1
                         for spin in [(row, col), (row - 1, col), (row, col - 1), (row - 1, col - 1)]:
                             action, state1 = state._getSpinAction(spin[0], spin[1])
                             if action is not None:
                                count+=1
                         if(count<=1):
                             myUtility+=weight
                             blocked[i]=(row,col)
                     else:
                         myCenter_row+=row
                         myCenter_col+=col
                         count2=0
                         for direction in DIRECTIONS:
                             action, state1 = state._getMoveAction(row, col, direction)
                             if action is not None:  #check blocking
                                count2+=1
                         for spin in [(row, col), (row - 1, col), (row, col - 1), (row - 1, col - 1)]:
                             action, state1 = state._getSpinAction(spin[0], spin[1])
                             if action is not None:
                                count2+=1
                         if(count2<=2):
                             myUtility-=weight*0.0
                         
         if(player==BLACK):
             enemySize=state.whites
             mySize=state.blacks
         else:
             enemySize=state.blacks
             mySize=state.whites
         enemyCenter=(enemyCenter_row*1.0/enemySize,enemyCenter_col*1.0/enemySize)
         myCenter=(myCenter_row*1.0/mySize,myCenter_col*1.0/mySize)
         return (myCenter,enemyCenter,myUtility)
#_______________________________________________---- 
     def getConnective(self,state,player):                    
         white_visited={}
         black_visited={}
         max_len_white = 0
         max_len_black = 0
         countW=0
         countB=0
         flagW=0
         flagB=0  
         max_W=0
         max_B=0
         black_wins=0
         white_wins=0
         weight=0.5
         for row, row_data in enumerate(state.board):
             for col, cell in enumerate(row_data):
                 if cell == WHITE:
                     component = state._getConnectiveComponent(row, col, WHITE)
                     white_wins = (len(component) ) *1.0
                     if(white_wins > max_W):
                         max_W=white_wins
                     for element in white_visited:
                        if element in component:
                            flagW=flagW+1
                     if(flagW==0):
                        countW=countW+1
                     flagW=0
                     white_visited[(row,col)]=1          
                 if cell == BLACK:
                     component = state._getConnectiveComponent(row, col, BLACK)
                     black_wins = (len(component) ) *1.0
                     if(black_wins > max_B):
                         max_B=black_wins
                     for element in black_visited:
                        if element in component:
                            flagB=flagB+1
                     if(flagB==0):
                        countB=countB+1
                     flagB=0
                     black_visited[(row,col)]=1
         if(player==BLACK):
             return(countB,countW,max_B,max_W,state.blacks,state.whites)  
         else:
             return(countW,countB,max_W,max_B,state.whites,state.blacks)        

