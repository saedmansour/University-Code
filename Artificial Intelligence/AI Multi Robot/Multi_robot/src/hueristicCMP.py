from search.problem_instances import ProblemInstances
from multi_robot_problem import MultiRobotState
from search.TestAgent import *
from search.utils import infinity
from pylab import *
from matplotlib.pyplot import *
import matplotlib.pyplot as plt
from scipy.stats import wilcoxon
import time


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
    
def CompareHeuristc(h6, h7,time_limit, problem_level, algo):

    resultsDG=dict.fromkeys(time_limit)
    resultsDW=dict.fromkeys(time_limit)
    resultsDE=dict.fromkeys(time_limit)
    
    if algo == "Greedy":
		for t in time_limit:
			tempResult=CompareHeuristcHelp(h7[t],h6[t])
			resultsDG[t]=tempResult[0]
			resultsDW[t]=tempResult[1]
			resultsDE[t]=tempResult[2]
		DrawGWEH(resultsDG,resultsDW,resultsDE,"Greedy", problem_level)
    else:
		for t in time_limit:
			tempResult=CompareHeuristcHelp(h7[t],h6[t])
			resultsDG[t]=tempResult[0]
			resultsDW[t]=tempResult[1]
			resultsDE[t]=tempResult[2]
		DrawGWEH(resultsDG,resultsDW,resultsDE,"Weight", problem_level)

#G = 6, #W = 7	
def CompareHeuristcHelp(resultsListW, resultsListG):
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
    return finalResult       


#----- MEDIUM
h6={}
h7={}
h7[5]=[inf, 37, 36, 55, 14, 42, 17, 20, inf, 31, inf, 15, 196, 49, 7, 9, 2, 129, inf, 73, 78, 65, inf, 89, 3, 43, inf, 31, 51, inf, 15, 11, inf, 49, 61, 35, 41, 72, 24, 16, inf, inf, inf, 24, inf, inf, 13, inf, 13, 14, 7, inf, inf, inf, inf, 85, 90, inf, inf, 45]
h6[5]=[inf, 44, inf, inf, inf, inf, 63, inf, inf, inf, inf, inf, 196, inf, inf, 10, 2, 129, inf, 73, inf, 69, inf, inf, 3, 30, inf, 46, inf, inf, 8, inf, inf, inf, inf, inf, 41, inf, 24, 27, inf, inf, inf, 25, inf, inf, inf, inf, 28, 17, 14, inf, inf, inf, inf, inf, 90, inf, inf, inf] 
h7[8]=[inf, 37, 36, 55, 14, 42, 17, 20, inf, 31, inf, 15, 196, 49, 7, 9, 2, 129, inf, 73, inf, 84, inf, inf, 3, 43, inf, 31, 51, inf, 15, 11, inf, 49, 61, 35, 41, 72, 24, 16, inf, inf, inf, 24, inf, 39, 13, 4, 13, 14, 7, inf, inf, inf, inf, 73, 90, inf, 9, 45]
h6[8]=[inf, 30, inf, inf, inf, inf, 28, 39, inf, 26, inf, inf, 196, inf, 16, 5, 2, 129, inf, 73, 104, inf, inf, inf, 3, 28, inf, 32, inf, inf, 6, inf, inf, 61, inf, inf, 41, inf, 24, inf, inf, inf, inf, 29, inf, inf, inf, inf, inf, 21, 9, inf, inf, inf, inf, 67, 90, inf, inf, inf] 
h7[15]=[inf, 37, 36, 55, 14, 42, 17, 20, inf, 31, inf, 15, 196, 49, 7, 9, 2, 129, inf, 73, 78, 65, 3, 89, 3, 43, inf, 31, 51, inf, 15, 11, inf, 49, 61, 35, 41, 72, 24, 16, inf, inf, 6, 24, inf, 39, 13, 4, 13, 14, 7, 26, inf, inf, inf, 66, 90, inf, 9, 45] 
h6[15]=[inf, 47, inf, inf, 20, inf, 16, 24, inf, inf, inf, inf, 196, inf, 8, 12, 2, 129, inf, 73, 110, 73, 3, inf, 3, 32, inf, 55, inf, inf, 7, 39, inf, 48, 109, inf, 41, 222, 24, 22, inf, inf, 6, 40, inf, inf, 34, 4, inf, 13, 8, inf, inf, inf, inf, inf, 90, inf, inf, 62]
h7[30]=[inf, 37, 36, 55, 14, 42, 16, 20, 4, 31, 11, 15, 196, 49, 7, 9, 2, 129, inf, 73, 78, 65, 3, 89, 3, 43, 37, 31, 51, 11, 7, 11, inf, 45, 34, 23, 41, 66, 24, 16, inf, inf, 6, 24, inf, 39, 13, 4, 13, 14, 7, 26, inf, inf, inf, 66, 90, 2, 9, 45]
h6[30]=[inf, 48, inf, inf, 22, inf, 18, 22, inf, 31, 9, inf, 196, 40, 9, 8, 2, 129, inf, 73, inf, inf, 3, 185, 3, 29, inf, 38, 52, inf, 9, 21, inf, 54, 47, 24, 41, 222, 24, 21, inf, inf, 6, 40, inf, inf, 32, 4, 18, 17, 7, inf, inf, inf, inf, 99, 90, 2, 16, 72] 	
CompareHeuristc(h6, h7,[5,8,15,30], "Medium", "Weight")

