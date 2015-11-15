'''
Created on Apr 23, 2011

@author: habasi
'''
from multi_robot_problem import MultiRobotState
from search.algorithm import Heuristic
import math
import random
import time




class Heuristic_Temp_Fixed7(Heuristic):
    def evaluate(self, state):
        if(len(state.dirt_locations)== 0):
            return 0 
        max=0
        sum_d=0
        for dirt in (state.dirt_locations):
            min_tmp=abs(state.robots[0][0]-dirt[0])+abs(state.robots[0][1]-dirt[1])
            for  robot in (state.robots):
                if(abs(robot[0]-dirt[0])+abs(robot[1]-dirt[1]) < min_tmp):
                    min_tmp=abs(robot[0]-dirt[0])+abs(robot[1]-dirt[1])
                sum_d+=min_tmp
            if(min_tmp>max):
                max=min_tmp
                
        #sum=max
        sum=0
        elment=min(state.dirt_locations)
        for  robot in (state.robots):
            min_tmp=abs(robot[0]-elment[0])+abs(robot[1]-elment[1])
            for dirt in (state.dirt_locations):
                if(abs(robot[0]-dirt[0])+abs(robot[1]-dirt[1]) < min_tmp):
                    min_tmp=abs(robot[0]-dirt[0])+abs(robot[1]-dirt[1])
            sum=sum+min_tmp    
        return  len(state.dirt_locations)*(sum+state.width*state.height)

    
class Heuristic_RobotsFromGarbage(Heuristic):
    def evaluate(self, state):
        max=0
        for dirt in (state.dirt_locations):
            min=abs(state.robots[0][0]-dirt[0])+abs(state.robots[0][1]-dirt[1])
            for  robot in (state.robots):
                if(abs(robot[0]-dirt[0])+abs(robot[1]-dirt[1]) < min):
                    min=abs(robot[0]-dirt[0])+abs(robot[1]-dirt[1])
            if(min>max):
                max=min
        return max+len(state.dirt_locations)*state.width*state.height

class Heuristic_GarbagesFromRobot(Heuristic):
    def evaluate(self, state):
        min_r=0  
        if(len(state.dirt_locations)== 0):
            return 0 
        elment=min(state.dirt_locations)
        for  robot in (state.robots):
            min_tmp=abs(robot[0]-elment[0])+abs(robot[1]-elment[1])
            for dirt in (state.dirt_locations):
                if(abs(robot[0]-dirt[0])+abs(robot[1]-dirt[1]) < min_tmp):
                    min_tmp=abs(robot[0]-dirt[0])+abs(robot[1]-dirt[1])
            if(min_r>min_tmp):
                min_r=min_tmp
        if(len(state.dirt_locations)>=len(state.robots)):
            return min_tmp+min_tmp*len(state.dirt_locations)
        else:
            t=float(len(state.robots)-len(state.dirt_locations))
            temp=t/float(len(state.robots))
            return min_tmp+int(math.ceil(temp))+(min_tmp+int(math.ceil(temp)))*len(state.dirt_locations)

class Heuristic_max(Heuristic):
        def evaluate(self, state):
            h1 = Heuristic_GarbagesFromRobot()
            h2 = Heuristic_RobotsFromGarbage()
            return max(h1.evaluate(state),h2.evaluate(state))

class Heuristic_alpha(Heuristic):
        def __init__ (self,weight):
            self.weight=weight
        def evaluate(self, state):
            h1 = Heuristic_GarbagesFromRobot()
            h2 = Heuristic_RobotsFromGarbage()
            return (self.weight)*h1.evaluate(state)+(1-self.weight)*h2.evaluate(state)     


class Heuristic_Temp(Heuristic):
    def evaluate(self, state):
        max=0
        a=set()
        for dirt in (state.dirt_locations):
            min_tmp=abs(state.robots[0][0]-dirt[0])+abs(state.robots[0][1]-dirt[1])
            for  robot in (state.robots):
                if(abs(robot[0]-dirt[0])+abs(robot[1]-dirt[1]) < min_tmp):
                    min_tmp=abs(robot[0]-dirt[0])+abs(robot[1]-dirt[1])
            if(min_tmp>max):
                max=min_tmp
        a.add(max)
        a.add(max+max*len(state.dirt_locations))
        s=max+max*len(state.dirt_locations)
        min_r=0  
        if(len(state.dirt_locations)== 0):
            return 0 
        elment=min(state.dirt_locations)
        for  robot in (state.robots):
            min_tmp=abs(robot[0]-elment[0])+abs(robot[1]-elment[1])
            for dirt in (state.dirt_locations):
                if(abs(robot[0]-dirt[0])+abs(robot[1]-dirt[1]) < min_tmp):
                    min_tmp=abs(robot[0]-dirt[0])+abs(robot[1]-dirt[1])
            a.add(min_tmp)  
            s=s+min_tmp 
        return (len(state.dirt_locations)*(s+state.width+state.height))
    
    
