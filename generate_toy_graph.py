import numpy as np

n = 25

xs = np.linspace(0,2, n)
ys = np.linspace(0,1, n)

out = open('toy_{}.graph'.format(n), 'w')

out.write('{} {} 2\n'.format(n**2, n**4))

points = []

for (i,x) in enumerate(xs):
    for (j,y) in enumerate(ys):
        out.write('{} {} '.format(x,y))
        if i*j==0:
            out.write('1 -1')
        elif i==n-1 and j==n-1:
            out.write('1 1')
        else:
            out.write('0')
        out.write('\n')
        points.append(np.array([x,y]) + np.random.normal(0,0.01,(1,2)))

points = np.vstack(points)

for (i,a) in enumerate(points):
    for (j,b) in enumerate(points):
        out.write('{} {} {}\n'.format(i,j, np.linalg.norm(a-b)))
