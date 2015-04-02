
clear; close all;
 
%%% user parameters
NUM_EVECS = 5; % how many eigenvectors/eigenfunctions to use
SIGMA = 0.2; % controls affinity in graph Laplacian
n_labels = 100;

%%
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


y = zeros(n_nodes, n_labels);

id_train = 1:n_nodes;
id_test  = id_train(data(:,2)==0);
id_train = id_train(data(:,2)==1);

labelled = id_train;

for i=labelled
    y(i,data(i,3))=1;
end;

% build sparse diagonal Lambda matrix
labelled = double(labelled);
n_nodes = double(n_nodes);
Lambda = sparse(labelled,labelled,1000*ones(size(labelled)),n_nodes, n_nodes);

for i=labelled
    Lambda(i,i) = 1000;
end

 
 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Now try approximate eigenvectors, as found by eigenfunction approach
 
% compute approximate eigenvectors using eigenfunction approach
[dd2,uu2] = eigenfunctions(positions,SIGMA,NUM_EVECS);
disp('eigenfunctions found');
alpha2=(dd2 +uu2'*Lambda*uu2)\(uu2'*Lambda*y);

size(alpha2)

n_ok = 0;
for i=id_test
    [~, label_us] = max(alpha2(i,:));
    if label_us == data(i,3)
        n_ok = n_ok + 1;
    end
end

n_ok

 
