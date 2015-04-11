# -*- coding: utf-8 -*-
"""
Created on Thu Apr  2 17:04:29 2015

@author: student
"""

def propagate_label (src, edge, dst):
    if src['is_labeled']:
        src['f_new'] = src['f_old']
        dst['f_new'] = dst['f_old']
    else:
        src['f_new'] += numpy.multiply(dst['f_old'], edge['distance']/max(src['degree'], 0.01))
        dst['f_new'] += numpy.multiply(src['f_old'], edge['distance']/max(dst['degree'], 0.01))

    return (src, edge, dst)
#%%

def bit_mask(sample,nb):
    bitmask = numpy.zeros(nb)
    bitmask[ sample ] = 1
    return bitmask

#%% 
import graphlab
import numpy
import random
import nearpy
import time
timing = list()
full_acc = list()

results_ = open('resultats_lsh.txt', 'w')

sf_m = graphlab.SFrame.read_csv('/home/student/project/nodes.txt',delimiter=' ',column_type_hints=[int,int,int],header=False)
sf_m.rename({'X1': 'node_id', 'X2':'train_or_test', 'X3':'label'})

features = numpy.load('/home/student/project/sub_transformed.npy')
sf_m = sf_m[sf_m['node_id'] != 0]
num_classes = 25
sf_m = sf_m[sf_m['label'] < num_classes]
N = len(sf_m)
sf_m['features'] = features[0:N,:]
sf_m['big_label'] = sf_m['label'].apply(lambda label: bit_mask(label, num_classes))
sf_m['new_id'] = range(N)
sf_features = sf_m[['new_id', 'features']]

#parameters = [(15, 5), (30, 5), (5, 12), (15, 12), (30, 12), (50, 12), (5, 20), (15, 20), (30, 20), (50, 20), (15, 40), (30, 40)]
parameters = [(15, 20), (30, 20), (50, 20), (15, 40), (30, 40)]

