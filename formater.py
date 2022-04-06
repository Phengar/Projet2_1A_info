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

NODES_CSV_IN = "nodes.csv.bak"
NODES_CSV_OUT = "nodes.csv"
EDGES_CSV_IN = "edges.csv.bak"
EDGES_CSV_OUT = "edges.csv"

dump = [] # Dump list that contains the file content processed
hashtable = {} # Hashtable to avoid duplicates

##################################################################################

# ------------------------------------------------------------------------------#
# Formating the edges file :												 	#
# ------------------------------------------------------------------------------#
file_in = open(EDGES_CSV_IN, "r")
file_in.readline() # Avoiding first row

for line in file_in:
	if(not line in hashtable): # Checks for any duplicates
		hashtable[line] = 1
		string = line.replace(" ", "") # Deletes all blank characters
		L = string.split(",")
		# Checks for loop edges
		if((line[1:] != L[2][1:]) or (L[1][:-1] != L[3][:-2])):
			string = ",".join(L)
			string = string.replace("[", "")
			string = string.replace("]", "")
			string = string.replace(",", " ")
			dump.append(string)

file_in.close()

# ------------------------------------------------------------------------------#
# Saving the formated edges file	:										    #
# ------------------------------------------------------------------------------#
file_out = open(EDGES_CSV_OUT, "w")

for l in dump:
	file_out.write(l)

file_out.close()

#################################################################################

# ------------------------------------------------------------------------------#
# Formating the nodes file :									                #	
# ------------------------------------------------------------------------------#
file_in = open(NODES_CSV_IN, "r")
file_in.readline() # Avoiding first row
dump = []
i = 0

for line in file_in:
	line = line.replace("\"", "")
	line = line.replace(", ", "_")
	line = line.replace(" ", "_") # Replaces blank characters by underscores
	line = line.replace(chr(0xa0), "")
	line = line.replace(",", " ")
	dump.append(str(i) + " " + line)
	i += 1

file_in.close()

# ------------------------------------------------------------------------------#
# Saving the formated nodes file	:										    #
# ------------------------------------------------------------------------------#
file_out = open(NODES_CSV_OUT, "w")

for l in dump:
	file_out.write(l)

file_out.close()

#################################################################################