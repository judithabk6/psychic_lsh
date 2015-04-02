import numpy as np
ind = np.array(np.genfromtxt('cifar_indexes', delimiter=",", dtype=int, ))
nn = np.array([1] * 50000 + [0] * 10000)

def unpickle(file):
    import cPickle
    fo = open(file, 'rb')
    dict = cPickle.load(fo)
    fo.close()
    return dict

def make_zero_one_format(labs):
    nb_labels = max(labs)
    nb_samples = len(labs)
    new_labels = np.zeros((nb_samples, nb_labels))
    b = range(nb_samples)
    new_labels[b, np.array(labs)-1] = 1
    return new_labels

uu = unpickle('train')
vv = unpickle('test')
uu_new = make_zero_one_format(uu['fine_labels'])
vv_new = make_zero_one_format(vv['fine_labels'])
sq = uu['fine_labels']+vv['fine_labels']
#final = np.hstack((np.column_stack((ind,nn)), sq))
final=np.column_stack((ind,nn,sq))
non_zero_ind = final[:,0]!=0
final = final[non_zero_ind,:]

final = final.astype(np.dtype('a'), copy=False)
fich = open("nodes.txt", "w")
fich.write(str(len(final)) + '\n')
for i in range(len(final)):
    to_write = ' '.join(list(final[i,:])) + '\n'
    fich.write(to_write)
fich.close()