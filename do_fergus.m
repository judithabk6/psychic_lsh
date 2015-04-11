
clear; close all;
 
%%% user parameters
NUM_EVECS = 256; % how many eigenvectors/eigenfunctions to use
SIGMA = 0.2; % controls affinity in graph Laplacian
n_labels = 100;

load('data.mat');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Load data and labels

m = memmapfile('matlab_gist_PCA.raw', 'Format',...
                {'single', [79302017 32], 'x'});

fileId = fopen('nodes.txt');
C = textscan(fileId, '%d');
C = C{1};
n_nodes = C(1);
data = reshape(C(2:end), 3, n_nodes)';
positions = zeros(n_nodes,32);
for i=1:n_nodes
    positions(i,:) = m.Data.x(data(i,1),:);
end;


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Set labelled / unlabelled

n_classes = 16;
recall = 0.15;


chosen_classes = randsample(1:n_labels,n_classes);
ids = 1:n_nodes;

n_run = 10;
max_positive = 100;
precision = zeros(n_run, max_positive);

[dd2,uu2] = eigenfunctions(positions,SIGMA,NUM_EVECS);
for run=1:n_run
    run
    for n_positive=1:max_positive
        for class=chosen_classes
            n_negative = (n_classes-1)*2*n_positive;
            %chose test / train sets
            ids_in = ids((data(:,3)==class) & (data(:,2)==1));
            ids_out = ids((data(:,3)~=class) & (data(:,2)==1));
            positive_examples = randsample(ids_in, n_positive);
            negative_examples = randsample(ids_out, n_negative);

            ids_in_test = ids((data(:,3)==class) & (data(:,2)==0));
            ids_out_test = ids((data(:,3)~=class) & (data(:,2)==0));
            positive_test = randsample(ids_in_test, min(100, length(ids_in_test)));
            negative_test = randsample(ids_out_test, 200);
            to_rank= zeros(n_nodes, 1);
            to_rank(positive_test)=1;
            to_rank(negative_test)=-1;

            %build y / lambda
            y = zeros(n_nodes, 1);
            y(positive_examples)=1;
            y(negative_examples)=-1;
            is_labelled = abs(y)>0;
            Lambda = sparse(double(n_nodes), double(n_nodes));
            for k=ids(is_labelled)
                Lambda(k,k) = 50;
            end;

            % get results
            result = get_results(y, Lambda, dd2, uu2, recall, to_rank);
            precision(run, n_positive) =  precision(run, n_positive) + result;
        end
        precision(run, n_positive) = precision(run, n_positive)/n_classes;
    end
end