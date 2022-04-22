import random as rd
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.axes as plta
from math import *
from math import factorial
import time as tps
import scipy.integrate as itg
import sys
from unicodedata import mirrored
import networkx as nx
import pandas as pd
#sys.setrecursionlimit(1e40)

refTable=np.empty((10,100))
refTable2=[]
names={}

def get_graph(): #This function read the CSV files to get the whole graph
    MA=np.empty((227,227))
    i=0
    with open("./csv/nodes.csv") as fp:
        Lines=fp.readlines()
        for line in Lines:
            line=line.split(" ")
            refTable[int(line[2])][int(line[3])]=int(line[0])
            refTable2.append((int(line[2]),int(line[3])))
            names[int(line[0])]=(line[1])
    with open("./csv/edges.csv") as fp2:
        Lines=fp2.readlines()
        for line in Lines:
            line=line.split(" ")
            id1,id2=refTable[int(line[0])][int(line[1])],refTable[int(line[2])][int(line[3])]
            MA[int(id1)][int(id2)]=1
            MA[int(id2)][int(id1)]=1
    return MA

def MA_to_LA(M): #this function converts an Adjacency matrix to a adjacency list
    n=len(M)
    res=[[] for i in range(n)]
    for i in range(n):
        for j in range(n):
            if M[i,j]==1:
                res[i].append(j)
    return res

def create_LA():
    return MA_to_LA(get_graph()[0])

def construct_graph(M):  #This function transforms an adjacency matrix to a graph of the library networkx
    G,n=nx.Graph(),len(M)
    for i in range(n):
        for j in range(n):
            if M[i,j]==1:
                G.add_edge(i,j)
    return G

##These functions are different way to display a graph but none are really interesting in our case

def affiche_circular(G):
    nx.draw(G,pos=nx.circular_layout(G))
    plt.show()

def affiche_kamda(G):
    nx.draw(G,pos=nx.kamada_kawai_layout(G))
    plt.show()

def affiche_planar(G):
    nx.draw(G,pos=nx.planar_layout(G))
    plt.show()

def affiche_shell(G):
    nx.draw(G,pos=nx.shell_layout(G))
    plt.show()

def affiche_spring(G):
    nx.draw(G,pos=nx.spring_layout(G))
    plt.show()

def affiche_spectral(G):
    nx.draw(G,pos=nx.spectral_layout(G))
    plt.show()

def affiche_spiral(G):
    nx.draw(G,pos=nx.spiral_layout(G))
    plt.show()

def affiche_graphviz(G):
    nx.draw(G,pos=nx.drawing.nx_agraph.pygraphviz_layout(G))
    plt.show()

def affiche_(G):
    nx.draw(G,pos=nx._layout(G))
    plt.show()

affiche_circular(construct_graph(get_graph()))

affiche_kamda(construct_graph(get_graph()))

affiche_planar(construct_graph(get_graph()))

affiche_shell(construct_graph(get_graph()))

affiche_spring(construct_graph(get_graph()[:100][:100]))

affiche_spectral(construct_graph(get_graph()))

affiche_spiral(construct_graph(get_graph()))

affiche_graphviz(construct_graph(get_graph()))

affiche_(construct_graph(get_graph()))
    


##Therefore we display it with the native position of the nodes (x as semester and y as the rank of the UP/GP in the semester)

G=construct_graph(get_graph())

nx.draw(G, pos=refTable2, width=0.25, node_size=5, with_labels=False)

nx.draw_networkx_labels(G,refTable2,names,font_size=2,font_color='r')

plt.savefig('whole_graph.png', dpi=1000, format="png")

plt.show()


