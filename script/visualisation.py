import matplotlib.pyplot as plt
import sys
import math

if len(sys.argv) == 2 :
	fichier = open(sys.argv[1], "r")
	nbCourbe = int(fichier.readline())
	for i in range(nbCourbe):
		abs = []
		ord = []
		try:
			Value = int(fichier.readline())
		except ValueError:
			Value = None
		while True:
			ligne = fichier.readline()
			if ligne == '':
				break
			if ligne.strip() == '-':
				break;
			element = ligne.split(',')
			
			ord.append(float(element[1]))
			abs.append(float(element[0]))
			
		
		plt.plot(abs,ord,label = Value)
		#plt.ylim(min,max)
	plt.legend(bbox_to_anchor =(0.75, 1.15), ncol = nbCourbe)
	plt.show()
else:
	print ('veuiller choisir un fichier à afficher')



