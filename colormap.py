import math
basecount = 4

cmapcount = 80

def interpolate(g):
    top = math.ceil(g*(basecount - 1))
    bottom = math.floor(g*(basecount - 1))
    

for i in range(cmapcount):
    g = float(i) / (cmapcount - 1)
    
    print "%d %f %d %d" % (i,g*(basecount - 1))
    
    
    
