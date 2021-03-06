#############################
##                         ##
##   A* Search Algorithm   ##
##                         ##
#############################

# This is an implementation of the SearchAlgorithm interface for the following
# search algorithms:
# - A*
# - IterativeDeepeningAStar
#
# The IterativeDeepeningAStar variant allows you to search with A* using layers
# of depth in the graph, with each search increasing the maximum depth.

from algorithm import Heuristic, SearchAlgorithm
from myGraph import GraphSearch
from utils import *
import time
from  types import *
from problem import ProblemState
finished=0

class AStarWeight (SearchAlgorithm):
    '''
    Implementation of the A* search algorithm for the Problem.
    It may also take a maximum depth at which to stop, if needed.
    '''

    def __init__(self ,limit_time = infinity, max_depth=infinity):
        '''
        Constructs the A* search.
        Optionally, a maximum depth may be provided at which to stop looking for
        the goal state.
        
        Given weight = 1/2, this algorithm is idnetical to A*
        '''
        self.max_depth = max_depth
        self.limit=limit_time

    def find(self, problem_state, heuristic):
        '''
        A* search is best-first graph search with f(n) = g(n)+h(n).
        You need to specify the h function when you call astar_search.
        Uses the pathmax trick: f(n) = max(f(n), g(n)+h(n)).

        @param problem_state: The initial state to start the search from.
        @param heuristic: A heuristic function that scores the Problem states.
        '''
        # This is the node evaluation function for the given heuristic.
        def evaluator(node):
            return self.weight*node.path_cost + (1-self.weight)*heuristic.evaluate(node.state)
    
        # This is a generator for the PriorityQueue we need.
        def queue_generator():
            return PriorityQueue(evaluator)

        # Use a graph search with a minimum priority queue to conduct the search.
        min_soultion=infinity
        soultionC=[]
        timeC=infinity
        for i in xrange(1,20):
            k=i*0.05
            start = time.clock()
            soultion=AStarWeightHelp(k,self.limit).find(problem_state,heuristic)
            run_time = time.clock() - start
            self.limit-=run_time
            if(type(soultion) is IntType):
                break;
            if(len(soultion) == min_soultion and run_time<timeC):
                soultionC=soultion
                min_soultion=len(soultion)
                timeC=run_time
            if(len(soultion)<min_soultion):
                soultionC=soultion
                min_soultion=len(soultion)
                timeC=run_time
            global finished
            if( finished ==1 or ((self.limit) <= 0.001)):
                break
        return soultionC

class AStarWeightHelp (SearchAlgorithm):
    '''
    Implementation of the A* search algorithm for the Problem.
    It may also take a maximum depth at which to stop, if needed.
    '''

    def __init__(self, weight,limit_time = infinity, max_depth=infinity):
        '''
        Constructs the A* search.
        Optionally, a maximum depth may be provided at which to stop looking for
        the goal state.
        
        Given weight = 1/2, this algorithm is idnetical to A*
        '''
        self.limit=limit_time
        self.max_depth = max_depth
        if weight < 0 or weight > 1:
            raise ValueError()
        self.weight = weight

    def find(self, problem_state, heuristic):
        '''
        A* search is best-first graph search with f(n) = g(n)+h(n).
        You need to specify the h function when you call astar_search.
        Uses the pathmax trick: f(n) = max(f(n), g(n)+h(n)).

        @param problem_state: The initial state to start the search from.
        @param heuristic: A heuristic function that scores the Problem states.
        '''
        # This is the node evaluation function for the given heuristic.
        def evaluator(node):
            return self.weight*node.path_cost + (1-self.weight)*heuristic.evaluate(node.state)
    
        # This is a generator for the PriorityQueue we need.
        def queue_generator():
            return PriorityQueue(evaluator)

        # Use a graph search with a minimum priority queue to conduct the search.
        search = GraphSearch(queue_generator,self.limit, self.max_depth)
        return search.find(problem_state)
class IterativeDeepeningAStar (SearchAlgorithm):
    '''
    Implementation of the A* search algorithm for the Problem.
    This implementation limits the depth of each of the searches performed by
    the AStar algorithm, and iteratively increases this depth up to an optional
    limit that is supplied at construction (or to infinity if unspecified).
    '''

    def __init__(self, max_depth=sys.maxint):
        '''
        Constructs the search algorithm with an optional max depth.
        '''
        self.max_depth = max_depth

    def find(self, problem_state, heuristic):
        '''
        A* search is best-first graph search with f(n) = g(n)+h(n).
        You need to specify the h function when you call astar_search.
        Uses the pathmax trick: f(n) = max(f(n), g(n)+h(n)).
        
        @param problem_state: The initial state to start the search from.
        @param heuristic: A heuristic function that scores the Problem states.
        '''
        for depth in xrange(1, self.max_depth):
            search = AStarWeight(depth)
            solution = search.find(problem_state, heuristic)
            if solution:
                return solution
        return None
