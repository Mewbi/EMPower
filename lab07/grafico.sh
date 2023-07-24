#!/bin/sh
ARQUIVODADOS=/home/pi/ESZB026-17-6-2022C/lab07/dados
ARQUIVOSAIDA=/home/pi/ESZB026-17-6-2022C/lab07/dados

arq="${ARQUIVODADOS}1.txt"
arqSaida="${ARQUIVOSAIDA}1.png"
gnuplot << EOF
set title "Título"
set ylabel "Eixo Y"
set xlabel "Eixo X"
set terminal png
set output "$arqSaida"
plot "$arq" \
     linecolor rgb "#2011ad" \
     linetype 1 \
     linewidth 1 \
     pointtype 1 \
     pointsize 1.0 \
     title "meus dados" \
     with linespoints
EOF

arq="${ARQUIVODADOS}2.txt"
arqSaida="${ARQUIVOSAIDA}2.png"
gnuplot << EOF
set title "Título"
set ylabel "Eixo Y"
set xlabel "Eixo X"
set terminal png
set output "$arqSaida"
plot "$arq" \
     linecolor rgb "#ff6464" \
     linetype 2 \
     linewidth 2 \
     pointtype 3 \
     pointsize 2.0 \
     title "meus dados" \
     with linespoints
EOF

arq="${ARQUIVODADOS}3.txt"
arqSaida="${ARQUIVOSAIDA}3.png"
gnuplot << EOF
set title "Título"
set ylabel "Eixo Y"
set xlabel "Eixo X"
set terminal png
set output "$arqSaida"
plot "$arq" \
     linecolor rgb "#91c483" \
     linetype 1 \
     linewidth 4 \
     pointtype 2 \
     pointsize 3.0 \
     title "meus dados" \
     with linespoints
EOF