class Heuristic_Temp(Heuristic):
    def evaluate(self, state):
        max=0
        a=set()
        for dirt in (state.dirt_locations):
            min_tmp=abs(state.robots[0][0]-dirt[0])+abs(state.robots[0][1]-dirt[1])
            for  robot in (state.robots):
                if(abs(robot[0]-dirt[0])+abs(robot[1]-dirt[1]) < min_tmp):
                    min_tmp=abs(robot[0]-dirt[0])+abs(robot[1]-dirt[1])
            if(min_tmp>max):
                max=min_tmp
        a.add(max)
        a.add(max+max*len(state.dirt_locations))
        s=max+max*len(state.dirt_locations)
        min_r=0  
        if(len(state.dirt_locations)== 0):
            return 0 
        elment=min(state.dirt_locations)
        for  robot in (state.robots):
            min_tmp=abs(robot[0]-elment[0])+abs(robot[1]-elment[1])
            for dirt in (state.dirt_locations):
                if(abs(robot[0]-dirt[0])+abs(robot[1]-dirt[1]) < min_tmp):
                    min_tmp=abs(robot[0]-dirt[0])+abs(robot[1]-dirt[1])
            a.add(min_tmp)  
            s=s+min_tmp 
        return (len(state.dirt_locations)*(s+state.width*state.height))
        
class Heuristic_Temp_Fixed(Heuristic):
    def evaluate(self, state):
        max=0
        a=set()
        for dirt in (state.dirt_locations):
            min_tmp=abs(state.robots[0][0]-dirt[0])+abs(state.robots[0][1]-dirt[1])
            for  robot in (state.robots):
                if(abs(robot[0]-dirt[0])+abs(robot[1]-dirt[1]) < min_tmp):
                    min_tmp=abs(robot[0]-dirt[0])+abs(robot[1]-dirt[1])
            if(min_tmp>max):
                max=min_tmp
        a.add(max)
        a.add(max+max*len(state.dirt_locations))
        s=max+max*len(state.dirt_locations)
        min_r=0  
        if(len(state.dirt_locations)== 0):
            return 0 
        elment=min(state.dirt_locations)
        for  robot in (state.robots):
            min_tmp=abs(robot[0]-elment[0])+abs(robot[1]-elment[1])
            for dirt in (state.dirt_locations):
                if(abs(robot[0]-dirt[0])+abs(robot[1]-dirt[1]) < min_tmp):
                    min_tmp=abs(robot[0]-dirt[0])+abs(robot[1]-dirt[1])
            a.add(min_tmp)  
            s=s+min_tmp
        
        obs_very_bad=0
        for  robot in (state.robots):
            obs_bad=0
            for obs in (state.obstacle_locations):
                if(abs(robot[0]-obs[0])+abs(robot[1]-obs[1]) == 1):
                    obs_bad=1
            if(obs_bad==1):
                obs_very_bad=1
                  
     
        return ((len(state.dirt_locations)+obs_very_bad)*(s+state.width*state.height)) 
    
class Heuristic_Temp_Fixed1(Heuristic):
    def evaluate(self, state):
        if(len(state.dirt_locations)== 0):
            return 0 
        max=0
        for dirt in (state.dirt_locations):
            min_tmp=abs(state.robots[0][0]-dirt[0])+abs(state.robots[0][1]-dirt[1])
            for  robot in (state.robots):
                if(abs(robot[0]-dirt[0])+abs(robot[1]-dirt[1]) < min_tmp):
                    min_tmp=abs(robot[0]-dirt[0])+abs(robot[1]-dirt[1])
            if(min_tmp>max):
                max=min_tmp
                
        s=max
        elment=min(state.dirt_locations)
        for  robot in (state.robots):
            min_tmp=abs(robot[0]-elment[0])+abs(robot[1]-elment[1])
            for dirt in (state.dirt_locations):
                if(abs(robot[0]-dirt[0])+abs(robot[1]-dirt[1]) < min_tmp):
                    min_tmp=abs(robot[0]-dirt[0])+abs(robot[1]-dirt[1])
            s=s+min_tmp
        return ((len(state.dirt_locations))*(s+state.width*state.height)) 
    
