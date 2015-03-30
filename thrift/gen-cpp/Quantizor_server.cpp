#include "Quantizor.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;
using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

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
  }


  void loadGraph(string fileName, Graph& toLoad) {
    fstream ifs(fileName, ios::in);
    int n_node, n_edges;

  }

};

int main(int argc, char **argv) {
  int port = 9090;
  shared_ptr<QuantizorHandler> handler(new QuantizorHandler());
  shared_ptr<TProcessor> processor(new QuantizorProcessor(handler));
  shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}

