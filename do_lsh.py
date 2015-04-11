# -*- coding: utf-8 -*-

def propagate_label (src, edge, dst):
    if src['labeled']:
        src['f_new'] = src['f_old']
        dst['f_new'] = dst['f_old']
    else:
        dst['f_new'] += src['f_old']*edge['distance']/dst['degree']
        src['f_new'] += dst['f_old']*edge['distance']/src['degree']
    return (src, edge, dst)


import graphlab
import numpy
import random
import nearpy
import time

timing = list()
full_acc = list()

sf_m = graphlab.SFrame.read_csv('nodes.txt',delimiter=' ',column_type_hints=[int,int,int],header=False)
sf_m.rename({'X1': 'node_id', 'X2':'train_or_test', 'X3':'label'})

features = numpy.load('/home/student/project/transformed.npy')
sf_m = sf_m[sf_m['node_id'] != 0]
N = len(sf_m)

print 'Loading Features from {}'.format(features.shape)
for i in range(N):
    sf_m['features'] = features[sf_m['node_id'][i],:]
print 'Done'

sf_m['new_id'] = range(N)
sf_features = sf_m[['new_id', 'features']]


parameters = [(15, 20), (30, 20), (50, 20), (15, 40), (30, 40)]

for param in parameters:
    print 'Param = {}'.format(param)
    results_ = open('resultats_lsh_{}.txt'.format(param), 'w')

    num_nn = param[0]
    num_bins = param[1]

    ann_engine = nearpy.Engine(
        features.shape[1],
        lshashes=[ nearpy.hashes.RandomBinaryProjectionTree('rbp',num_bins, num_nn) ],
        distance=nearpy.distances.EuclideanDistance()
    )
    feat_mat = sf_features.to_dataframe().as_matrix()
    
    edge_list = []
    for src_id, feat in feat_mat:
        ann_engine.store_vector(numpy.transpose(feat), data=src_id)

    print 'adding edges - NN'
    for src_id, feat in feat_mat:
        edge_list += [graphlab.Edge(src_id, dst_id, attr={ 'distance' : dist })
                      for _, dst_id, dist
                      in ann_engine.neighbours(numpy.array(feat))
                      if src_id != dst_id]

    print 'adding {}*2 edges - add_eges'.format(len(edge_list))
    graph = graphlab.SGraph()    
    graph = graph.add_edges(edge_list)
    graph = graph.add_edges(graph.edges, src_field='__dst_id', dst_field='__src_id')
    
    print 'Compute degrees and add reg'
    gamma = 0.0
    graph = graph.add_vertices(
        sf_m.join(
            graph.edges.groupby( ['__src_id'],
            {'degree' : graphlab.aggregate.SUM('distance')}
        ),
        on={'new_id':'__src_id'}), vid_field='new_id'
    )
    graph.vertices['degree'] = graph.vertices.apply(lambda row: row['degree']+gamma)

    
    n_labeled_examples = [0, 1, 2, 3, 5, 8, 10, 16, 20, 40, 60, 100]
    n_classes = 16
    label_set = set(sf_m['label'])
    chosen_classes = random.sample(label_set, n_classes)
    
    n_run = 2
    
    for run in range(n_run):
        for n_positive in n_labeled_examples:
            for cur_class in chosen_classes:
                # Chose test / train sets
                n_negative = (n_classes-1)*2*n_positive
                sf_m.rename({'X1': 'node_id', 'X2':'train_or_test', 'X3':'label'})
                ids_in = sf_m[sf_m['train_or_test']==1][sf_m['label']==cur_class]['new_id']
                ids_out = sf_m[sf_m['train_or_test']==1][sf_m['label']!=cur_class]['new_id']

                positive_examples = random.sample(ids_in, n_positive)
                negative_examples = random.sample(ids_out, n_negative)

                ids_in_test = sf_m[sf_m['train_or_test']==0][sf_m['label']==cur_class]['new_id']
                ids_out_test = sf_m[sf_m['train_or_test']==0][sf_m['label']!=cur_class]['new_id']

                positive_test = random.sample(ids_in_test, min(100, length(ids_in_test)))
                negative_test = random.sample(ids_out_test, 200)

                to_rank = np.zeros(N)
                to_rank[positive_test] = 1
                to_rank[negative_test] = -1

                # Set labels. 1 & -1 for positive / negative examples, 0 elsewhere
                # Set labeled to true for examples

                graph.vertices['f_old'] = 0
                graph.vertices[positive_examples]['f_old'] = 1
                graph.vertices[negative_examples]['f_old'] = -1

                graph.vertices['labeled'] = False
                graph.vertices[positive_examples]['labeled'] = True
                graph.vertices[negative_examples]['labeled'] = True

                print 'Propagating Labels'
                for i in range(3):
                    graph = graph.triple_apply(propagate_label,'f_new')
                    graph.vertices['f_old'] = graph.vertices['f_new']
                    graph.vertices['f_new'] = numpy.zeros([graph.vertices.num_rows(), num_classes])
            
                # rank unlabeled by descending score
                to_score = []
                for x in positive_test:
                    to_score.append((x, graph.vertices[x]['f_old']))
                for x in negative_test:
                    to_score.append((x, graph.vertices[x]['f_old']))

                to_score = sorted(to_score, key=lambda x:x[1], reverse=True)
                
                cur_recall = 0.
                correct = 0.
                total = float(len(positive_test))
                stop = 0
                precision = 0.

                while cur_recall < 0.15:
                    cur_id = to_score[stop][0]
                    if to_rank[cur_id]==1:
                        correct += 1
                    stop += 1
                    cur_recall = correct/total
                    precision = correct/stop

                print 'precision'

        
        
        
