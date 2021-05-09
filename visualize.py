import matplotlib.pyplot as plt
import networkx as nx

f = open(".\\data\\g1.txt", "r")

line1 = f.readline()
G = nx.Graph()
names = []
color_list = []
for line in f:
    data = line.split()
    # print(data)
    G.add_edge(data[0], data[1], edge_labels=data[2], lenght=(2*len(data[2])))
    color_list.append("wheat")
    names.append(((data[0], data[1]), data[2]))

pos = nx.spring_layout(G)
fig = plt.figure()
# edge_names = nx.get_edge_attributes(G,'edge_labels').values()
nx.draw(G, pos, with_labels=True, node_size=450,
        node_color="black", width=7,font_color='white')

props = dict(boxstyle='round', facecolor='#fffdd0', alpha=1)

nx.draw_networkx_edge_labels(G, pos, edge_labels=dict(
    names), font_color='#00008B', bbox=props)

nx.draw_networkx_edges(G,pos,edge_color=color_list,style="dashed")
fig.set_facecolor("#ADD8E6")
plt.show()
