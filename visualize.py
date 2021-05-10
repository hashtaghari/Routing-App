import matplotlib.pyplot as plt
import networkx as nx

f = open(".\\data\\g2.txt", "r")
f2 = open(".\\data\\curr_edge.txt", "r")

Hi_edge_list = f2.readline().split()
Hi_edge = Hi_edge_list[0]

Hi_edge = str(Hi_edge)


highleted_color = "orange"
back_ground = "#59999c"
edge_color = "black"
vertex_color = "#f67d7d"

line1 = f.readline().split()


G = nx.DiGraph()
formatted_edge_labels_list = []

for line in f:
    data = line.split()
    if(str(data[2]) == Hi_edge):
        G.add_edge(data[0], data[1], color=highleted_color, edge_label=data[2],
                   lenght=(1.33*len(data[2])))
    else:
        G.add_edge(data[0], data[1], color=edge_color, edge_label=data[2],
                   lenght=(1.33*len(data[2])))
    formatted_edge_labels_list.append(((data[0],data[1]),data[2]))


fig = plt.figure()

pos = nx.circular_layout(G)

formatted_edge_labels = dict(formatted_edge_labels_list)
colors = nx.get_edge_attributes(G, 'color').values()
props = dict(boxstyle='round', facecolor="#FFFDD0", alpha=1)

nx.draw(G,pos,with_labels=True, font_color='white',width=7,edge_color=colors)

nx.draw_networkx_nodes(G,pos,node_size=450,node_color=vertex_color)
nx.draw_networkx_edges(G, pos, edge_color="white",arrowsize=15,style="dashed")
nx.draw_networkx_edge_labels(G,pos,edge_labels=formatted_edge_labels,font_color='red',bbox=props,label_pos=0.55)


fig.set_facecolor(back_ground)
plt.show()
f.close()
f2.close()