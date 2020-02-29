reset
set datafile separator ","
set key autotitle columnhead

plot 'traces.csv' using 1:2 with steps lw 3, \
     'traces.csv' using 1:3 with steps lw 3