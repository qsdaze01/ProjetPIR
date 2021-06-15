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

title = 'Frequence'	
plot = pd.DataFrame(val_read,x)
#XN,YN = augment(x,y,10)
#augmented = pd.DataFrame(YN,XN)
plot.columns = {title}

#Writer = animation.writers['ffmpeg']
#writer = Writer(fps=5, metadata=dict(artist='Me'), bitrate=1800)

fig = plt.figure(figsize=(10,6))
plt.xlim(0, 1000)
plt.ylim(np.min(plot)[0], np.max(plot)[0]+10)
plt.xlabel('Time',fontsize=20)
plt.ylabel(title,fontsize=20)
plt.title('Frequency',fontsize=20)

def animate(i):
    data = plot.iloc[:int(i+5)] #select data range
    p = sns.lineplot(x=data.index, y=data[title], data=data, color="r")
    p.tick_params(labelsize=17)
    plt.setp(p.lines,linewidth=0.2)

ani = matplotlib.animation.FuncAnimation(fig, animate, frames=1200,interval=1, repeat=True)
ani.save('lune2.mp4', fps=24, dpi=200)

#writer = animation.FFMpegWriter(fps=70, metadata=dict(artist='Me'), bitrate=1800)
#ani.save("movie.mp4", writer=writer)
#plt.show()