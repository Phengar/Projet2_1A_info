#################################################################################

# -*-*-*-*-*-*-*-* File formater program *-*-*-*-*-*-*-*-*-
#													      #
# 	> Deletes duplicate rows from an edges csv file       #
#	> Deletes loop edges from an edges csv file 	      #
#   > Replaces blank characters by _ in nodes csv file    #
#													      #
# -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-

# DAVAL Quentin - HUBINET Benjamin
# ISMIN 1A - EI21

#################################################################################

NODES_CSV = "nodes.csv"
EDGES_CSV = "edges.csv"

dump = [] # Dump list that contains the file content processed
hashtable = {} # Hashtable to avoid duplicates

##################################################################################

# ------------------------------------------------------------------------------#
# Formating the edges file :												 	#
# ------------------------------------------------------------------------------#
file_in = open(EDGES_CSV, "r")
dump.append(file_in.readline())

for line in file_in:
	if(not line in hashtable): # Checks for any duplicates
		hashtable[line] = 1
		string = line.replace(" ", "") # Deletes all blank characters
		L = string.split(",")
		# Checks for loop edges
		if((L[0][1:] != L[2][1:]) or (L[1][:-1] != L[3][:-2])):
			dump.append(",".join(L))

file_in.close()

# ------------------------------------------------------------------------------#
# Saving the formated edges file	:										    #
# ------------------------------------------------------------------------------#
file_out = open(EDGES_CSV, "w")

for l in dump:
	file_out.write(l)

file_out.close()

#################################################################################

# ------------------------------------------------------------------------------#
# Formating the nodes file :									                #	
# ------------------------------------------------------------------------------#
file_in = open(NODES_CSV, "r")
dump = [file_in.readline()]

for line in file_in:
	L = line.split(",")
	L[0] = L[0].replace(" ", "_") # Replaces blank characters by underscores
	dump.append(",".join(L))

file_in.close()

# ------------------------------------------------------------------------------#
# Saving the formated nodes file	:										    #
# ------------------------------------------------------------------------------#
file_out = open(NODES_CSV, "w")

for l in dump:
	file_out.write(l)

file_out.close()

#################################################################################