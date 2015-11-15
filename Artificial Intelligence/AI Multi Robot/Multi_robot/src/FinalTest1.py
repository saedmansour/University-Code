from search.problem_instances import ProblemInstances
from multi_robot_problem import MultiRobotState
from search.TestAgent import *
from search.utils import infinity
from pylab import *
from matplotlib.pyplot import *
import matplotlib.pyplot as plt
from scipy.stats import wilcoxon
import time


def DrawGWE(G,W,E,problem_level,hurestic):
    f = figure()
    keys=G.keys()
    values=G.values()
    myGraph1 = plot(keys,values , 'bo')
    keys=W.keys()
    values=W.values()
    myGraph2 = plot(keys,values , 'gs')
    keys=E.keys()
    values=E.values()
    myGraph3 = plot(keys,values , 'r^')
    plt.axis([-0.1,35,-3,103])
    plt.title("Algorithm Comparison, problem level: " + problem_level + ", Hueristic: " + hurestic)
    legend([myGraph1,myGraph2,myGraph3],["AstarAndGreedy Win","AstarWeight Win","Tie"])
    xlabel("Time limited")
    ylabel("Win Percentage")
    draw()


def CompareAlgo(problem,time_limit, hurestic, problem_level):

    resultsDG=dict.fromkeys(time_limit)
    resultsDW=dict.fromkeys(time_limit)
    resultsDE=dict.fromkeys(time_limit)
    
    if hurestic == "Heuristic 7":
        hueristicNum = 1
    else:
        hueristicNum = 0
    
    for t in xrange(len(time_limit)):
        tempResult=CompareAlgoPerTimeLimit(problem,time_limit[t],hueristicNum) #call with second hureistic
        resultsDG[time_limit[t]]=tempResult[0]
        resultsDW[time_limit[t]]=tempResult[1]
        resultsDE[time_limit[t]]=tempResult[2]
    DrawGWE(resultsDG,resultsDW,resultsDE, problem_level, hurestic)
        
        
    
    
     
