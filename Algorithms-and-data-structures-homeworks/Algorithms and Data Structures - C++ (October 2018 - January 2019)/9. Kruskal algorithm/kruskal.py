#!/usr/bin/env python
class Graph:
    def __init__(self,vertices):
        self.V = vertices
        self.graph = [] 
        self.visited_vertices = set()
        self.result_edges = []
        self.result_dict = {}

    def add_edge(self,u,v,w):
        self.graph.append([u,v,w])
    
    def Kruskal_algorithm(self):
        self.graph = sorted(self.graph,key=lambda item: item[2])
        
        for i in range(len(self.graph)):
            if self.graph[i][1] not in self.visited_vertices:
                self.visited_vertices.add(self.graph[i][1])
                self.result_edges.append(self.graph[i])
                if self.graph[i][0] not in self.result_dict:
                    self.result_dict[self.graph[i][0]] = []
                if self.graph[i][1] not in self.result_dict:
                    self.result_dict[self.graph[i][1]] = []
                
                self.result_dict[self.graph[i][0]].append("%d(%d)" % (self.graph[i][1], self.graph[i][2]))
        
        for key in sorted(self.result_dict.keys()):
            values = self.result_dict[key]
            print("%d -> " % key, end="")
            if len(values) > 0:
                for value in values:
                    print("%s " % value, end="")
            else:
                print("-", end="")
            print()

    
edges = int(input("Enter number of edges: "))
vertices = int(input("Enter number of vertices: "))

g = Graph(vertices)

print("For each edge in the graph enter source vertex, destination vertex and weight of the edge:")

for x in range(edges):
    src,dest,weight = map(int,input().split(" "))    
    g.add_edge(src, dest, weight)

g.Kruskal_algorithm()
