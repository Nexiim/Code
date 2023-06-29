import matplotlib.pyplot as plt
import sys
import math

if len(sys.argv) == 2 :
	fichier = open(sys.argv[1], "r")
	evolution =""
	c = 0
	for line in fichier:
		c =c+1
		if "evolution" in line:
			if "densite" in line:
				evolution = "densite"
			elif "probabilite" in line:
				evolution = "probabilite"
			else:
				print("impossible de visualiser ce fichier")
			
		if "probaDef" in line:
			line = line.replace("probaDef:","")
			line = line.replace("\n","")
			nbProbaDef = len(line.split(","))
			valueProbaDef = line.split(",")
			valueProbaDef = list(map(float, valueProbaDef))
			
		if "parametre" in line:
			line = line.replace("parametre:","")
			line = line.replace("\n","")
			nbLambda = len(line.split(","))
			valueLambda = line.split(",")
			valueLambda = list(map(float, valueLambda))
			
		if "nbIteration" in line:
			line = line.replace("nbIteration:","")
			line = line.replace("\n","")
			nbIter = len(line.split(","))
			valueNbIter = line.split(",")
			valueNbIter = list(map(float, valueNbIter))
		if "-\n" in line:
			break
	
	data = [[[[]] * nbIter for i in range(nbProbaDef)]for i in range(nbLambda)]
	
	if evolution == "densite":			
		while(line != ''):
			value = fichier.readline()
			value = value.split(",")
			for v in value:
				if "lambda" in v:
					v = v.replace("lambda:","")
					posLambda = valueLambda.index(float(v))	
				if "probaDef" in v:
					v = v.replace("probaDef:","")
					posProbaDef = valueProbaDef.index(float(v))	
				if "T" in v:
					v = v.replace("T:","")
					posNbIter = valueNbIter.index(float(v))
		
			line = fichier.readline()
		
			while(line != "-\n"):
				data[posLambda][posProbaDef][posNbIter].append(line)
				line = fichier.readline()
				if (line == ''):
					break
		
		if nbProbaDef < nbLambda:	
			fig, axs = plt.subplots(1,nbProbaDef)
		
			for i in range(nbProbaDef):
				if nbProbaDef >1 :
					axs[i].set_title("Evolution de la densité avec $\kappa = $"+str(valueProbaDef[i]))
					axs[i].set(xlabel="nombre d'itérarions", ylabel="Population en état d'alerte(%)")
				else:
					axs.set_title("Evolution de la densité avec $\kappa = $"+str(valueProbaDef[i]))
					axs.set(xlabel="nombre d'itérarions", ylabel="Population en état d'alerte(%)")
				for j in range(nbLambda):
					abs = []
					ord = []
					for element in data[j][i][0]:
						element = element.split(",")
						ord.append(float(element[1]))
						abs.append(float(element[0]))	
					if nbProbaDef >1 :
						axs[i].plot(abs,ord,label = "lambda :"+str(valueLambda[j]))
						axs[i].legend(loc = "lower right")
					else:
						axs.plot(abs,ord,label = "lambda :"+str(valueLambda[j]))
						axs.legend(loc = "lower right")	
		else:
			fig, axs = plt.subplots(1,nbLambda)
		
			for i in range(nbLambda):
				if nbLambda >1 :
					axs[i].set_title("Evolution de la densité avec un lambda  de "+str(valueLambda[i]))
					axs[i].set(xlabel="nombre d'itérarions", ylabel="Population en état d'alerte(%)")
				else:
					axs.set_title("Evolution de la densité avec un lambda de  "+str(valueLambda[i]))
					axs.set(xlabel="nombre d'itérarions", ylabel="Population en état d'alerte(%)")
				for j in range(nbProbaDef):
					abs = []
					ord = []
					for element in data[i][j][0]:
						element = element.split(",")
						ord.append(float(element[1]))
						abs.append(float(element[0]))	
					if nbLambda >1 :
						axs[i].plot(abs,ord,label = "proba de def :"+str(valueProbaDef[j]))										
						axs[i].legend(loc = "lower right")
					else:
						axs.plot(abs,ord,label = "proba de def :"+str(valueProbaDef[j]))
						axs.legend(loc = "lower right")	
			
				
	elif evolution == "probabilite":
		while(line != ''):
			value = fichier.readline()
			value = value.split(",")
			for v in value:
				if "lambda" in v:
					v = v.replace("lambda:","")
					posLambda = valueLambda.index(float(v))
				if "probaDef" in v:
					v = v.replace("probaDef:","")
					posProbaDef = valueProbaDef.index(float(v))	
				if "T" in v:
					v = v.replace("T:","")
					posNbIter = valueNbIter.index(float(v))
		
			line = fichier.readline()
			while(line != "-\n"):
				data[posLambda][posProbaDef][posNbIter].append(line)
				line = fichier.readline()
				if (line == ''):
					break
			
		fig, axs = plt.subplots(1,nbIter)
		
		for k in range(nbIter):
			if nbIter > 1:
				axs[k].set_title("Evolution de la probabilité d'avoir atteint le seuil en "+str(valueNbIter[k])+" itérations")
				axs[k].set(ylabel="Probabilité(%) d'avoir atteint le seuil", xlabel="Probabilité de défaillance")
			else:
				axs.set_title("Evolution de la probabilité d'avoir atteint le seuil en "+str(valueNbIter[0])+" itérations")
				axs.set(ylabel="Probabilité(%) d'avoir atteint le seuil", xlabel="Probabilité de défaillance")
			for j in range(nbLambda):
				abs = []
				ord = []
				for i in range(nbProbaDef):
					for element in data[j][i][k]:
						ord.append(float(element))
						abs.append(float(valueProbaDef[i]))
				if nbIter > 1:	
					axs[k].plot(abs,ord,label = "lambda :"+str(valueLambda[j]))
					axs[k].legend(loc = "lower right")
				else:
					axs.plot(abs,ord,label = "lambda :"+str(valueLambda[j]))
					axs.legend(loc = "lower right")
					
	plt.show()
else:
	print ('veuiller choisir un fichier à afficher')



