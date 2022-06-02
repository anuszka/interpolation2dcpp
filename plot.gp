file = "./output/out2.csv"
x=5; y=5; z=0.625;
dx=5; dy=5;
dzdx=0.025; dzdy=0.025;
set arrow 1 from x,y,z to x+dx,y,z+dzdx*dx
set arrow 2 from x,y,z to x,y+dy,z+dzdy*dy
set datafile separator ","
splot file u 1:2:3 with points
