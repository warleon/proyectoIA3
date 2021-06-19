srcDir =src
libDir =${srcDir}/lib
sourceDS = ${srcDir}/DBScan.cpp ${libDir}/KDTree.cpp
sourceKM = ${srcDir}/Kmeans.cpp 
sourceGMM = ${srcDir}/GMM.cpp 
main =  ${srcDir}/main.cpp
eigenSrc = ${libDir}/Eigen

default:
	g++ -g ${main} ${sourceDS} ${sourceKM} ${sourceGMM} -I${eigenSrc} -o test


PHONY: default./