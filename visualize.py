import matplotlib.pyplot as plt
import networkx as nx


class Graph:
    def __init__(self):
        self.edges = []
        self.names = []

    def addEdge(self, a, b, name):
        self.edges.append([a, b])
        self.names.append(((a, b), name))

    def visualize(self):
        G = nx.DiGraph()
        G.add_edges_from(self.edges)
        pos = nx.spring_layout(G)

        plt.figure()

        nx.draw(G, pos, edge_color='black', width=1, linewidths=1, node_size=600,node_color='green', alpha=0.9, labels={node: node for node in G.nodes()})

        nx.draw_networkx_edge_labels(G, pos, edge_labels=dict(self.names), font_color='red' )
        plt.axis('off')
        plt.show()

    def print_name(self):
        print(self.names)


G = Graph()

n, m = [int(x) for x in input().split()]

# print(n,m)

for i in range(0, m):
    x, y = [int(p) for p in input().split()]
    G.addEdge(x, y, "x")
# G.print_name()
G.visualize()
