getValue(row,col,filename) = real(system('awk -v FS='','' ''{if (NR == '.row.') print $'.col.'}'' '.filename.''))


file = "./output/out2.csv"

nline=11

x=getValue(nline,1,file)
y=getValue(nline,2,file)
z=getValue(nline,3,file)
dx=5; dy=5;
dzdx=getValue(nline,4,file)
dzdy=getValue(nline,5,file)

set arrow 1 from x,y,z to x+dx,y,z+dzdx*dx
set arrow 2 from x,y,z to x,y+dy,z+dzdy*dy
set datafile separator ","
splot file u 1:2:3 with points

