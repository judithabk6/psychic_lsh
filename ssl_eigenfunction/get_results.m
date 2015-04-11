function [ precision ] = get_results(y, Lambda, dd2, uu2, recall, to_rank)
%GET_RESULTS Summary of this function goes here
%   Detailed explanation goes here

% compute score
alpha2=(dd2 +uu2'*full(Lambda*sparse(double(uu2))))\(uu2'*full(Lambda*y));
f_efunc=uu2*alpha2;

[score, index] = sort(f_efunc, 'descend');


cur_recall = 0;
correct = 0;
total = sum(to_rank>0);
total_ranked = 0;
stop = 0;
precision = 0;
while cur_recall<recall
    stop = stop + 1;
    if abs(to_rank(index(stop)))>0
        correct = correct + (to_rank(index(stop))==1);
        total_ranked = total_ranked + 1;
        cur_recall = correct/total;
        precision = correct/total_ranked;
    end;
end;
end

