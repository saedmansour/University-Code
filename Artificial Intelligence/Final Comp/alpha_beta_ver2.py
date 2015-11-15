# A bloody large number.
INFINITY = 1.0e400
from steps import steps ,maxDepthAnyTime , cuttingAnyTime
from time import clock
class AlphaBetaSearchAnyTimeTemp:
    '''
    This search algorithm implements the limited-resource minimax tree search 
    algorithm with alpha-beta pruning for zero-sum games. This version cuts off 
    search by depth alone and uses an evaluation function (utility).
    '''
    
    def __init__(self, player, max_depth, utility,limited_time,increase=5,table_size=0):
        '''
        Constructor.
        
        @param player: Your player. This search algorithm will choose the best
                       actions for this player.
        @param max_depth: The depth of the search tree.
        @param utility: An evaluation function for states.
        '''
        self.player = player
        self.max_depth = max_depth
        self.utility = utility
        self.max_increase=increase
        self.increase=0
        self.table_size=table_size
        self.table={}
        self.element_table_number=0
        self.time=limited_time
        self.safe=0.05
    def search(self, current_state):
       
        best_value = -INFINITY
        #TODO-HASSAN
        
        #start count the time
        start_time=clock()
        #
        left_time=self.time-clock()+start_time
        mySuccessors = current_state.getSuccessors(left_time,self.safe).items()
        #safe action in case of time over
        for action,state in mySuccessors :
            best_action=action
            break
        #
        #cut part of the state
        mySuccessors= cuttingAnyTime().decreaseSuccessors(mySuccessors,self.time,self.safe)
        #
        length=len(mySuccessors)
        for index in xrange(length) :
        #order the sons
            #check if time over
            if(self.time_over(self.time,start_time)):
                return best_action
            # 
            time_left=self.time-clock()+start_time
            h=steps().getBestStep(mySuccessors,time_left,self.safe)
            #check if the time over
            if(self.time_over(self.time,start_time)):
                return best_action
            #
            state=h[1]
            action=h[0]
            mySuccessors.remove(h)
        #
            value_fn = self._getValueFn(state)
            time_left=self.time-clock()+start_time
            value = value_fn(state, best_value, INFINITY, 1,time_left)
            if value > best_value:
                best_value = value
                best_action = action
        return best_action
    
    def _getValueFn(self, state):
        if state.getCurrentPlayer() == self.player:
            return self._maxValue
        else:
            return self._minValue
    
    def _cutoffTest(self, state, depth):
        #TODO-HASAN
        if(state.getWinner() is not None):
            return 1
        #check if the point not quiet
        if( depth >= self.max_depth and (self.max_increase > self.increase) ) :
            if( maxDepthAnyTime().stopDepth(state) == 0) :
                self.increase+=1
                return 0
            else:
                return 1
        #
        return depth >= self.max_depth
       
    
    def _maxValue(self, state, alpha, beta, depth,time):
        #start count clock
        start_time=clock()
        #
        if self._cutoffTest(state, depth):
            return self.utility(state,time-clock()+start_time,self.safe)
        value = -INFINITY
        #TODO-HASSAN
        left_time=self.time-clock()+start_time
        mySuccessors = state.getSuccessors(left_time,self.safe).values()
        # cut part of state
        time_left=time-clock()+start_time
        mySuccessors= cuttingAnyTime().decreaseSuccessorsState(mySuccessors,time_left,self.safe)
        #
        length=len(mySuccessors)
        for index in xrange(length) :
        #order the sons    
            #check if time over
            if(self.time_over(time,start_time)):
                return value
            # 
            time_left=time-clock()+start_time
            successor=steps().getBestStepState(mySuccessors,time_left,self.safe)
            mySuccessors.remove(successor)
            #check if time over
            if(self.time_over(time,start_time)):
                return value
            # 
        #
        #check if the element is in the table
            if (successor,depth) in self.table:
                value= self.table[(successor,depth)]
            else:
                value_fn = self._getValueFn(successor)
                value = max(value, value_fn(successor, alpha, beta, depth + 1,time-clock()+start_time))
                if(self.table_size>self.element_table_number):
                    self.table[(successor,depth)]=value
                    self.element_table_number+=1
        #
            if value >= beta:
                return value
            alpha = max(alpha, value)
            
        return value
    
    def _minValue(self, state, alpha, beta, depth,time):
        #start count clock
        start_time=clock()
        #
        if self._cutoffTest(state, depth):
            return self.utility(state,time-clock()+start_time,self.safe)
        value = INFINITY
        
        #TODO-HASSAN
        time_left=time-clock()+start_time
        mySuccessors = state.getSuccessors(time_left,self.safe).values()
        # cut part of state
        mySuccessors= cuttingAnyTime().decreaseSuccessorsState(mySuccessors,time_left,self.safe)
        #
        length=len(mySuccessors)
        for index in xrange(length) :
        #order the sons
            #check if time over
            if(self.time_over(time,start_time)):
                return value
            #     
            time_left=time-clock()+start_time
            successor=steps().getBestStepState(mySuccessors,time_left,self.safe)
            mySuccessors.remove(successor)
            #
            if(self.time_over(time,start_time)):
                return value
            # 
        #
        #check if the element is in the table
            if (successor,depth) in self.table:
                value= self.table[(successor,depth)]
            else:
                value_fn = self._getValueFn(successor)
                value = min(value, value_fn(successor, alpha, beta, depth + 1,time-clock()+start_time))
                if(self.table_size>self.element_table_number):
                    self.table[(successor,depth)]=value
                    self.element_table_number+=1
        #
            if value <= alpha:
                return value
            beta = min(beta, value)
        return value

    def time_over(self,time,start):
        time_pass=clock() -start
        if(time > time_pass+self.safe):
            return 0
        else:
            return 1