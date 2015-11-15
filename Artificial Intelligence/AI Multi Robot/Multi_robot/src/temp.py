'''
Created on May 5, 2011

@author: habasi
'''
from multi_robot_problem import *
from search.problems_easy import *
from search.problems_hard import *
from search.problems_medium import *
from search.ProblemsGenrators import *

'''
ResultFiles=open('c:\lala\Mytemp.txt','w')
ResultFiles.write("easy\n")
EasyProblems().printALL(ResultFiles)
ResultFiles.write("\n\n**************medium\n")
MediumProblems().printALL(ResultFiles)
ResultFiles.write("\n\n**************hard\n")
HardProblems().printALL(ResultFiles)
ResultFiles.write("\n\n\n myeasy\n")
EasyProblems1().printALL(ResultFiles)
'''
problem={}
m=18
n=12
Aset=set([(m/2+1,n/2-1),(m/2+7,n/2+1),(m/2+8,n/2-1) ])
Bset=set([(m/2,n/2),(m/2-4,n/2),(m/2-7,n/2),(m/2-5,n/2),(m/2,n/2-5),(m/2,n/2-6),(m/2,n/2-1),(m/2,n/2-2),(m/2,n/2-3),(m/2,n/2+1),(m/2,n/2+2),(m/2,n/2+3),(m/2,n/2+4),(m/2-1,n/2),(m/2-2,n/2),(m/2-3,n/2),(m/2-1,n/2),(m/2-2,n/2),(m/2+3,n/2),(m/2+2,n/2),(m/2+3,n/2),(m/2+5,n/2),(m/2+1,n/2),(m/2+6,n/2),(m/2+7,n/2),(m/2+4,n/2),(m/2+8,n/2)   ])            
gtuple=tuple([(m/2+3,n/2+3)])
problem[0] = MultiRobotState(m,n,gtuple,frozenset(Aset),frozenset(Bset))
gtuple=tuple([(m/2+3,n/2+3),(m/2+1,n/2+1)])
problem[1] = MultiRobotState(m,n,gtuple,frozenset(Aset),frozenset(Bset))
gtuple=tuple([(m/2+3,n/2+3),(m/2+1,n/2+1),(m/2+5,n/2+1)])
problem[2] = MultiRobotState(m,n,gtuple,frozenset(Aset),frozenset(Bset))

m=22
n=16
Aset=set([(m/2,0),(m/2,n-1) ])
#Bset=set([(m/2,n/2),(m/2-4,n/2),(m/2-7,n/2),(m/2-5,n/2),(m/2,n/2-5),(m/2,n/2-6),(m/2,n/2-1),(m/2,n/2-2),(m/2,n/2-3),(m/2,n/2+1),(m/2,n/2+2),(m/2,n/2+3),(m/2,n/2+4),(m/2-1,n/2),(m/2-2,n/2),(m/2-3,n/2),(m/2-1,n/2),(m/2-2,n/2),(m/2+3,n/2),(m/2+2,n/2),(m/2+3,n/2),(m/2+5,n/2),(m/2+1,n/2),(m/2+6,n/2),(m/2+7,n/2),(m/2+4,n/2),(m/2+8,n/2)   ])            
Bset1=set([ (m/2-10,n/2),(m/2-9,n/2),(m/2-8,n/2-1),(m/2-7,n/2-1),(m/2-6,n/2-2),(m/2-5,n/2-2),(m/2-4,n/2-3),(m/2-3,n/2-3),(m/2-2,n/2-4),(m/2-1,n/2-4) ,(m/2,n/2-3),(m/2+1,n/2-3),(m/2+2,n/2-2),(m/2+3,n/2-2),(m/2+4,n/2-1),(m/2+5,n/2-1),(m/2+7,n/2),(m/2+6,n/2),(m/2+8,n/2)   ])
Bset2=set([ (m/2+8,n/2+2),(m/2+7,n/2+2),(m/2+6,n/2+2),(m/2+5,n/2+3),(m/2+4,n/2+3),(m/2+3,n/2+4),(m/2+2,n/2+4),(m/2+1,n/2+5),(m/2,n/2+5),(m/2-1,n/2+6),(m/2-2,n/2+6),(m/2-3,n/2+5),(m/2-4,n/2+5),(m/2-5,n/2+4),(m/2-6,n/2+4),(m/2-7,n/2+3),(m/2-8,n/2+3),(m/2-9,n/2+2),(m/2-10,n/2+2) ])
Bset=Bset1.union(Bset2)

