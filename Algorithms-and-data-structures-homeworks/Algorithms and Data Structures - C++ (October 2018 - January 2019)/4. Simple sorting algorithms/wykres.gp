set terminal "pdfcairo" enhance size 6,4
set output "wykres.pdf"
set xlabel "n"
set ylabel "s"
set xtics (10000, 20000, 40000, 80000, 160000)
set ytics 0, 5, 35

set style line 2  lc rgb '#0060ad' lt 1 lw 1.5 pointtype 2 pointsize 0.5 # --- blue
set style line 3  lc rgb '#00ffff' lt 1 lw 1.5 pointtype 3 pointsize 0.5 #      .
set style line 4  lc rgb '#ff7d00' lt 1 lw 1.5 pointtype 4 pointsize 0.5 #      .
set style line 5  lc rgb '#97ff00' lt 1 lw 1.5 pointtype 5 pointsize 0.5 #      .
set style line 6  lc rgb '#334d73' lt 1 lw 1.5 pointtype 6 pointsize 0.5 #      .
set style line 7  lc rgb '#000000' lt 1 lw 1.5 pointtype 7 pointsize 0.5 #      .

plot "dane.dat" u 1:2 title "Bubble" w linespoints ls 2, "" u 1:3 title "Counting" w linespoints ls 3, "" u 1:4  title "Insertion" w linespoints ls 4, "" u 1:5  title "Selection" w linespoints ls 5, "" u 1:6  title "Std" w linespoints ls 6