struct Edge {
  1: i32 dest,
  2: double length
}

struct Graph {  
  1: map<i32, set<i32>> cluster,
  2: map<i32, set<Edge>> neighbors,
  3: map<i32, set<i32>> labels,
}


service Quantizor {
   Graph quantize(1:string graphFile, 2:string method, 3:i32 maxSize, 4:list<double> params)
}