h6={}
h7={}
h7[5]=[inf, 48, inf, 55, 14, 42, 17, 20, inf, 31, inf, inf, inf, inf, 7, 9, 2, 133, inf, 73, inf, 84, inf, inf, 3, 43, inf, 31, 55, inf, 26, 11, inf, 49, 61, 35, 41, 72, 24, 16, inf, inf, inf, 24, inf, inf, 13, inf, 18, 14, 7, inf, inf, inf, inf, 86, 90, inf, 9, 45]
h6[5]=[inf, 41, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, 196, inf, 9, 17, 4, 133, inf, 73, inf, inf, inf, inf, 3, inf, inf, 33, inf, inf, 9, inf, inf, 79, inf, inf, 43, inf, 24, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, 17, 14, inf, inf, inf, inf, inf, 90, inf, inf, inf]
h7[8]=[inf, 48, 36, 55, 14, 42, 17, 20, inf, 31, inf, 15, 196, 49, 7, 9, 2, 133, inf, 73, 71, 84, inf, inf, 3, 43, inf, 31, 55, inf, 26, 11, inf, 49, 61, 35, 41, 72, 24, 16, inf, inf, 6, 24, inf, 39, 13, 4, 18, 14, 7, inf, inf, inf, inf, 86, 90, inf, 9, 45]
h6[8]=[inf, 41, inf, inf, inf, inf, 47, inf, inf, 31, inf, inf, 196, inf, 35, 11, 2, 133, inf, 73, inf, inf, inf, inf, 3, 36, inf, 50, inf, inf, 9, inf, inf, 50, inf, inf, 41, inf, 24, 29, inf, inf, inf, 23, inf, inf, inf, inf, inf, 27, 8, inf, inf, inf, inf, inf, 90, inf, inf, inf]
h7[15]=[inf, 48, 36, 55, 14, 42, 17, 20, inf, 31, inf, 15, 196, 49, 7, 9, 2, 133, inf, 73, 71, 84, 3, 97, 3, 43, 37, 31, 52, inf, 26, 11, inf, 49, 61, 35, 41, 72, 24, 16, inf, inf, 6, 24, inf, 39, 13, 4, 18, 14, 7, 26, inf, inf, inf, 86, 90, inf, 9, 45]
h6[15]=[inf, 54, inf, inf, inf, inf, 35, 24, inf, inf, inf, inf, 196, inf, 12, 9, 2, 133, inf, 73, inf, inf, 3, inf, 3, 31, inf, 47, inf, inf, 8, 26, inf, inf, inf, 21, 41, inf, 24, 26, inf, inf, 6, 29, inf, inf, 29, 4, inf, 18, 11, inf, inf, inf, inf, inf, 90, inf, 11, inf]
h7[30]=[inf, 44, 36, 55, 14, 42, 17, 20, 4, 31, 11, 15, 196, 49, 7, 9, 2, 129, inf, 73, 71, 84, 3, 97, 3, 43, 37, 31, 51, 11, 15, 11, inf, 49, 61, 35, 41, 72, 24, 16, inf, inf, 6, 24, inf, 39, 13, 4, 18, 14, 7, 26, inf, inf, inf, 86, 90, 2, 9, 45]
h6[30]=[inf, 67, inf, 61, 16, inf, 28, 30, inf, inf, 12, 55, 196, 34, 7, 12, 2, 129, inf, 73, 60, 94, 3, inf, 3, 37, inf, 53, 104, 11, 8, 24, inf, 57, inf, 29, 41, inf, 24, 22, inf, inf, 6, 28, inf, inf, 45, 4, 48, 18, 8, inf, inf, inf, inf, 73, 90, 2, 10, 63]
CompareHeuristc(h6, h7,[5,8,15,30], "Medium", "Greedy")


