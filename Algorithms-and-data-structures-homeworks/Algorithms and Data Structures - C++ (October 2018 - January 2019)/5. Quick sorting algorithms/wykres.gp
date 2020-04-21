set terminal "pdfcairo" enhance size 6,4
set output "wykres.pdf"
set xlabel "n"
set ylabel "s"
set xtics (10000, 20000, 40000, 80000, 160000)
set ytics 0, .01, 0.1

set style line 2  lc rgb '#0060ad' lt 1 lw 1.5 pointtype 7 pointsize 0.5 # --- blue
set style line 3  lc rgb '#ffd100' lt 1 lw 1.5 pointtype 7 pointsize 0.5 #      .
set style line 4  lc rgb '#ff7d00' lt 1 lw 1.5 pointtype 7 pointsize 0.5 #      .
set style line 5  lc rgb '#97ff00' lt 1 lw 1.5 pointtype 7 pointsize 0.5 #      .
set style line 6  lc rgb '#334d73' lt 1 lw 1.5 pointtype 7 pointsize 0.5 #      .
set style line 7  lc rgb '#000000' lt 1 lw 1.5 pointtype 7 pointsize 0.5 #      .
set style line 8  lc rgb '#00ffff' lt 1 lw 1.5 pointtype 7 pointsize 0.5 #      .
set style line 9  lc rgb '#ff00ff' lt 1 lw 1.5 pointtype 7 pointsize 0.5 #      .

plot "dane.dat" u 1:3 title "Counting O(n)" w linespoints ls 2, "" u 1:6 title "Std O(n*logn)" w linespoints ls 3, "" u 1:7  title "QSort O(n*logn)" w linespoints ls 4, "" u 1:8  title "IT Heap O(n*logn)" w linespoints ls 5, "" u 1:9  title "R Heap O(n*logn)" w linespoints ls 6, "" u 1:10  title "R Quick O(n*logn)" w linespoints ls 7, "" u 1:11  title "IT Quick O(n*logn)" w linespoints ls 8, "" u 1:12  title "R Merge O(n*logn)" w linespoints ls 9