def CompareAlgoPerTimeLimit(problem,time_limit,flagH=0):
    #Define the constant      
    NumberOfTheFile=-1
    ResultFiles=open('c:\lala\MyResults'+ str(NumberOfTheFile)+ '.txt','w')
    DetailsFiles=open('c:\lala\MyResultsDetails'+ str(NumberOfTheFile)+ '.txt','w')
    NumberOfTheTests=len(problem)
    LimitedTimeEnd=time_limit+1
    LimitedTimeStart=time_limit
    AlgorithemName=""
    
    #Enable flags
    enableDetails=1
    enableResults=0
    enableGraph=0
    enableAstarWeight=1
    enableAstarAndGreedy=1
    enableHist=0
    
    problems=problem
    #resultsDictionaryW=dict.fromkeys(range(0,MaxSolutionLen))
    #resultsDictionaryG=dict.fromkeys(range(0,MaxSolutionLen))
    resultsListW=[]
    timeListW=[]    
    resultsListG=[]
    timeListG=[]    
    
    
    #AStarWeight
    #Create the N tests with each Test specific time and save the result
    if(enableAstarWeight==1):
        for problemNumber in xrange(0,NumberOfTheTests):
            problem =problems[problemNumber]
            for limitedTime in xrange(LimitedTimeStart,LimitedTimeEnd):
                agent = TestAgentAStarWeight()
                start = time.clock()
                solution = agent.solve(problem,limitedTime,flagH)
                run_time = time.clock() - start
                resultsListW.append(len(solution))
                timeListW.append((limitedTime,run_time))
        
    #AStarAndGreedy
    #Create the N tests with each Test specific time and save the result
    if(enableAstarAndGreedy==1):
        for problemNumber in xrange(0,NumberOfTheTests):
            problem =problems[problemNumber]
            for limitedTime in xrange(LimitedTimeStart,LimitedTimeEnd):
                agent = TestAgentAStarAndGreedy()
                start = time.clock()
                solution = agent.solve(problem,limitedTime,flagH)
                run_time = time.clock() - start
                resultsListG.append(len(solution))
                timeListG.append((limitedTime,run_time))
         
    #Print Details
    if(enableDetails==1):
        DetailsFiles.write("The Details file of  "+str(NumberOfTheFile)+":\n")
        for problemNumber in xrange(0,NumberOfTheTests):
            problem =problems[problemNumber]
            DetailsFiles.write("Problem Number: "+ str(problemNumber))
            DetailsFiles.write("\n" + str(problem) +"\n")
            for i in xrange(0,LimitedTimeEnd-LimitedTimeStart):
                index=i+problemNumber
                DetailsFiles.write("solution length: "+str(resultsListG[index])+","+str(resultsListW[index]) +"\n")
                #DetailsFiles.write("solution time: "+str(timeList[index]) +"\n\n")
            
    #Create Dictionary : Solution length Vs  Number of tests
    if enableHist == 1:
        hist(resultsListG)
    
    if(enableResults==1):
        resultsListG.sort()
        resultsDictionaryG=dict.fromkeys(range(0,resultsListG[len(resultsListG)-1] ))
        for i in xrange(0,resultsListW[len(resultsListG)-1]):
            resultsDictionaryG[i]=0
        prev= resultsList[0]
        count=0
        for i in xrange(0,NumberOfTheTests*(LimitedTimeEnd-LimitedTimeStart)):
            if(prev == resultsListG[i]):
                count=count+1
            else:
                resultsDictionaryG[prev]=count
                count=1
                prev=resultsList[i]
        resultsDictionaryG[prev]=count
        ##### for weight
        resultsListW.sort()
        resultsDictionaryW=dict.fromkeys(range(0,resultsListW[len(resultsListW)-1] ))
        for i in xrange(0,resultsListW[len(resultsListW)-1]):
            resultsDictionaryG[i]=0
        prev= resultsList[0]
        count=0
        for i in xrange(0,NumberOfTheTests*(LimitedTimeEnd-LimitedTimeStart)):
            if(prev == resultsListW[i]):
                count=count+1
            else:
                resultsDictionaryW[prev]=count
                count=1
                prev=resultsList[i]
        resultsDictionaryW[prev]=count
    
    #Print results to result file
        #ResultFiles.write("The result file of "str(NumberOfTheFile)+":\n" +"Greedy\t\tWeight\n")
        for i in xrange(0,MaxSolutionLen):
            ResultFiles.write(str(resultsDictionaryG[i])+"\t\t")
            ResultFiles.write(str(resultsDictionaryw[i])+"\n")
    
    #Draw Graph.........
    if(enableGraph==1):
        keys=resultsDictionary.keys()
        values=resultsDictionary.values()
        myGraph = plot(keys,values , 'bo', keys, values, 'k--', markerfacecolor='green')
        show()
    #
    Gwin=0.0
    Wwin=0.0
    GWwin=0.0
    count=0.0
    for i in xrange(0,len(resultsListG)):
        if(resultsListW[i]==0):
            resultsListW[i]=infinity
        if(resultsListG[i]==0):
            resultsListG[i]=infinity
        if(resultsListG[i]<resultsListW[i]):
            Gwin+=1
        if(resultsListG[i]>resultsListW[i]):
            Wwin+=1
        if(resultsListG[i]==resultsListW[i] and (resultsListG[i]!=infinity or resultsListW[i]!=infinity)  ):
            GWwin+=1

    sum=Gwin+Wwin+GWwin
    sum/=100.0
    
    
    if(sum==0):
        finalResult=(0,0,0)
    else:
        finalResult=(Gwin/sum,Wwin/sum,GWwin/sum)
    
        
    a=wilcoxon(resultsListW,resultsListG)
    print "****\n\nPvalue ="
    print a[1],resultsListW,resultsListG
    print timeListG,timeListW
    print finalResult
    print "^^^^^\n"
    return finalResult
 
 #####################################################################Hure


def DrawGWEH(G,W,E,algo,problem_level):
    figure()
    keys=G.keys()
    values=G.values()
    myGraph1 = plot(keys,values,'go' )
    keys=W.keys()
    values=W.values()
    myGraph2 = plot(keys,values,'rs' )
    keys=E.keys()
    values=E.values()
    myGraph3 = plot(keys,values,'b^')
    plt.axis([-0.1,53,-3,103])
    plt.title("Hueristic Comparison, problem level: " + problem_level + ", Algorithm: " + algo)
    legend([myGraph1,myGraph2,myGraph3], ["Heuristic 6 Win","Heuristic 7 Win","Tie"])
    xlabel("Time limited")
    ylabel("Win Percentage")
    draw()
    
def CompareHeuristc(problem,time_limit, problem_level):

    resultsDG=dict.fromkeys(time_limit)
    resultsDW=dict.fromkeys(time_limit)
    resultsDE=dict.fromkeys(time_limit)
    
    
    for t in xrange(len(time_limit)):
        tempResult=CompareHeuristcHelp(problem,time_limit[t],1)
        resultsDG[time_limit[t]]=tempResult[0]
        resultsDW[time_limit[t]]=tempResult[1]
        resultsDE[time_limit[t]]=tempResult[2]
    DrawGWEH(resultsDG,resultsDW,resultsDE,"Greedy", problem_level)

    for t in xrange(len(time_limit)):
        tempResult=CompareHeuristcHelp(problem,time_limit[t])
        resultsDG[time_limit[t]]=tempResult[0]
        resultsDW[time_limit[t]]=tempResult[1]
        resultsDE[time_limit[t]]=tempResult[2]
    DrawGWEH(resultsDG,resultsDW,resultsDE,"Weight", problem_level)
       
