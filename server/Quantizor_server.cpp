#include "Quantizor.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <fstream>

using namespace std;
using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

double distance(Node& a, Node &b){
  double sum=0;
  for(int i=0;i<a.position.size();i++)
    sum += pow(a.position[i]-b.position[i], 2);
  return sqrt(sum);
}

class QuantizorHandler : virtual public QuantizorIf {
 public:
  QuantizorHandler() {
  }

  void quantize(
    Graph& _return, const std::string& graphFile,
    const std::string& method, const int maxSize,
    const std::vector<double> & params) {

    cout << "quantize "<<graphFile<<endl;
    Graph graph;
    loadGraph(graphFile, graph);
    int nb_edges = 0;
    for(auto node: graph.neighbors)
      nb_edges += node.second.size();
    cout << "Loaded : "<<graph.nodes.size()<<" nodes and "
         <<nb_edges/2 << " relations."<<endl;
  }


  void loadGraph(string fileName, Graph& toLoad) {
    fstream ifs(fileName, ios::in);
    int n_nodes, n_edges, n_labels, label, n_dim;
    ifs >> n_nodes >> n_edges >> n_dim;
    for(int i=0;i<n_nodes;i++){
      toLoad.neighbors[i] = set<Edge>();

      Node n;
      for(int d=0;d<n_dim;d++){
        double v;
        ifs >> v;
        n.position.push_back(v);
      }

      ifs >> n_labels;
      for(int k=0;k<n_labels;k++){
        ifs >> label;
        n.labels.push_back(label);
      }
      toLoad.nodes.push_back(n);
    }
    int a, b;
    double length;
    for(int i=0;i<n_edges;i++){
      ifs >> a >> b >> length;
      toLoad.neighbors[a].insert(Edge(b, length));
      // graph is symmetric
      toLoad.neighbors[b].insert(Edge(a, length));
    }
  }

};

int main(int argc, char **argv) {
  int port = 9090;
  boost::shared_ptr<QuantizorHandler> handler(new QuantizorHandler());
  boost::shared_ptr<TProcessor> processor(new QuantizorProcessor(handler));
  boost::shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  boost::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  boost::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}

