set term tikz monochrome font '\ttfamily,14.4'
set output "ex2.tex"
set logscale y
set key spacing 3
set xrange [0:160]
set yrange [1e-16:1]
set format y "$10^{%L}$"
set xlabel "$m=2n+1$"
set ylabel "maximum error"
plot "SE_ex2.dat" using 1:2 w lp title "SE-Sinc" lt 2 pt 9 ps 1, "DE_ex2.dat" using 1:2 w lp title "DE-Sinc" lt 1 pt 7 ps 1
