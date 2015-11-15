from multi_robot_problem import MultiRobotState
from problem_agent import ProblemAgent
from search.algorithm import Heuristic
from search.best_first import BestFirstGraphSearch
from search.astar import AStar
from search.astar_weight import AStarWeight
from search.astar_and_greedy import AStarAndGreedy
import time
from search.Heuristcs import Heuristic_RobotsFromGarbage,Heuristic_Temp_Fixed6,Heuristic_Temp_Fixed6 ,Heuristic_Temp_Fixed1,Heuristic_Temp_Fixed5 ,Heuristic_Temp ,Heuristic_max, Heuristic_GarbagesFromRobot, Heuristic_alpha, Heuristic_Temp_Fixed
#from search.GetProblems import EasyProblems
from search.EasyProblems import EasyProblems

from search.utils import infinity
from pylab import *

class TestAgent(ProblemAgent):
    def solve(self, problem_state, time_limit):
        return AStar().find(problem_state, Heuristic_Temp_Fixed6())

class TestAgentAStarWeight(ProblemAgent):
    def solve(self, problem_state, time_limit):
        return AStarWeight(time_limit).find(problem_state, Heuristic_Temp_Fixed6())

class TestAgentAStarAndGreedy(ProblemAgent):
    def solve(self, problem_state, time_limit):
        return AStarAndGreedy(time_limit).find(problem_state, Heuristic_Temp_Fixed6())     

class CleanHeuristic(Heuristic):
    def evaluate(self, state):
        return len(state.dirt_locations)


    problems=EasyProblems().getProblems()
############################## create 1 starweight
    print "start"
    #f=open('C:\Users\habasi\Desktop\hw1_ver1','w')
    f=open('c:\lala\hasan1.txt','w')
    g=open('c:\lala\hasan2.txt','w')
    N=100
    T=20
    enable=0
    ''' 
   f.write( "AStarWeight \n")
    for i in xrange(0,N):
        if(enable == 0):
            break
        f.write("Test Number:" + str(i)+"\n")
        for j in xrange(5,T):
            problem =problems[i]
            agent = TestAgentAStarWeight()
            start = time.clock()
            solution = agent.solve(problem,j)
            run_time = time.clock() - start
            
            f.write('*********************************************************************************\n')
            f.write('limited time: '+  str(j))
            f.write("\nRunning time: " + str(run_time) +'\n' 'Solution length:' + str(len(solution)) +"\n" )
            f.write("Solution: "  + str(solution) + "\n")
            f.write("problem: "  + "\n" + str(problem) + "\n" )
            f.write('*********************************************************************************\n')
            
            
############################## create 2 stargreedy 
    f.close()
    f=open('c:\lala\hasan.txt','w') 
    f.write( "AStarANdGreedy \n")
    for i in xrange(0,N):
        if(enable == 0):
            break
        f.write("Test Number:" + str(i)+"\n")
        for j in xrange(5,T):
            problem =problems[i]
            agent = TestAgentAStarAndGreedy()
            start = time.clock()
            solution = agent.solve(problem,j)
            run_time = time.clock() - start
            
            f.write('*********************************************************************************\n')
            f.write('limited time: '+  str(j))
            f.write("\nRunning time: " + str(run_time) +'\n' 'Solution length:' + str(len(solution)) +"\n" )
            f.write("Solution: "  + str(solution) + "\n")
            f.write("problem: "  + "\n" + str(problem) + "\n" )
            f.write('*********************************************************************************\n')
    
    '''
    '''
    g.write("number of test\t|\t\t\ttime limited\n")
    g.write("----------------------------------------------------------\n")
    g.write("\t\t|")
    for i in xrange (2,4):
        g.write(str(i)+"\t\t|")
    g.write("\n----------------------------------------------------------\n")
    for i in xrange(0,N):
        g.write(str(i)+"\t\t")
        problem =problems[i]
        for j in xrange(5,T):
            agent = TestAgentAStarWeight()
            start = time.clock()
            solution = agent.solve(problem,j)
            run_time = time.clock() - start
            agent2 = TestAgentAStarAndGreedy()
            start= time.clock()
            solution2 = agent2.solve(problem,j)
            run_time2 = time.clock() - start
            a=set()
            a.add((len(solution),len(solution2)))
            temp=min(a)
            g.write("|"+str(temp[0])+","+str(temp[1])+"\t\t")
        g.write("\n")        
    '''
    d=dict.fromkeys(range(0,120))
    for i in xrange(0,120):
        d[i]=0
    
    d[3]=3
    l = plot(d.keys(), d.values(), 'bo', d.keys(), d.values(), 'k--', markerfacecolor='green')
    show()
    
    g.write( "TestAgentAStarWeight \n")   
    print "#####################"
    a=[]
    N=30
    T=8
    for i in xrange(0,N):
       # g.write(str(i)+"\t\t")
        problem =problems[i]
        for j in xrange(7,T):
            agent = TestAgentAStarWeight()
            start = time.clock()
            solution = agent.solve(problem,j)
            run_time = time.clock() - start
            a.append(len(solution))
    a.sort()
    g.write(str(a)+"\n")
    d=dict.fromkeys(range(0,120))
    prev=a[0]
    count =0
    for i in xrange(0,N*(T-7)):
        if(prev == a[i]):
            count=count+1
        else:
            d[prev]=count
            count=1
            prev=a[i]
    d[prev]=count
    for i in xrange(0,120):
        g.write(str(i)+":"+str(d[i])+"\n")
    l = plot(d.keys(), d.values(), 'bo', d.keys(), d.values(), 'k--', markerfacecolor='green')
    show()
    '''
    for i in xrange(0,1):
        g.write("Test Number:" + str(i)+"\n ********\n")
        problem =problems[i]
        g.write("problem: "  + "\n" + str(problem) + "\n" )
        for j in xrange(5,T):
            
            agent = TestAgentAStarWeight()
            start = time.clock()
            solution = agent.solve(problem,j)
            run_time = time.clock() - start
            agent2 = TestAgentAStarAndGreedy()
            start= time.clock()
            solution2 = agent2.solve(problem,j)
            run_time2 = time.clock() - start
            
            g.write( "AStarWeight\t\t\t\tAStarandGreedy \n")        
            g.write('limited time: '+  str(j)) 
            g.write('\t\t\t\ttlimited time: '+  str(j) + "\n") 
            
            g.write("Running time: " + str(run_time) )
            g.write("\t\tRunning time: " + str(run_time2) +'\n' )
            
            g.write('Solution length:' + str(len(solution)) )
            g.write('\t\t\ttSolution length:' + str(len(solution2)) +"\n" )
            g.write('************************\n\n\n')
            
    print "finished"
    f.close()
    '''