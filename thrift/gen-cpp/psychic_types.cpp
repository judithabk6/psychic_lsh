/**
 * Autogenerated by Thrift Compiler (0.9.2)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#include "psychic_types.h"

#include <algorithm>
#include <ostream>

#include <thrift/TToString.h>




Edge::~Edge() throw() {
}


void Edge::__set_dest(const int32_t val) {
  this->dest = val;
}

void Edge::__set_length(const double val) {
  this->length = val;
}

const char* Edge::ascii_fingerprint = "0B663F1913C9C6F43150B524A8B76386";
const uint8_t Edge::binary_fingerprint[16] = {0x0B,0x66,0x3F,0x19,0x13,0xC9,0xC6,0xF4,0x31,0x50,0xB5,0x24,0xA8,0xB7,0x63,0x86};

uint32_t Edge::read(::apache::thrift::protocol::TProtocol* iprot) {

  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->dest);
          this->__isset.dest = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_DOUBLE) {
          xfer += iprot->readDouble(this->length);
          this->__isset.length = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t Edge::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  oprot->incrementRecursionDepth();
  xfer += oprot->writeStructBegin("Edge");

  xfer += oprot->writeFieldBegin("dest", ::apache::thrift::protocol::T_I32, 1);
  xfer += oprot->writeI32(this->dest);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("length", ::apache::thrift::protocol::T_DOUBLE, 2);
  xfer += oprot->writeDouble(this->length);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  oprot->decrementRecursionDepth();
  return xfer;
}

void swap(Edge &a, Edge &b) {
  using ::std::swap;
  swap(a.dest, b.dest);
  swap(a.length, b.length);
  swap(a.__isset, b.__isset);
}

Edge::Edge(const Edge& other0) {
  dest = other0.dest;
  length = other0.length;
  __isset = other0.__isset;
}
Edge& Edge::operator=(const Edge& other1) {
  dest = other1.dest;
  length = other1.length;
  __isset = other1.__isset;
  return *this;
}
std::ostream& operator<<(std::ostream& out, const Edge& obj) {
  using apache::thrift::to_string;
  out << "Edge(";
  out << "dest=" << to_string(obj.dest);
  out << ", " << "length=" << to_string(obj.length);
  out << ")";
  return out;
}


Graph::~Graph() throw() {
}


void Graph::__set_cluster(const std::map<int32_t, std::set<int32_t> > & val) {
  this->cluster = val;
}

void Graph::__set_neighbors(const std::map<int32_t, std::set<Edge> > & val) {
  this->neighbors = val;
}

const char* Graph::ascii_fingerprint = "94DF3A228FA8CE3F91342E0CAE116FCD";
const uint8_t Graph::binary_fingerprint[16] = {0x94,0xDF,0x3A,0x22,0x8F,0xA8,0xCE,0x3F,0x91,0x34,0x2E,0x0C,0xAE,0x11,0x6F,0xCD};

uint32_t Graph::read(::apache::thrift::protocol::TProtocol* iprot) {

  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_MAP) {
          {
            this->cluster.clear();
            uint32_t _size2;
            ::apache::thrift::protocol::TType _ktype3;
            ::apache::thrift::protocol::TType _vtype4;
            xfer += iprot->readMapBegin(_ktype3, _vtype4, _size2);
            uint32_t _i6;
            for (_i6 = 0; _i6 < _size2; ++_i6)
            {
              int32_t _key7;
              xfer += iprot->readI32(_key7);
              std::set<int32_t> & _val8 = this->cluster[_key7];
              {
                _val8.clear();
                uint32_t _size9;
                ::apache::thrift::protocol::TType _etype12;
                xfer += iprot->readSetBegin(_etype12, _size9);
                uint32_t _i13;
                for (_i13 = 0; _i13 < _size9; ++_i13)
                {
                  int32_t _elem14;
                  xfer += iprot->readI32(_elem14);
                  _val8.insert(_elem14);
                }
                xfer += iprot->readSetEnd();
              }
            }
            xfer += iprot->readMapEnd();
          }
          this->__isset.cluster = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_MAP) {
          {
            this->neighbors.clear();
            uint32_t _size15;
            ::apache::thrift::protocol::TType _ktype16;
            ::apache::thrift::protocol::TType _vtype17;
            xfer += iprot->readMapBegin(_ktype16, _vtype17, _size15);
            uint32_t _i19;
            for (_i19 = 0; _i19 < _size15; ++_i19)
            {
              int32_t _key20;
              xfer += iprot->readI32(_key20);
              std::set<Edge> & _val21 = this->neighbors[_key20];
              {
                _val21.clear();
                uint32_t _size22;
                ::apache::thrift::protocol::TType _etype25;
                xfer += iprot->readSetBegin(_etype25, _size22);
                uint32_t _i26;
                for (_i26 = 0; _i26 < _size22; ++_i26)
                {
                  Edge _elem27;
                  xfer += _elem27.read(iprot);
                  _val21.insert(_elem27);
                }
                xfer += iprot->readSetEnd();
              }
            }
            xfer += iprot->readMapEnd();
          }
          this->__isset.neighbors = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t Graph::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  oprot->incrementRecursionDepth();
  xfer += oprot->writeStructBegin("Graph");

  xfer += oprot->writeFieldBegin("cluster", ::apache::thrift::protocol::T_MAP, 1);
  {
    xfer += oprot->writeMapBegin(::apache::thrift::protocol::T_I32, ::apache::thrift::protocol::T_SET, static_cast<uint32_t>(this->cluster.size()));
    std::map<int32_t, std::set<int32_t> > ::const_iterator _iter28;
    for (_iter28 = this->cluster.begin(); _iter28 != this->cluster.end(); ++_iter28)
    {
      xfer += oprot->writeI32(_iter28->first);
      {
        xfer += oprot->writeSetBegin(::apache::thrift::protocol::T_I32, static_cast<uint32_t>(_iter28->second.size()));
        std::set<int32_t> ::const_iterator _iter29;
        for (_iter29 = _iter28->second.begin(); _iter29 != _iter28->second.end(); ++_iter29)
        {
          xfer += oprot->writeI32((*_iter29));
        }
        xfer += oprot->writeSetEnd();
      }
    }
    xfer += oprot->writeMapEnd();
  }
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("neighbors", ::apache::thrift::protocol::T_MAP, 2);
  {
    xfer += oprot->writeMapBegin(::apache::thrift::protocol::T_I32, ::apache::thrift::protocol::T_SET, static_cast<uint32_t>(this->neighbors.size()));
    std::map<int32_t, std::set<Edge> > ::const_iterator _iter30;
    for (_iter30 = this->neighbors.begin(); _iter30 != this->neighbors.end(); ++_iter30)
    {
      xfer += oprot->writeI32(_iter30->first);
      {
        xfer += oprot->writeSetBegin(::apache::thrift::protocol::T_STRUCT, static_cast<uint32_t>(_iter30->second.size()));
        std::set<Edge> ::const_iterator _iter31;
        for (_iter31 = _iter30->second.begin(); _iter31 != _iter30->second.end(); ++_iter31)
        {
          xfer += (*_iter31).write(oprot);
        }
        xfer += oprot->writeSetEnd();
      }
    }
    xfer += oprot->writeMapEnd();
  }
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  oprot->decrementRecursionDepth();
  return xfer;
}

void swap(Graph &a, Graph &b) {
  using ::std::swap;
  swap(a.cluster, b.cluster);
  swap(a.neighbors, b.neighbors);
  swap(a.__isset, b.__isset);
}

Graph::Graph(const Graph& other32) {
  cluster = other32.cluster;
  neighbors = other32.neighbors;
  __isset = other32.__isset;
}
Graph& Graph::operator=(const Graph& other33) {
  cluster = other33.cluster;
  neighbors = other33.neighbors;
  __isset = other33.__isset;
  return *this;
}
std::ostream& operator<<(std::ostream& out, const Graph& obj) {
  using apache::thrift::to_string;
  out << "Graph(";
  out << "cluster=" << to_string(obj.cluster);
  out << ", " << "neighbors=" << to_string(obj.neighbors);
  out << ")";
  return out;
}


