from multi_robot_problem import MultiRobotState
from problem_agent import ProblemAgent
from search.algorithm import Heuristic
from search.best_first import BestFirstGraphSearch
from search.astar import AStar
from search.astar_weight import AStarWeight
from search.astar_and_greedy import AStarAndGreedy

import time




class TestAgent(ProblemAgent):
    def solve(self, problem_state, time_limit):
        #Greedy
        return BestFirstGraphSearch().find(problem_state, CleanHeuristic())
        
        #A*
        #return AStar().find(problem_state, CleanHeuristic())
        
        #A*-weight
        #return AStarWeight(0.999999).find(problem_state, CleanHeuristic())     #the best (for given example)
        #return AStarWeight(0.000001).find(problem_state, CleanHeuristic())     #the worst
        #return AStarWeight(0.5).find(problem_state, CleanHeuristic())          #in between
        #return AStarWeight(1).find(problem_state, CleanHeuristic())
        
        #N-times-A*-then-Greedy  
        #return AStarAndGreedy(10).find(problem_state, CleanHeuristic())
      


class CleanHeuristic(Heuristic):
    def evaluate(self, state):
        return len(state.dirt_locations)


def createProblem():
    # First Problem - Easy
    robots = tuple([(2, 2)])
    
    dirt_locations = set()
    dirt_locations.add((1, 1))
    dirt_locations.add((1, 3))
    dirt_locations.add((3, 1))
    dirt_locations.add((3, 3))
    
    obstacle_locations = set()
    
    return MultiRobotState(5, 5, robots, frozenset(dirt_locations), frozenset(obstacle_locations))


def createProblemB():
    # First Problem - Easy
    #robots = tuple([(2, 2), (0,0), (0,5), (12,12), (13,14), (10,15), (29,29), (39,1)])
    
    robots = tuple([(2, 2)])
    
    '''
    dirt_locations = set()
    dirt_locations.add((1, 1))
    dirt_locations.add((1, 3))
    dirt_locations.add((3, 1))
    dirt_locations.add((3, 3))
    dirt_locations.add((12, 1))
    dirt_locations.add((13, 2))
    dirt_locations.add((14, 3))
    dirt_locations.add((15, 4))
    dirt_locations.add((15, 5))
    dirt_locations.add((15, 6))
    '''
           
    dirt_locations = set()
    dirt_locations.add((1, 1))
    dirt_locations.add((1, 3))
    dirt_locations.add((3, 1))
    dirt_locations.add((3, 3))
    
    
    
    obstacle_locations = set()
    #obstacle_locations.add((14, 1))
    #obstacle_locations.add((14, 2))
    #obstacle_locations.add((14, 4))
    
    return MultiRobotState(40, 40, robots, frozenset(dirt_locations), frozenset(obstacle_locations))






#problem = createProblem()
problem = createProblemB()
print problem

agent = TestAgent()
start = time.clock()
solution = agent.solve(problem, 17)
run_time = time.clock() - start
print 'Solution:', solution
print 'Solution length:', len(solution)
print 'Running time:', run_time
