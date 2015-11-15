from Heuristcs import Heuristic_Temp_Fixed6, Heuristic_Temp_Fixed7 
from astar_weight import AStarWeight
from problem_agent import ProblemAgent
from algorithm import Heuristic
from utils import infinity




class TestAgentAStarWeight(ProblemAgent):
    def solve(self, problem_state, time_limit,flag=0):
        return AStarWeight(time_limit).find(problem_state, Heuristic_Temp_Fixed6())
        