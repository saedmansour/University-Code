from search.best_first import BestFirstGraphSearch
from search.astar_and_greedy import AStarAndGreedy
from search.Heuristcs import Heuristic_Temp_Fixed6, Heuristic_Temp_Fixed7 
from search.astar_weight import AStarWeight
from problem_agent import ProblemAgent
from search.algorithm import Heuristic
from search.utils import infinity
from search.astar import AStar



class TestAgentAStarWeight(ProblemAgent):
    def solve(self, problem_state, time_limit,flag=0):
        return AStarWeight(time_limit).find(problem_state, Heuristic_Temp_Fixed6())
        