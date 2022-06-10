getValue(row,col,file_outname) = real(system('awk -v FS='','' ''{if (NR == '.row.') print $'.col.'}'' '.file_outname.''))


file_out = "./output/out1.csv"
file_in = "./input/in.csv"

nline=46

x=getValue(nline,1,file_out)
y=getValue(nline,2,file_out)
z=getValue(nline,3,file_out)
dx=3; dy=3;
dzdx=getValue(nline,4,file_out)
dzdy=getValue(nline,5,file_out)

set arrow 1 from x,y,z to x+dx,y,z+dzdx*dx
set arrow 2 from x,y,z to x,y+dy,z+dzdy*dy
set datafile separator ","
set xlabel "x"
set ylabel "y"
set zlabel 'z'
set view 65, 300
splot \
file_in u 1:2:3 lt 7 title "Data",\
file_out u 1:2:3 with points title "Interpolation"