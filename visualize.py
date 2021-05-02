import matplotlib.pyplot as plt
import networkx as nx

class Graph:
    def __init__(self):
        self.edges = []
        self.names = []

    def addEdge(self, a, b,name):
        self.edges.append([a,b])
        self.names.append(((a,b),name))

    def visualize(self):
        G = nx.Graph()
        G.add_edges_from(self.edges)
        pos = nx.spring_layout(G)
        plt.figure()

        nx.draw(G,pos,edge_color='black',width=20,linewidths=1,node_size=600,node_color='green',alpha=0.9,labels={node:node for node in G.nodes()})

        nx.draw_networkx_edge_labels(G,pos,edge_labels=dict(self.names),font_color='red')
        nx.draw_networkx_edge_labels
        plt.axis('off')
        plt.show()
    def print_name(self):
        print(self.names)
  

G = Graph()

G.addEdge(0,2,'high way 1')
G.addEdge(2,1,'high way 2')
G.addEdge(3,2,'high way 3')
G.addEdge(1,3,'high way 4')
G.addEdge(2,4,'high way 5')
G.addEdge(1,4,'high way 6')
# G.print_name()
G.visualize()