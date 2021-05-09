import matplotlib.pyplot as plt
import networkx as nx

f = open(".\\data\\g2.txt", "r")
f2 = open(".\\data\\curr_edge.txt", "r")

name_edge = f2.readline()
# print("\n in python name : "+name_edge)
# name = "name1"

highleted_color = "orange"
back_ground = "#59999c"
edge_color = "white"
vertex_color = "#f67d7d"

line1 = f.readline()
G = nx.DiGraph()
names = []
color_list = []
for line in f:
    data = line.split()
    # print(data)
    G.add_edge(data[0], data[1], edge_labels=data[2], lenght=(1.33*len(data[2])))
    if(data[2] == name_edge):
        color_list.append(highleted_color)
    else:
        color_list.append(edge_color)
    
    names.append(((data[0], data[1]), data[2]))

pos = nx.circular_layout(G)
fig = plt.figure()
# edge_names = nx.get_edge_attributes(G,'edge_labels').values()
nx.draw(G, pos, with_labels=True, node_size=450,
        node_color=vertex_color, width=7, font_color='white')

props = dict(boxstyle='round', facecolor="#FFFDD0", alpha=1)

nx.draw_networkx_edge_labels(G, pos, edge_labels=dict(
    names), font_color='#1C4755', bbox=props)

nx.draw_networkx_edges(G, pos, edge_color=color_list, style="dashed")

fig.set_facecolor(back_ground)
plt.show()