class Heuristic_Temp_Fixed2(Heuristic):
    def evaluate(self, state):
        if(len(state.dirt_locations)== 0):
            return 0 
        max=0
        for dirt in (state.dirt_locations):
            min_tmp=abs(state.robots[0][0]-dirt[0])+abs(state.robots[0][1]-dirt[1])
            for  robot in (state.robots):
                if(abs(robot[0]-dirt[0])+abs(robot[1]-dirt[1]) < min_tmp):
                    min_tmp=abs(robot[0]-dirt[0])+abs(robot[1]-dirt[1])
            if(min_tmp>max):
                max=min_tmp
                
        s=max
        elment=min(state.dirt_locations)
        for  robot in (state.robots):
            min_tmp=abs(robot[0]-elment[0])+abs(robot[1]-elment[1])
            for dirt in (state.dirt_locations):
                if(abs(robot[0]-dirt[0])+abs(robot[1]-dirt[1]) < min_tmp):
                    min_tmp=abs(robot[0]-dirt[0])+abs(robot[1]-dirt[1])
            s=s+min_tmp
        if(time.clock()%1 == 0):
            obs=1
        else:
            obs=0
        
        return ((len(state.dirt_locations))*(s+state.width*state.height+obs*random.sample(xrange(state.width+state.height),1))) 
    
class Heuristic_Temp_Fixed3(Heuristic):
    def evaluate(self, state):
        if(len(state.dirt_locations)== 0):
            return 0 
        max=0
        sum_d=0
        for dirt in (state.dirt_locations):
            min_tmp=abs(state.robots[0][0]-dirt[0])+abs(state.robots[0][1]-dirt[1])
            for  robot in (state.robots):
                if(abs(robot[0]-dirt[0])+abs(robot[1]-dirt[1]) < min_tmp):
                    min_tmp=abs(robot[0]-dirt[0])+abs(robot[1]-dirt[1])
                sum_d+=min_tmp
            if(min_tmp>max):
                max=min_tmp
                
        sum=max
        elment=min(state.dirt_locations)
        for  robot in (state.robots):
            min_tmp=abs(robot[0]-elment[0])+abs(robot[1]-elment[1])
            for dirt in (state.dirt_locations):
                if(abs(robot[0]-dirt[0])+abs(robot[1]-dirt[1]) < min_tmp):
                    min_tmp=abs(robot[0]-dirt[0])+abs(robot[1]-dirt[1])
            sum=sum+min_tmp    
        robot_distancex = 0
        robot_distancey = 0
        
        
        for robot in (state.robots):
            for  robot2 in (state.robots):
                robot_distancex=robot_distancex+abs(robot[0]-robot2[0])
                robot_distancey=robot_distancey+abs(robot[1]-robot2[1])
        disAfect=robot_distancey+robot_distancex
        
        iterator1
        max_sum
        iterator1=iterator1+1
        if(iterator1<20*state.width*state.height):
            flag=0
        if(iterator1>=20*state.width*state.height):
            if(max_sum<disAfect):
                flag=1
        if(iterator1>40*state.width*state.height):
            iterator1=0
            flag=0
        temp= flag*disAfect
        if(temp == 0):
            temp2=0
        else:
            temp2=1.0/temp
        return ((len(state.dirt_locations))*(sum+state.width*state.height+temp2*state.width*state.height))

class Heuristic_Temp_Fixed4(Heuristic):
    def evaluate(self, state):
        if(len(state.dirt_locations)== 0):
            return 0 
        max=0
        for dirt in (state.dirt_locations):
            min_tmp=abs(state.robots[0][0]-dirt[0])+abs(state.robots[0][1]-dirt[1])
            for  robot in (state.robots):
                if(abs(robot[0]-dirt[0])+abs(robot[1]-dirt[1]) < min_tmp):
                    min_tmp=abs(robot[0]-dirt[0])+abs(robot[1]-dirt[1])
            if(min_tmp>max):
                max=min_tmp
                
        sum=max
        elment=min(state.dirt_locations)
        for  robot in (state.robots):
            min_tmp=abs(robot[0]-elment[0])+abs(robot[1]-elment[1])
            for dirt in (state.dirt_locations):
                if(abs(robot[0]-dirt[0])+abs(robot[1]-dirt[1]) < min_tmp):
                    min_tmp=abs(robot[0]-dirt[0])+abs(robot[1]-dirt[1])
            sum=sum+min_tmp    
        robot_distance = 0
        
        
        for robot in (state.robots):
            for  robot2 in (state.robots):
                robot_distance=robot_distance+abs(robot[0]-robot2[0])+abs(robot[1]-robot2[1])
        
      
        obs_distance = 0
        for obs in (state.dirt_locations):
            for  obs2 in (state.dirt_locations):
                obs_distance=robot_distance+abs(obs[0]-obs2[0])+abs(obs[1]-obs2[1])
        
        return ((len(state.dirt_locations))*(sum+state.width*state.height-robot_distance))
    
