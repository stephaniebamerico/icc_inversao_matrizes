#!/usr/bin/gnuplot

set terminal pngcairo size 600,600 enhanced font 'Courier,10'
set grid

set style line 1 lc rgb '#343d3a' lt 1 lw 3 pt 5 ps 1 # --- red
set style line 2 lc rgb '#fd2e58' lt 1 lw 3 pt 7 ps 1   # --- yellow
set style line 3 lc rgb '#efa93a' lt 1 lw 3 pt 9 ps 1   # --- blue
set style line 4 lc rgb '#5fd0d4' lt 1 lw 3 pt 13 ps 1   # --- green



set title 'Teste de Tempo'
set logscale y
set logscale x 2
set output 'xyTempo.png' 
plot 'xyTempo.dat' index 0 title 'Original op1' with linespoints ls 1, \
     ''                   index 1 title 'Original op2' with linespoints ls 2, \
     ''                   index 2 title 'Otimizado op1' with linespoints ls 3, \
     ''                   index 3 title 'Otimizado op2' with linespoints ls 4
     