#----- HARD
#WEIGHT
h6={}
h7={}
h6[5]=[63, 57, 61, 63, 58, 29, inf, inf, inf, inf, inf, 38, inf, inf, inf, 54, 32, inf, inf, 49, inf, inf, 62, 62, 74, inf, 58, 58, 49, 60, 67, 75, inf, 47, 133, 161]
h6[8]=[63, 61, inf, inf, 66, inf, 35, inf, inf, inf, inf, 38, inf, inf, inf, 62, 32, inf, inf, 49, inf, inf, 62, 62, 51, inf, 58, 58, 51, inf, 63, 69, inf, inf, 131, 139]
h6[15]=[61, 63, 63, 59, 69, 25, inf, inf, inf, inf, inf, 38, inf, inf, inf, 30, 32, inf, inf, 49, inf, inf, 62, 62, 51, 60, 58, 58, 51, inf, 63, 69, inf, 46, 125, 139]
h6[30]=[55, 53, 58, 51, 63, 33, 31, 24, inf, inf, inf, 38, inf, inf, inf, 56, 32, 70, inf, 49, 53, 61, 62, 62, 53, 83, 58, 58, 49, 54, 63, 69, inf, 41, 121, 131]
h7[5]=[inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, 38, inf, inf, inf, inf, 32, inf, inf, 49, inf, inf, 62, 62, inf, inf, 58, 58, inf, inf, 67, 73, inf, inf, 133, 151] 
h7[8]=[inf, inf, inf, inf, inf, 27, 29, 22, inf, inf, inf, 38, inf, inf, inf, inf, 32, inf, inf, 49, inf, inf, 62, 62, inf, inf, 58, 58, inf, inf, 65, 73, inf, inf, 133, 161] 
h7[15]=[inf, inf, inf, inf, inf, 27, 29, 22, inf, inf, inf, 38, inf, inf, inf, inf, 32, 39, inf, 49, inf, inf, 62, 62, inf, inf, 58, 58, inf, inf, 63, 69, inf, inf, 131, 137]
h7[30]=[inf, inf, inf, inf, inf, 27, 29, 22, inf, inf, inf, 38, inf, inf, inf, inf, 32, 39, inf, 49, inf, inf, 62, 62, inf, inf, 58, 58, inf, inf, 63, 69, 60, inf, 121, 135] 
CompareHeuristc(h6, h7,[5,8,15,30], "Hard", "Weight")