#parameters = [(5, 5), (15, 5), (30, 5), (5, 12), (15, 12), (30, 12), (50, 12), (5, 20), (15, 20), (30, 20), (50, 20), (15, 40), (30, 40)]
for param in parameters:
    results_.write('&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n')
    num_nn = param[0]
    num_bins = param[1]
    results_.write('new parameters : {} neighbours and {} bins \n'.format(num_nn, num_bins))
    

    D=32
    ann_engine = nearpy.Engine(D, lshashes=[ nearpy.hashes.RandomBinaryProjectionTree('rbp',num_bins, num_nn) ], distance=nearpy.distances.EuclideanDistance() )
    feat_mat = sf_features.to_dataframe().as_matrix()
    
    edge_list = []
    for src_id, feat in feat_mat:
        #store_vector takes the features that you want to use for the distances, but you have to also add enough information to recognize the id of the neighbours
        ann_engine.store_vector(numpy.transpose(feat), data=src_id)
    sss = time.time()
    for src_id, feat in feat_mat:
        #remember to avoid self loops
        print src_id, time.time()-sss
        edge_list = edge_list + [graphlab.Edge(src_id, dst_id, attr={ 'distance' : dist }) for discard_var, dst_id, dist in ann_engine.neighbours(numpy.array( feat )) if src_id != dst_id]
    endd = time.time()
    results_.write('construction_time : {}\n'.format(int(endd-sss)))
    graph = graphlab.SGraph()
    
    graph = graph.add_edges(edge_list)
    
    #the graph is directed, remember to make it undirected, and also take notice when you compute the normalization for label propagation
    graph = graph.add_edges(graph.edges, src_field='__dst_id', dst_field='__src_id')
    
    # compute the degree of the nodes
    gamma = 0.0
    reg = lambda row: row['degree']+gamma
    
    graph = graph.add_vertices( sf_m.join(graph.edges.groupby( ['__src_id'],{'degree' : graphlab.aggregate.SUM('distance')} ), on={'new_id':'__src_id'}), vid_field='new_id')
    graph.vertices['degree'] = graph.vertices.apply(reg)
    # let's build the data structures for the label propagation
    
    label_vect = numpy.zeros(N)
    
    
    # select a random subset (say 200) of labels
    nb_labeled_examples = [0, 1, 2, 3, 5, 8, 10, 16, 20, 40, 60, 100]
    C = 10
    label_set = set(sf_m['label'])
    used_labels = random.sample(label_set, C)
    big_matrix = numpy.zeros((C, len(nb_labeled_examples )))
    starting = time.time()
    for zzz, pos in enumerate(nb_labeled_examples):
        rrr = []
        print pos

        # draw pos positive training examples
        
        
        used_label_map = {k:1 for k in used_labels}
        unused_labels = set(range(num_classes)).difference(set(used_labels))
        used_label_map.update({k : 0 for k in unused_labels})
        sf_m['is_used'] = sf_m.apply(lambda vert : used_label_map[ vert['label'] ])
        negative_train_list = sf_m[sf_m['train_or_test']==1 and sf_m['is_used']==0]
        l_idx = random.sample(negative_train_list, C*pos)
        for lab in used_labels:
            positive_train_list = sf_m[sf_m['train_or_test']==1 and sf_m['label']==lab][['new_id']]
            l_idx += random.sample(positive_train_list, pos)
        u_idx = set(xrange(N))
        l_idx = [i['new_id'] for i in l_idx]
        l_idx = set(l_idx)
        u_idx = u_idx.difference(l_idx)
        label_map = {k : 1 for k in l_idx}
        label_map.update({k : 0 for k in u_idx})
        
        # obscure the unlabeled data
        graph.vertices['label_desc'] = graph.vertices.apply(lambda vert: numpy.array( vert['big_label'] ) if vert['__id'] in l_idx else numpy.zeros(num_classes) )
        
        # keep track of what is labeled
        graph.vertices['is_labeled'] = graph.vertices.apply(lambda vert : label_map[ vert['__id'] ])
        
        # initialize the f vector to the labels
        graph.vertices['f_old'] = graph.vertices['label_desc']
        graph.vertices['f_new'] = numpy.zeros([graph.vertices.num_rows(),num_classes])
        
            #iterate to propagate the labels
        for i in range(3):
            graph = graph.triple_apply(propagate_label,'f_new')
            graph.vertices['f_old'] = graph.vertices['f_new']
            graph.vertices['f_new'] = numpy.zeros([graph.vertices.num_rows(), num_classes])
            

            
        for lab in used_labels:
            print lab
            # draw the test evaluation set
            positive_test_list = sf_m[sf_m['train_or_test']==0 and sf_m['label']==lab][['new_id']]
            negative_test_list = sf_m[sf_m['train_or_test']==0 and sf_m['label']!=lab][['new_id']]
            testing_ids = random.sample(positive_test_list, 100) + random.sample(negative_test_list, 200)
            testing_ids = [i['new_id'] for i in testing_ids]        
            testing_ids = set(testing_ids)
            #evaluate the final labeling
            non_test_ids = set(xrange(N))
            non_test_ids = non_test_ids.difference(testing_ids)
            test_map = {k : 1 for k in testing_ids}
            test_map.update({k : 0 for k in non_test_ids})
            graph.vertices['is_tested'] = graph.vertices.apply(lambda vert : test_map[ vert['__id'] ])
            final_eval = graph.vertices[graph.vertices['is_tested'] == 1]
            final_eval['lab_score'] = final_eval['f_old'].apply(lambda x: x[lab])
            fin = final_eval[['label', 'lab_score']].to_dataframe().as_matrix()
            
            a = numpy.argsort(-fin[:,1])
            fin = fin[a,:]
            fin[:,0] = fin[:,0]==lab
            ranking = numpy.cumsum(fin[:,0])
            stopping = numpy.argmax(ranking>=15)
            precision_at_15_recall = 15.0/stopping
            rrr.append(precision_at_15_recall)
        big_matrix[:,zzz] = rrr
    numpy.save('neib_{}_hash_{}.npy'.format(num_nn, num_bins), big_matrix)
    ending = time.time()
    mean_ = numpy.mean(big_matrix,0)
    mean_ = [str(i) for i in mean_]
    results_.write(' '.join(mean_) + '\n')
    std_ = numpy.std(big_matrix,0)
    std_ = [str(i) for i in std_]
    results_.write(' '.join(std_) + '\n')
    results_.write('the second step took {} seconds \n'.format(int(ending-starting)))
    
results_.close()
    
        

        
        
        
