g1=L3
g2=L2CACHE
g3=FLOPS_AVX
tam=32
CAM=sba16-thcf16
CORE=1

for (( i = 0; i < 4; i++ )); do
    tam2=$((tam+1))
    cd $CAM
    likwid-perfctr -c $CORE -g $g1 invmat -r $tam -i 10 -o saida > likwid/$g1-$tam
    likwid-perfctr -c $CORE -g $g1 invmat -r $tam2 -i 10 -o saida > likwid/$g1-$tam2
    likwid-perfctr -c $CORE -g $g2 invmat -r $tam -i 10 -o saida > likwid/$g2-$tam
    likwid-perfctr -c $CORE -g $g2 invmat -r $tam2 -i 10 -o saida > likwid/$g2-$tam2
    likwid-perfctr -c $CORE -g $g3 invmat -r $tam -i 10 -o saida > likwid/$g3-$tam
    likwid-perfctr -c $CORE -g $g3 invmat -r $tam2 -i 10 -o saida > likwid/$g3-$tam2
    cd ..
    cd $CAM\0 
    likwid-perfctr -c $CORE -g $g1 invmat -r $tam -i 10 -o saida > likwid/$g1-$tam
    likwid-perfctr -c $CORE -g $g1 invmat -r $tam2 -i 10 -o saida > likwid/$g1-$tam2
    likwid-perfctr -c $CORE -g $g2 invmat -r $tam -i 10 -o saida > likwid/$g2-$tam
    likwid-perfctr -c $CORE -g $g2 invmat -r $tam2 -i 10 -o saida > likwid/$g2-$tam2
    likwid-perfctr -c $CORE -g $g3 invmat -r $tam -i 10 -o saida > likwid/$g3-$tam
    likwid-perfctr -c $CORE -g $g3 invmat -r $tam2 -i 10 -o saida > likwid/$g3-$tam2
    cd ..
    tam=$((tam*2))
done