#GREEDY
h6={}
h7={}
h6[5]=[inf, 65, inf, inf, 58, inf, inf, inf, inf, inf, inf, 48, inf, inf, inf, 62, 32, inf, inf, 51, inf, inf, 62, 62, 51, 63, 58, 58, inf, inf, 73, 95, inf, 45, 143, 161]
h6[8]=[65, 53, 57, 57, 69, 19, inf, inf, inf, inf, inf, 48, inf, inf, inf, 62, 32, inf, inf, 51, inf, inf, 62, 62, 50, 51, 58, 58, 56, inf, 73, 95, inf, 48, 143, 161]
h6[15]=[57, 62, 63, 54, 74, inf, inf, inf, inf, inf, inf, 48, inf, inf, inf, 32, 32, inf, inf, 51, 54, inf, 62, 62, 57, 91, 58, 58, 50, 57, 73, 95, inf, 49, 143, 161]
h6[30]=[59, 57, 57, 54, 66, 29, 73, 25, inf, inf, inf, 48, inf, inf, inf, 62, 32, 52, inf, 51, inf, 63, 62, 62, 52, inf, 58, 58, 52, 53, 73, 95, inf, inf, 143, 161]
h7[5]=[inf, inf, inf, inf, inf, 27, 29, inf, inf, inf, inf, 44, inf, inf, inf, 100, 32, inf, inf, 51, inf, inf, 63, 69, inf, inf, 59, 65, inf, inf, 73, 95, inf, inf, 145, 162]
h7[8]=[inf, inf, inf, inf, inf, 27, 29, 22, inf, inf, inf, 40, inf, inf, inf, 100, 32, inf, inf, 51, inf, inf, 62, 68, inf, inf, 58, 64, inf, inf, 73, 95, inf, inf, 145, 162]
h7[15]=[inf, inf, inf, inf, inf, 27, 29, 22, inf, inf, inf, 40, inf, inf, inf, 100, 32, inf, inf, 51, inf, inf, 62, 68, inf, inf, 58, 64, inf, inf, 73, 95, inf, inf, 145, 162]
h7[30]=[inf, inf, inf, inf, inf, 27, 29, 22, inf, inf, inf, 38, inf, inf, inf, 100, 32, inf, inf, 51, inf, inf, 62, 68, inf, inf, 58, 64, inf, inf, 73, 95, inf, inf, 145, 162]
CompareHeuristc(h6, h7,[5,8,15,30], "Hard", "Greedy")



#----- EASY
h6={}
h7={}
h7[4]=[30, 14, inf, 96, 92, 92, inf, 36, 7, 19, inf, 4, 25, 131, 20, 22, inf, 8, 5, 34, 13, inf, inf, 81, 36, 14, 78, 20, 32, inf, 59, inf, inf, 16, inf, 83, inf, inf, 61, inf, inf, 91, 11, 18, 12, 68, 56, 91, 26, 6, 27, 160, 32, 17, 17, 101, 53, 20, 17, 24] 
h7[6]=[30, 14, inf, 96, 92, 92, inf, 36, 7, 19, inf, 4, 25, 131, 20, 22, inf, 8, 5, 34, 13, inf, inf, 81, 36, 14, 78, 20, 32, inf, 59, inf, inf, 16, inf, 83, inf, inf, 61, inf, inf, 91, 11, 18, 12, 68, 56, 91, inf, inf, 27, 160, 32, 17, inf, 101, 53, 20, 17, 24] 
h7[8]=[30, 14, 36, 96, 92, 92, inf, 36, 7, 19, 45, 4, 25, 131, 20, 22, inf, 8, 5, 34, 13, inf, inf, 81, 36, 14, 78, 20, inf, inf, 59, inf, inf, 16, inf, 83, inf, inf, 61, inf, inf, 91, 11, 18, 12, 68, 56, 91, 26, inf, 27, 160, 32, 17, 17, 101, 53, 20, 17, 24]
h7[13]=[30, 14, 36, 96, 92, 92, inf, 36, 7, 19, 45, 4, 25, 131, 20, 22, inf, 8, 5, 34, 13, inf, 19, 81, 36, 14, 78, 20, 32, 12, 59, inf, inf, 16, inf, 83, inf, inf, 61, inf, inf, 91, 11, 18, 12, 68, 56, 91, 26, 6, 27, 160, 32, 17, 17, 101, 47, 20, 17, 24]
h7[15]=[30, 14, 36, 96, 92, 92, inf, 36, 7, 19, 45, 4, 25, 131, 20, 22, inf, 8, 5, 34, 13, inf, inf, 81, 36, 14, 78, 20, 32, 12, 59, 22, 59, 16, 30, 83, 75, inf, 61, inf, 18, 91, 11, 18, 12, 68, 56, 91, 26, 6, 27, 160, 32, 17, 17, 101, 53, 20, 17, 24]
h7[17]=[30, 14, 36, 96, 92, 92, inf, 36, 7, 19, 45, 4, 25, 131, 20, 22, inf, 8, 5, 34, 13, inf, 19, 81, 36, 14, 78, 20, 32, inf, 59, inf, inf, 16, 30, 83, inf, inf, 61, inf, 18, 91, 11, 18, 12, 68, 56, 91, 26, 6, 27, 160, 32, 17, 17, 101, 47, 20, 17, 24]
h6[4]=[26, 12, 23, 96, 78, 92, inf, 36, 7, 19, inf, 4, 25, 131, 16, 22, inf, 8, 5, 34, 12, inf, inf, 81, 34, 13, 78, 19, 31, inf, 59, inf, 34, 12, inf, 83, inf, inf, 61, inf, inf, 91, 11, 18, 11, 68, 38, 91, 26, 6, 26, 160, 23, 17, 17, 101, 53, 12, 17, 15] 
h6[6]=[27, 12, 23, 96, 94, 92, inf, 30, 7, 19, inf, 4, 25, 131, 16, 20, inf, 8, 5, 34, 12, inf, 17, 81, 32, 13, 78, 19, 26, inf, 59, inf, 62, 12, 37, 83, 54, inf, 59, inf, inf, 91, 11, 18, 14, 68, 37, 91, 26, 6, 24, 160, 23, 17, 17, 101, 53, 12, 17, 14] 
h6[8]=[27, 12, 36, 96, 82, 92, inf, 30, 7, 19, 45, 4, 25, 131, 16, 21, inf, 8, 5, 34, 12, inf, inf, 81, 35, 13, 78, 19, 32, 13, 59, inf, 34, 11, 37, 83, 71, inf, 59, inf, inf, 91, 11, 18, 11, 68, 38, 91, 23, 6, 24, 160, 25, 17, 17, 101, 47, 14, 17, 15]
h6[13]=[23, 12, 23, 96, 82, 92, inf, 30, 7, 19, 49, 4, 25, 131, 16, 20, 27, 8, 5, 34, 12, inf, 17, 81, 35, 13, 78, 19, 26, 13, 59, 22, 44, 11, 26, 83, 41, inf, 60, inf, 23, 91, 11, 18, 11, 68, 38, 91, 23, 6, 26, 160, 23, 17, 17, 101, 47, 12, 17, 15] 
h6[15]=[26, 12, 22, 96, 79, 92, inf, 30, 7, 19, 49, 4, 25, 131, 16, 21, 27, 8, 5, 34, 12, inf, 17, 81, 32, 14, 78, 19, 26, 13, 59, 21, 34, 12, 30, 83, 47, 22, 60, inf, 23, 91, 11, 18, 11, 68, 38, 91, 23, 6, 24, 160, 23, 17, 17, 101, 47, 12, 17, 15]
h6[17]=[26, 12, 22, 96, 77, 92, 28, 30, 7, 19, 46, 4, 25, 131, 16, 20, inf, 8, 5, 34, 12, inf, 17, 81, 32, 13, 78, 19, 25, 17, 59, 22, 44, 11, 26, 83, 41, 22, 60, inf, 19, 91, 11, 18, 11, 68, 38, 91, 23, 6, 24, 160, 23, 17, 17, 101, 47, 12, 17, 15] 
CompareHeuristc(h6, h7,[4,6,8,13,15,17], "Easy", "Weight")

