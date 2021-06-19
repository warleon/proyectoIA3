srcDir =src
libDir =${srcDir}/lib
sourceDS = ${srcDir}/DBScan.cpp ${libDir}/KDTree.cpp
sourceKM = ${srcDir}/Kmeans.cpp 
sourceGMM = ${srcDir}/GMM.cpp 
main =  ${srcDir}/main.cpp

default:
	g++ -g ${main} ${sourceDS} ${sourceKM} ${sourceGMM} -o test


PHONY: default./