import sys
import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib
import matplotlib.pyplot as plt
import matplotlib.animation as animation


x = range(1000)
val_read = [];
with open(sys.argv[1], 'r') as f:
    d = f.readlines()
    for i in d:
        val_read.append((int)(i)) 

title = 'Heroin Overdoses'	
plot = pd.DataFrame(val_read,x)
#XN,YN = augment(x,y,10)
#augmented = pd.DataFrame(YN,XN)
plot.columns = {title}

Writer = animation.writers['ffmpeg']
writer = Writer(fps=20, metadata=dict(artist='Me'), bitrate=1800)

fig = plt.figure(figsize=(10,6))
plt.xlim(0, 1000)
plt.ylim(np.min(plot)[0], np.max(plot)[0])
plt.xlabel('Time',fontsize=20)
plt.ylabel(title,fontsize=20)
plt.title('Frequency',fontsize=20)

def animate(i):
    data = plot.iloc[:int(i+1)] #select data range
    p = sns.lineplot(x=data.index, y=data[title], data=data, color="r")
    p.tick_params(labelsize=17)
    plt.setp(p.lines,linewidth=1)

ani = matplotlib.animation.FuncAnimation(fig, animate, frames=500, repeat=True)

plt.show()