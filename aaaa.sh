g[1]=L3
g[2]=L2CACHE
g[3]=FLOPS_AVX
cd sba16-thcf16
CORE=0
for (( i = 1; i < 4; i++ )); do
	echo $g[%i]
	echo ${g[$i]}
done