class Heuristic_Temp_Fixed5(Heuristic):
  
    def evaluate(self, state):
        s=0
        for dirt in (state.dirt_locations):
            min_tmp=abs(state.robots[0][0]-dirt[0])+abs(state.robots[0][1]-dirt[1])
            for  robot in (state.robots):
                if(abs(robot[0]-dirt[0])+abs(robot[1]-dirt[1]) < min):
                    min_tmp=abs(robot[0]-dirt[0])+abs(robot[1]-dirt[1])
                s+=min_tmp
        
        if(len(state.dirt_locations)== 0):
            return 0 
        elment=min(state.dirt_locations)
        for  robot in (state.robots):
            min_tmp=abs(robot[0]-elment[0])+abs(robot[1]-elment[1])
            for dirt in (state.dirt_locations):
                if(abs(robot[0]-dirt[0])+abs(robot[1]-dirt[1]) < min_tmp):
                    min_tmp=abs(robot[0]-dirt[0])+abs(robot[1]-dirt[1])
                s+=min_tmp
       
        robot_distancex=0
        robot_distancey=0
        for robot in (state.robots):
            for  robot2 in (state.robots):
                robot_distancex=robot_distancex+abs(robot[0]-robot2[0])
                robot_distancey=robot_distancey+abs(robot[1]-robot2[1])
            disAfect=robot_distancey+robot_distancex
        
        
        
        return len(state.dirt_locations)*state.width*state.height+s+float(1)/(disAfect*disAfect)

class Heuristic_Temp_Fixed6(Heuristic):
    def __init__(self):
        self.iterator=0
        self.max_sum=0
    def evaluate(self, state):
        if(len(state.dirt_locations)== 0):
            return 0 
        max=0
        sum_d=0
        for dirt in (state.dirt_locations):
            min_tmp=abs(state.robots[0][0]-dirt[0])+abs(state.robots[0][1]-dirt[1])
            for  robot in (state.robots):
                if(abs(robot[0]-dirt[0])+abs(robot[1]-dirt[1]) < min_tmp):
                    min_tmp=abs(robot[0]-dirt[0])+abs(robot[1]-dirt[1])
                sum_d+=min_tmp
            if(min_tmp>max):
                max=min_tmp
                
        #sum=max
        sum=0
        elment=min(state.dirt_locations)
        for  robot in (state.robots):
            min_tmp=abs(robot[0]-elment[0])+abs(robot[1]-elment[1])
            for dirt in (state.dirt_locations):
                if(abs(robot[0]-dirt[0])+abs(robot[1]-dirt[1]) < min_tmp):
                    min_tmp=abs(robot[0]-dirt[0])+abs(robot[1]-dirt[1])
            sum=sum+min_tmp    
        if(len(state.obstacle_locations)==0):
            return  len(state.dirt_locations)*(sum+state.width*state.height)
        robot_distancex = 0
        robot_distancey = 0
        
        
        for robot in (state.robots):
            for  robot2 in (state.robots):
                robot_distancex=robot_distancex+abs(robot[0]-robot2[0])
                robot_distancey=robot_distancey+abs(robot[1]-robot2[1])
        disAfect=robot_distancey+robot_distancex
        
        if(self.max_sum>=40):
            self.max_sum=10
        else:
            self.max_sum=self.max_sum+1
        self.iterator=self.iterator+1
        if(self.iterator<2*state.width*state.height):
            flag=0
        if(self.iterator>=2*state.width*state.height):
            flag=1
        if(self.iterator>self.max_sum*state.width*state.height):
            self.iterator=0
        #    self.max_sum=self.max_sum+1
            flag=0
        temp= flag*disAfect
        if(temp == 0):
            temp2=0
        else:
            temp2=state.width*state.height*(1.0/temp)
        return  len(state.dirt_locations)*(sum+state.width*state.height   +  temp2*state.width*state.height)
    
