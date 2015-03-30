from psychic import Quantizor
from psychic.ttypes import *

from thrift.transport import TSocket, TTransport

class QuantizorClient(object):

    def __init__(self, host, port):
        self.socket = TSocket.TSocket(host, port)
        self.transport = TTransport.TBufferedTransport(self.socket)
        self.protocol = TBinaryProtocol.TBinaryProtocol(self.transport)
        self.client = Quantizor.Client(self.protocol)
        self.transport.open()

    def __del__(self):
        self.transport.close()

    def quantize(self, graphFile, method, maxSize, params):
        return self.client.quantize(graphFile, method, maxSize, params)