def CompareHeuristcHelp(problem,time_limit,isGreedy=1):
    #Define the constant      
    NumberOfTheFile=-1
    NumberOfTheTests=len(problem)
    LimitedTimeEnd=time_limit+1
    LimitedTimeStart=time_limit
    AlgorithemName=""
    
    #Enable flags
    enableDetails=1
    enableResults=0
    enableGraph=0
    
    problems=problem
    #resultsDictionaryW=dict.fromkeys(range(0,MaxSolutionLen))
    #resultsDictionaryG=dict.fromkeys(range(0,MaxSolutionLen))
    resultsListW=[]
    timeListW=[]    
    resultsListG=[]
    timeListG=[]    
    
    
    #AStarWeight
    #Create the N tests with each Test specific time and save the result
    if not isGreedy:
        for problemNumber in xrange(0,NumberOfTheTests):
            problem =problems[problemNumber]
            for limitedTime in xrange(LimitedTimeStart,LimitedTimeEnd):
                agent = TestAgentAStarWeight()
                start = time.clock()
                solution = agent.solve(problem,limitedTime,0)
                run_time = time.clock() - start
                resultsListG.append(len(solution))
                timeListG.append((limitedTime,run_time))
        for problemNumber in xrange(0,NumberOfTheTests):
            problem =problems[problemNumber]
            for limitedTime in xrange(LimitedTimeStart,LimitedTimeEnd):
                agent = TestAgentAStarWeight()
                start = time.clock()
                solution = agent.solve(problem,limitedTime,1)
                run_time = time.clock() - start
                resultsListW.append(len(solution))
                timeListW.append((limitedTime,run_time))
    #AStarAndGreedy
    #Create the N tests with each Test specific time and save the result
    else:
        for problemNumber in xrange(0,NumberOfTheTests):
            problem =problems[problemNumber]
            for limitedTime in xrange(LimitedTimeStart,LimitedTimeEnd):
                agent = TestAgentAStarAndGreedy()
                start = time.clock()
                solution = agent.solve(problem,limitedTime,0)
                run_time = time.clock() - start
                resultsListG.append(len(solution))
                timeListG.append((limitedTime,run_time))
                
        for problemNumber in xrange(0,NumberOfTheTests):
            problem =problems[problemNumber]
            for limitedTime in xrange(LimitedTimeStart,LimitedTimeEnd):
                agent = TestAgentAStarAndGreedy()
                start = time.clock()
                solution = agent.solve(problem,limitedTime,1)
                run_time = time.clock() - start
                resultsListW.append(len(solution))
                timeListW.append((limitedTime,run_time))
                #DetailsFiles.write("solution time: "+str(timeList[index]) +"\n\n")
    
    Gwin=0.0
    Wwin=0.0
    GWwin=0.0
    count=0.0
    for i in xrange(0,len(resultsListG)):
        if(resultsListW[i]==0):
            resultsListW[i]=infinity
        if(resultsListG[i]==0):
            resultsListG[i]=infinity
        if(resultsListG[i]<resultsListW[i]):
            Gwin+=1
        if(resultsListG[i]>resultsListW[i]):
            Wwin+=1
        if(resultsListG[i]==resultsListW[i] and (resultsListG[i]!=infinity or resultsListW[i]!=infinity)  ):
            GWwin+=1
    sum=Gwin+Wwin+GWwin
    sum/=100.0
    
        
    if(sum==0):
        finalResult=(0,0,0)
    else:
        finalResult=(Gwin/sum,Wwin/sum,GWwin/sum)
    
        
    a=wilcoxon(resultsListW,resultsListG)
    print "****\n\nPvalue ="
    print a[1],resultsListW,resultsListG
    print timeListG,timeListW
    print finalResult
    print "^^^^^\n"
    return finalResult       






timeList = [4,6,8,13,15,17]
n = 0
m = 60

#TESTS
#Easy cmp alg


problems=ProblemInstances().getEasy()
startEasy=time.clock()
CompareAlgo(problems.values()[n:m],timeList, "Heuristic 7", "Easy")
endEasy=time.clock()-startEasy
print "the easy take: "+str(abs(endEasy))+" time"

'''
#Med cmp alg
start=time.clock()
problems=ProblemInstances().getMedium()
CompareAlgo(problems.values()[n:m],timeList, "Heuristic 7", "Medium")
end=time.clock()-start
print "the easy take: "+str(abs(end))+" time"
'''
'''
#Hard cmp alg
problems=ProblemInstances().getHard()
CompareAlgo(problems.values()[n:36],timeList, "Heuristic 7", "Hard")
'''
'''
#HEURISTIC CMP

#Easy
problems=ProblemInstances().getEasy()
CompareHeuristc(problems.values()[n:m],timeList,"Easy")

#Med
problems=ProblemInstances().getMedium()
CompareHeuristc(problems.values()[n:m],timeList, "Medium")

#Hard
problems=ProblemInstances().getHard()
CompareHeuristc(problems.values()[n:m],timeList, "Hard")

'''
show()