gtuple=tuple([(m/2-1,n/2+5)])
problem[3] = MultiRobotState(m,n,gtuple,frozenset(Aset),frozenset(Bset))
gtuple=tuple([(m/2-1,n/2-3)])
problem[4] = MultiRobotState(m,n,gtuple,frozenset(Aset),frozenset(Bset))
gtuple=tuple([(m/2-1,n/2-3),(m/2-1,n/2+5)])
problem[5] = MultiRobotState(m,n,gtuple,frozenset(Aset),frozenset(Bset))
gtuple=tuple([(m/2-1,n/2-3),(m/2-1,n/2+5),(m/2,n/2)])
problem[6] = MultiRobotState(m,n,gtuple,frozenset(Aset),frozenset(Bset))

m=22
n=16
Aset=set([(m/2,0),(m/2,n-1) ])
#Bset=set([(m/2,n/2),(m/2-4,n/2),(m/2-7,n/2),(m/2-5,n/2),(m/2,n/2-5),(m/2,n/2-6),(m/2,n/2-1),(m/2,n/2-2),(m/2,n/2-3),(m/2,n/2+1),(m/2,n/2+2),(m/2,n/2+3),(m/2,n/2+4),(m/2-1,n/2),(m/2-2,n/2),(m/2-3,n/2),(m/2-1,n/2),(m/2-2,n/2),(m/2+3,n/2),(m/2+2,n/2),(m/2+3,n/2),(m/2+5,n/2),(m/2+1,n/2),(m/2+6,n/2),(m/2+7,n/2),(m/2+4,n/2),(m/2+8,n/2)   ])            
Bset1=set([ (m/2-9,n/2),(m/2-8,n/2-1),(m/2-7,n/2-1),(m/2-6,n/2-2),(m/2-5,n/2-2),(m/2-4,n/2-3),(m/2-3,n/2-3),(m/2-2,n/2-4),(m/2-1,n/2-4) ,(m/2,n/2-3),(m/2+1,n/2-3),(m/2+2,n/2-2),(m/2+3,n/2-2),(m/2+4,n/2-1),(m/2+5,n/2-1),(m/2+7,n/2),(m/2+6,n/2)   ])
Bset2=set([ (m/2+7,n/2+2),(m/2+6,n/2+2),(m/2+5,n/2+3),(m/2+4,n/2+3),(m/2+3,n/2+4),(m/2+2,n/2+4),(m/2+1,n/2+5),(m/2,n/2+5),(m/2-1,n/2+6),(m/2-2,n/2+6),(m/2-3,n/2+5),(m/2-4,n/2+5),(m/2-5,n/2+4),(m/2-6,n/2+4),(m/2-7,n/2+3),(m/2-8,n/2+3),(m/2-9,n/2+2) ])
Bset=Bset1.union(Bset2)

gtuple=tuple([(m/2-1,n/2+5)])
problem[7] = MultiRobotState(m,n,gtuple,frozenset(Aset),frozenset(Bset))
gtuple=tuple([(m/2-1,n/2-3)])
problem[8] = MultiRobotState(m,n,gtuple,frozenset(Aset),frozenset(Bset))
gtuple=tuple([(m/2-1,n/2-3),(m/2-1,n/2+5)])
problem[9] = MultiRobotState(m,n,gtuple,frozenset(Aset),frozenset(Bset))
gtuple=tuple([(m/2-1,n/2-3),(m/2-1,n/2+5),(m/2,n/2)])
problem[10] = MultiRobotState(m,n,gtuple,frozenset(Aset),frozenset(Bset))