h6={}
h7={}
h7[4]=[30, 14, inf, 96, 92, 92, inf, 36, 7, 19, inf, 4, 25, 131, 20, 22, inf, 8, 5, 34, 13, inf, inf, 81, 36, 14, 78, 20, inf, inf, 59, inf, inf, 16, inf, 83, inf, inf, 61, inf, inf, 91, 11, 18, 12, 68, 56, 91, inf, inf, 27, 160, 32, 17, 17, 101, 53, 20, 17, 24]
h7[6]=[30, inf, inf, 96, inf, 92, inf, 36, 7, inf, inf, 4, inf, 131, 20, 22, inf, 8, 5, 34, 13, inf, inf, 81, 36, 14, 78, 20, inf, inf, 59, inf, inf, 16, inf, 83, inf, inf, 61, inf, inf, 91, 11, 18, 12, 68, 56, 91, 26, 6, 27, 160, 32, 17, 17, 101, 53, 20, 17, 24]
h7[8]=[30, 14, 36, 96, 92, 92, inf, 36, 7, 19, 45, 4, 25, 131, 20, 22, inf, 8, 5, 34, 13, inf, 19, 81, 36, 14, 78, 20, 32, 12, 59, inf, 59, 16, 30, 83, inf, inf, 61, inf, inf, 91, 11, 18, 12, 68, 56, 91, 26, 6, 27, 160, 32, 17, 17, 101, 53, 20, 17, 24]
h7[13]=[30, 14, 36, 96, 92, 92, inf, 36, 7, 19, 45, 4, 25, 131, 20, 22, inf, 8, 5, 34, 13, inf, 19, 81, 36, 14, 78, 20, 32, 12, 59, 22, 59, 16, 30, 83, 75, inf, 61, inf, inf, 91, 11, 18, 12, 68, 56, 91, 26, 6, 27, 160, 32, 17, 17, 101, 53, 20, 17, 24]
h7[15]=[30, 14, 36, 96, 92, 92, inf, 36, 7, 19, 45, 4, 25, 131, 20, 22, inf, 8, 5, 34, 13, inf, 19, 81, 36, 14, 78, 20, 32, inf, 59, inf, inf, 16, 30, 83, inf, inf, 61, inf, 18, 91, 11, 18, 12, 68, 56, 91, 26, 6, 27, 160, 32, 17, 17, 101, 53, 20, 17, 24]
h7[17]=[30, 14, 36, 96, 92, 92, inf, 36, 7, 19, 45, 4, 25, 131, 20, 22, inf, 8, 5, 34, 13, inf, 19, 81, 36, 14, 78, 20, 32, 12, 59, 22, 59, 16, 30, 83, inf, inf, 61, inf, inf, 91, 11, 18, 12, 68, 56, 91, 26, 6, 27, 160, 32, 17, 17, 101, 53, 20, 17, 24]
h6[4]=[30, 12, 23, 96, 78, 92, inf, 34, 7, 19, inf, 4, 25, 131, 16, 20, inf, 8, 5, 34, 12, inf, inf, 81, 35, 13, 78, 19, 27, inf, 59, inf, inf, 12, inf, 83, inf, inf, 60, inf, inf, 91, 11, 18, 14, 68, 45, 91, 27, 6, 25, 160, 25, 17, 17, 101, 53, 13, 17, 15]
h6[6]=[27, 12, 24, 96, 81, 92, inf, 32, 7, 19, inf, 4, 25, 131, 16, 22, inf, 8, 5, 34, 12, inf, 17, 81, 34, 13, 78, 19, 25, inf, 59, inf, 45, 11, 37, 83, 61, inf, 59, inf, inf, 91, 11, 18, 14, 68, 50, 91, 28, 6, 25, 160, 24, 17, 19, 101, 53, 14, 17, 15]
h6[8]=[23, 12, 24, 96, 82, 92, inf, 34, 7, 19, 47, 4, 25, 131, 16, 21, inf, 8, 5, 34, 12, inf, 17, 81, 32, 13, 78, 19, 26, 13, 59, inf, 32, 11, 30, 83, 54, inf, 61, inf, inf, 91, 11, 18, 11, 68, 38, 91, 27, 6, 25, 160, 24, 17, 17, 101, 53, 14, 17, 15]
h6[13]=[25, 12, 23, 96, 78, 92, inf, 34, 7, 19, 45, 4, 25, 131, 16, 20, 27, 8, 5, 34, 12, inf, 17, 81, 32, 13, 78, 19, 26, 17, 59, 22, 36, 11, 28, 83, 55, 20, 61, inf, 23, 91, 11, 18, 11, 68, 39, 91, 25, 6, 24, 160, 24, 17, 17, 101, 53, 12, 17, 14]
h6[15]=[26, 12, 22, 96, 78, 92, inf, 29, 7, 19, 46, 4, 25, 131, 16, 21, 27, 8, 5, 34, 12, inf, 17, 81, 30, 13, 78, 19, 26, 12, 59, 22, 33, 11, 29, 83, 42, 20, 59, inf, 23, 91, 11, 18, 11, 68, 39, 91, 23, 6, 23, 160, 24, 17, 17, 101, 53, 12, 17, 14]
h6[17]=[23, 12, 23, 96, 80, 92, inf, 32, 7, 19, 45, 4, 25, 131, 16, 21, 27, 8, 5, 34, 12, 34, 17, 81, 31, 13, 78, 19, 26, 14, 59, 22, 39, 11, 26, 83, 45, inf, 60, inf, 19, 91, 11, 18, 11, 68, 37, 91, 23, 6, 24, 160, 24, 17, 17, 101, 53, 16, 17, 15]
CompareHeuristc(h6, h7,[4,6,8,13,15,17], "Easy", "Greedy")


show()