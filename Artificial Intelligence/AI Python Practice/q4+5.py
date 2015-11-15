class Graph:
    
    def __init__(self, N):
        self.N = N
        self.edges = {}
        
        for i in xrange(0, N):
            if i not in self.edges:
                self.edges[i] = set()
    
    def addEdge(self, src, dest):
        self.edges[src].add(dest)
    
    def getSuccessors(self, vertex):
        return self.edges[vertex]
    

def DFS(graph, current, goal, visited=set()):
    if current in visited:
        return None
    
    if current == goal:
        return 0
    
    visited.add(current)
    
    for son in graph.getSuccessors(current):
        result = DFS(graph, son, goal, visited)
        if result is not None:
            return result + 1
    
    return None


graph = Graph(10)
graph.addEdge(0, 1)
graph.addEdge(0, 2)
graph.addEdge(0, 3)
graph.addEdge(0, 4)
graph.addEdge(0, 5)
graph.addEdge(1, 6)
graph.addEdge(6, 7)
graph.addEdge(7, 8)
graph.addEdge(8, 9)
graph.addEdge(4, 9)

print DFS(graph, 0, 9) #Should be 5, not 2.