m=22
n=16
Aset=set([(m/2,0),(m/2,n-1),(1,3),(3,n-1) ])
#Bset=set([(m/2,n/2),(m/2-4,n/2),(m/2-7,n/2),(m/2-5,n/2),(m/2,n/2-5),(m/2,n/2-6),(m/2,n/2-1),(m/2,n/2-2),(m/2,n/2-3),(m/2,n/2+1),(m/2,n/2+2),(m/2,n/2+3),(m/2,n/2+4),(m/2-1,n/2),(m/2-2,n/2),(m/2-3,n/2),(m/2-1,n/2),(m/2-2,n/2),(m/2+3,n/2),(m/2+2,n/2),(m/2+3,n/2),(m/2+5,n/2),(m/2+1,n/2),(m/2+6,n/2),(m/2+7,n/2),(m/2+4,n/2),(m/2+8,n/2)   ])            
Bset1=set([ (0,n/4),(1,n/4),(2,n/4),(3,n/4),(4,n/4),(5,n/4) ])
Bset2=set([ (5,n/4-1),(5,n/4-2),(5,n/4-3),(5,n/4) ])
Bset3=set([ (1,int(0.75*n)),(2,int(0.75*n)),(3,int(0.75*n)),(4,int(0.75*n)),(5,int(0.75*n)) ])
Bset4=set([ (5,int(0.75*n)+1),(5,int(0.75*n)+2),(5,int(0.75*n)+3),(5,int(0.75*n)) ])
Bset=Bset1.union(Bset2.union(Bset3.union(Bset4)))

gtuple=tuple([(m/2-1,n/2+5)])
problem[11] = MultiRobotState(m,n,gtuple,frozenset(Aset),frozenset(Bset))
gtuple=tuple([(m/2-1,n/2-3)])
problem[12] = MultiRobotState(m,n,gtuple,frozenset(Aset),frozenset(Bset))
gtuple=tuple([(m/2-1,n/2-3),(m/2-1,n/2+5)])
problem[13] = MultiRobotState(m,n,gtuple,frozenset(Aset),frozenset(Bset))
gtuple=tuple([(m/2-1,n/2-3),(m/2-1,n/2+5),(m/2,n/2)])
problem[14] = MultiRobotState(m,n,gtuple,frozenset(Aset),frozenset(Bset))
Bset=Bset1.union(Bset2.union(Bset3.union(Bset4)))

m=22
n=16
Aset=set([(m/2,0),(m/2,n-1),(1,3),(3,n-1),(m-2,3),(m-4,n-1) ])
#Bset=set([(m/2,n/2),(m/2-4,n/2),(m/2-7,n/2),(m/2-5,n/2),(m/2,n/2-5),(m/2,n/2-6),(m/2,n/2-1),(m/2,n/2-2),(m/2,n/2-3),(m/2,n/2+1),(m/2,n/2+2),(m/2,n/2+3),(m/2,n/2+4),(m/2-1,n/2),(m/2-2,n/2),(m/2-3,n/2),(m/2-1,n/2),(m/2-2,n/2),(m/2+3,n/2),(m/2+2,n/2),(m/2+3,n/2),(m/2+5,n/2),(m/2+1,n/2),(m/2+6,n/2),(m/2+7,n/2),(m/2+4,n/2),(m/2+8,n/2)   ])            
Bset1=set([ (m-1,n/4),(m-2,n/4),(m-3,n/4),(m-4,n/4),(m-5,n/4),(m-6,n/4) ])
Bset2=set([ (m-6,n/4-1),(m-6,n/4-2),(m-6,n/4-3),(m-6,n/4) ])
Bset3=set([ (m-2,int(0.75*n)),(m-3,int(0.75*n)),(m-4,int(0.75*n)),(m-5,int(0.75*n)),(m-6,int(0.75*n)) ])
Bset4=set([ (m-6,int(0.75*n)+1),(m-6,int(0.75*n)+2),(m-6,int(0.75*n)+3),(m-6,int(0.75*n)) ])
Bset=Bset.union(Bset1.union(Bset2.union(Bset3.union(Bset4))))


gtuple=tuple([(m/2-1,n/2+5)])
problem[15] = MultiRobotState(m,n,gtuple,frozenset(Aset),frozenset(Bset))
gtuple=tuple([(m/2-1,n/2-3)])
problem[16] = MultiRobotState(m,n,gtuple,frozenset(Aset),frozenset(Bset))
gtuple=tuple([(m/2-1,n/2-3),(m/2-1,n/2+5)])
problem[17] = MultiRobotState(m,n,gtuple,frozenset(Aset),frozenset(Bset))
gtuple=tuple([(m/2-1,n/2-3),(m/2-1,n/2+5),(m/2,n/2)])
problem[18] = MultiRobotState(m,n,gtuple,frozenset(Aset),frozenset(Bset))

for i in xrange(0,len(problem)):
    print problem[i]    