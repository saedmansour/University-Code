from multi_robot_problem import MultiRobotState


class HardProblems():    
    
    
    def __init__(self):
        self.problem = {}
        
        
        ########################################################################
        ##### (1)
        
        #<PROBLEM 0>
        robots = tuple([(2, 0), (3,0)])
        dirt_locations = set()
        dirt_locations.add((1, 5))
        obstacle_locations = set()
        for i in xrange(0,10):
            obstacle_locations.add((i,i))
        self.problem[0] = MultiRobotState(20, 20, robots, frozenset(dirt_locations), frozenset(obstacle_locations))
        #</PROBLEM 0>
        
        
        #<PROBLEM 1>
        robots = tuple([(2, 0), (3,0)])
        dirt_locations = set()
        dirt_locations.add((1, 5))
        obstacle_locations = set()
        for i in xrange(0,10):
            obstacle_locations.add((i,i))
        obstacle_locations = obstacle_locations.union(frozenset([(10,9),(11,9),(12,9),(13,9),(14,9)]))
        #obstacle_locations.add( ((1,2),(3,4)) )
        self.problem[1] = MultiRobotState(20, 20, robots, frozenset(dirt_locations), frozenset(obstacle_locations))
        #</PROBLEM 1>
        
        
        #<PROBLEM 2>
        robots = tuple([(2, 0), (3,0)])
        dirt_locations = set()
        dirt_locations.add((1, 5))
        obstacle_locations = set()
        for i in xrange(0,10):
            obstacle_locations.add((i,i))
        obstacle_locations = obstacle_locations.union(frozenset([(10,9),(11,9),(12,9),(13,9),(14,9),(15,9),(16,9),(17,9),(18,9)]))
        #obstacle_locations.add( ((1,2),(3,4)) )
        self.problem[2] = MultiRobotState(20, 20, robots, frozenset(dirt_locations), frozenset(obstacle_locations))
        #</PROBLEM 2>
        
        
        #<PROBLEM 3>
        robots = tuple([(2, 0), (3,0)])
        dirt_locations = set()
        dirt_locations.add((1, 5))
        obstacle_locations = set()
        for i in xrange(0,10):
            obstacle_locations.add((i,i))
        obstacle_locations = obstacle_locations.union(frozenset([(10,9),(11,9),(12,9),(13,9),(14,9),(16,9),(17,9),(18,9),(19,9)]))
        #obstacle_locations.add( ((1,2),(3,4)) )
        self.problem[3] = MultiRobotState(20, 20, robots, frozenset(dirt_locations), frozenset(obstacle_locations))
        #</PROBLEM 3>
        
        
        #<PROBLEM 4>
        robots = tuple([(2, 0), (14,0)])
        dirt_locations = set()
        dirt_locations = dirt_locations.union(frozenset([(1, 5), (19,1), (3,4),(10,19), (15,7)]))
        obstacle_locations = set()
        for i in xrange(0,10):
            obstacle_locations.add((i,i))
        obstacle_locations = obstacle_locations.union(frozenset([(10,9),(11,9),(12,9),(13,9),(14,9),(16,9),(17,9),(18,9),(19,9)]))
        self.problem[4] = MultiRobotState(20, 20, robots, frozenset(dirt_locations), frozenset(obstacle_locations))
        #</PROBLEM 4>
        
        
        #<PROBLEM 5>
        robots = tuple([(2, 0), (14,0), (1,3), (2,10)])
        dirt_locations = set()
        dirt_locations = dirt_locations.union(frozenset([(1, 5), (19,1), (3,4),(10,19), (15,7)]))
        obstacle_locations = set()
        for i in xrange(0,10):
            obstacle_locations.add((i,i))
        obstacle_locations = obstacle_locations.union(frozenset([(10,9),(11,9),(12,9),(13,9),(14,9),(16,9),(17,9),(18,9),(19,9)]))
        self.problem[5] = MultiRobotState(20, 20, robots, frozenset(dirt_locations), frozenset(obstacle_locations))
        #</PROBLEM 5>
        
        
        #<PROBLEM 6>
        robots = tuple([(2, 0), (14,0), (1,3), (2,10)])
        dirt_locations = set()
        dirt_locations = dirt_locations.union(frozenset([(1, 5), (19,1), (3,4),(10,19), (15,7), (15,15), (17,18)]))
        obstacle_locations = set()
        for i in xrange(0,10):
            obstacle_locations.add((i,i))
        obstacle_locations = obstacle_locations.union(frozenset([(10,9),(11,9),(12,9),(13,9),(14,9),(16,9),(17,9),(18,9),(19,9)]))
        self.problem[6] = MultiRobotState(20, 20, robots, frozenset(dirt_locations), frozenset(obstacle_locations))
        #</PROBLEM 6>
        
        #<PROBLEM 7>
        robots = tuple([(2, 0), (14,0), (1,3), (2,10), (2,18)])
        dirt_locations = set()
        dirt_locations = dirt_locations.union(frozenset([(1, 5), (19,1), (3,4),(10,19), (15,7), (15,15), (17,18)]))
        obstacle_locations = set()
        for i in xrange(0,10):
            obstacle_locations.add((i,i))
        obstacle_locations = obstacle_locations.union(frozenset([(10,9),(11,9),(12,9),(13,9),(14,9),(16,9),(17,9),(18,9),(19,9)]))
        self.problem[7] = MultiRobotState(20, 20, robots, frozenset(dirt_locations), frozenset(obstacle_locations))
        #</PROBLEM 7>
        
        
        #<PROBLEM 8>
        robots = tuple([(0,3), (0,17), (5,10), (6,18), (14,13), (18, 19)])
        dirt_locations = set()
        dirt_locations = dirt_locations.union(frozenset([(1, 5), (4,2), (10,4), (19,1), (3,4),(10,19), (15,7), (15,15), (17,18)]))
        obstacle_locations = set()
        for i in xrange(0,10):
            obstacle_locations.add((i,i))
        obstacle_locations = obstacle_locations.union(frozenset([(10,9),(11,9),(12,9),(13,9),(14,9),(16,9),(17,9),(18,9),(19,9)]))
        self.problem[8] = MultiRobotState(20, 20, robots, frozenset(dirt_locations), frozenset(obstacle_locations))
        #</PROBLEM 8>
        
        
        #<PROBLEM 9>
        robots = tuple([(1,0), (10,0), (19,4), (15,5), (10,7), (18,0)])
        dirt_locations = set()
        dirt_locations = dirt_locations.union(frozenset([(1, 5), (4,2), (10,4), (19,1), (3,4),(10,19), (15,7), (15,15), (17,18)]))
        obstacle_locations = set()
        for i in xrange(0,10):
            obstacle_locations.add((i,i))
        obstacle_locations = obstacle_locations.union(frozenset([(10,9),(11,9),(12,9),(13,9),(14,9),(16,9),(17,9),(18,9),(19,9)]))
        self.problem[9] = MultiRobotState(20, 20, robots, frozenset(dirt_locations), frozenset(obstacle_locations))
        #</PROBLEM 9>
        
        
        #<PROBLEM 10>
        robots = tuple([(1,0), (10,0), (19,4), (15,5), (10,7), (18,0)])
        dirt_locations = set()
        dirt_locations = dirt_locations.union(frozenset([(1, 5), (4,2), (10,4), (19,1), (3,4),(10,19), (15,7), (15,15), (17,18)]))
        obstacle_locations = set()
        for i in xrange(0,10):
            obstacle_locations.add((i,i))
        obstacle_locations = obstacle_locations.union(frozenset([(10,9),(11,9),(12,9),(13,9),(14,9),(16,9),(17,9),(18,9),(19,9)]))
        for i in xrange(0,10):
            obstacle_locations.add((i,i+5))
        obstacle_locations = obstacle_locations.union(frozenset([(10,14), (11,14), (12,14), (13,14), (14,14), (15,14), (16,14), (17,14), (18,14)]))
        
        self.problem[10] = MultiRobotState(20, 20, robots, frozenset(dirt_locations), frozenset(obstacle_locations))
        #</PROBLEM 10>
        
        
        
        ########################################################################
        ##### (2)
        
        #<PROBLEM 11>
        robots = tuple([(0,0)])
        dirt_locations = frozenset([(19,19)])
        obstacle_locations = set()
        for i in xrange(0,20):
            if i == 9:
                continue
            obstacle_locations.add((i,19-i))
        self.problem[11] = MultiRobotState(20, 20, robots, frozenset(dirt_locations), frozenset(obstacle_locations))
        #</PROBLEM 11>
        
        
        #<PROBLEM 12>
        robots = tuple([(0,0), (0,1),(0,2),(1,0),(1,1),(1,2)])
        dirt_locations = frozenset([(19,19)])
        obstacle_locations = set()
        for i in xrange(0,20):
            if i == 9:
                continue
            obstacle_locations.add((i,19-i))
        self.problem[12] = MultiRobotState(20, 20, robots, frozenset(dirt_locations), frozenset(obstacle_locations))
        #</PROBLEM 12>
        
        
        #<PROBLEM 13>
        robots = tuple([(0,0), (0,1),(0,2),(1,0),(1,1),(1,2)])
        dirt_locations = frozenset([(19,19)])
        obstacle_locations = set()
        for i in xrange(0,20):
            if i == 9:
                continue
            obstacle_locations.add((i,19-i))
        self.problem[13] = MultiRobotState(20, 20, robots, frozenset(dirt_locations), frozenset(obstacle_locations))
        #</PROBLEM 13>
        
        
        #<PROBLEM 14>
        robots = tuple([(0,0), (0,1),(0,2),(1,0),(1,1),(1,2)])
        dirt_locations = frozenset([(19,19)])
        obstacle_locations = set()
        for i in xrange(0,20):
            if i == 18:
                continue
            obstacle_locations.add((i,19-i))
        self.problem[14] = MultiRobotState(20, 20, robots, frozenset(dirt_locations), frozenset(obstacle_locations))
        #</PROBLEM 14>
        
        
        #<PROBLEM 15>
        robots = tuple([(0,0), (1,10), (17,0)])
        dirt_locations = frozenset([(19,19), (10,1), (0,8), (0,9)])
        obstacle_locations = set()
        for i in xrange(0,20):
            if i == 18:
                continue
            obstacle_locations.add((i,19-i))
        self.problem[15] = MultiRobotState(20, 20, robots, frozenset(dirt_locations), frozenset(obstacle_locations))
        #</PROBLEM 15>
        
        
        
        ########################################################################
        ##### (3)
        
        #<PROBLEM 16>
        robots = tuple([(9,19)])
        dirt_locations = frozenset([(11,19)])
        obstacle_locations = set()
        for i in xrange(0,20):
            if i == 15:
                break
            obstacle_locations.add((10,19-i))
        self.problem[16] = MultiRobotState(20, 20, robots, frozenset(dirt_locations), frozenset(obstacle_locations))
        #</PROBLEM 16>
        
        

        ########################################################################
        ##### (4)
        
        #<PROBLEM 17>
        robots = tuple([(9,19), (18, 15), (10,15)])
        dirt_locations = frozenset([(11,19), (0,2), (3,5), (7,9), (10,11)])
        obstacle_locations = frozenset([(0,3), (1,3), (2,3), (3,3), (3,2),(3,0)])
        self.problem[17] = MultiRobotState(20, 20, robots, frozenset(dirt_locations), frozenset(obstacle_locations))
        #</PROBLEM 17>
        
        
        ########################################################################
        ##### (4)
        
        #<PROBLEM 18>
        robots = tuple([(15,15), (19,19), (14,7)])
        dirt_locations = frozenset([(0,19), (12,12), (13,14)])
        obstacle_locations = set()
        for i in xrange(0,20):
            if i == 0:
                continue
            obstacle_locations.add((1,i))
        for i in xrange(0,20):
            if i == 0 or i == 19:
                continue
            obstacle_locations.add((i,1))
        self.problem[18] = MultiRobotState(20, 20, robots, frozenset(dirt_locations), frozenset(obstacle_locations))
        #</PROBLEM 18>
        
        
        
    
        
    def printALL(self,f): 
        for i in xrange(0,len(self.problem)):
            f.write( "\n\n\n\n\n\n")
            f.write( "================"+str(i)+"==================================\n")
            f.write(str(self.problem[i]))
            
                
    def getProblems(self):
        return self.problem
    
#HardProblems().printALL()