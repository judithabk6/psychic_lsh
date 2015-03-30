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




Node::~Node() throw() {
}


void Node::__set_labels(const std::vector<int32_t> & val) {
  this->labels = val;
}

void Node::__set_position(const std::vector<double> & val) {
  this->position = val;
}

const char* Node::ascii_fingerprint = "A2801F02B81B73CF35BAC5309B029DC3";
const uint8_t Node::binary_fingerprint[16] = {0xA2,0x80,0x1F,0x02,0xB8,0x1B,0x73,0xCF,0x35,0xBA,0xC5,0x30,0x9B,0x02,0x9D,0xC3};

uint32_t Node::read(::apache::thrift::protocol::TProtocol* iprot) {

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
        if (ftype == ::apache::thrift::protocol::T_LIST) {
          {
            this->labels.clear();
            uint32_t _size0;
            ::apache::thrift::protocol::TType _etype3;
            xfer += iprot->readListBegin(_etype3, _size0);
            this->labels.resize(_size0);
            uint32_t _i4;
            for (_i4 = 0; _i4 < _size0; ++_i4)
            {
              xfer += iprot->readI32(this->labels[_i4]);
            }
            xfer += iprot->readListEnd();
          }
          this->__isset.labels = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_LIST) {
          {
            this->position.clear();
            uint32_t _size5;
            ::apache::thrift::protocol::TType _etype8;
            xfer += iprot->readListBegin(_etype8, _size5);
            this->position.resize(_size5);
            uint32_t _i9;
            for (_i9 = 0; _i9 < _size5; ++_i9)
            {
              xfer += iprot->readDouble(this->position[_i9]);
            }
            xfer += iprot->readListEnd();
          }
          this->__isset.position = true;
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

uint32_t Node::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  oprot->incrementRecursionDepth();
  xfer += oprot->writeStructBegin("Node");

  xfer += oprot->writeFieldBegin("labels", ::apache::thrift::protocol::T_LIST, 1);
  {
    xfer += oprot->writeListBegin(::apache::thrift::protocol::T_I32, static_cast<uint32_t>(this->labels.size()));
    std::vector<int32_t> ::const_iterator _iter10;
    for (_iter10 = this->labels.begin(); _iter10 != this->labels.end(); ++_iter10)
    {
      xfer += oprot->writeI32((*_iter10));
    }
    xfer += oprot->writeListEnd();
  }
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("position", ::apache::thrift::protocol::T_LIST, 2);
  {
    xfer += oprot->writeListBegin(::apache::thrift::protocol::T_DOUBLE, static_cast<uint32_t>(this->position.size()));
    std::vector<double> ::const_iterator _iter11;
    for (_iter11 = this->position.begin(); _iter11 != this->position.end(); ++_iter11)
    {
      xfer += oprot->writeDouble((*_iter11));
    }
    xfer += oprot->writeListEnd();
  }
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  oprot->decrementRecursionDepth();
  return xfer;
}

void swap(Node &a, Node &b) {
  using ::std::swap;
  swap(a.labels, b.labels);
  swap(a.position, b.position);
  swap(a.__isset, b.__isset);
}

Node::Node(const Node& other12) {
  labels = other12.labels;
  position = other12.position;
  __isset = other12.__isset;
}
Node& Node::operator=(const Node& other13) {
  labels = other13.labels;
  position = other13.position;
  __isset = other13.__isset;
  return *this;
}
std::ostream& operator<<(std::ostream& out, const Node& obj) {
  using apache::thrift::to_string;
  out << "Node(";
  out << "labels=" << to_string(obj.labels);
  out << ", " << "position=" << to_string(obj.position);
  out << ")";
  return out;
}


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

Edge::Edge(const Edge& other14) {
  dest = other14.dest;
  length = other14.length;
  __isset = other14.__isset;
}
Edge& Edge::operator=(const Edge& other15) {
  dest = other15.dest;
  length = other15.length;
  __isset = other15.__isset;
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

void Graph::__set_nodes(const std::vector<Node> & val) {
  this->nodes = val;
}

const char* Graph::ascii_fingerprint = "7289290673F41D4718449FBB25CEAAB4";
const uint8_t Graph::binary_fingerprint[16] = {0x72,0x89,0x29,0x06,0x73,0xF4,0x1D,0x47,0x18,0x44,0x9F,0xBB,0x25,0xCE,0xAA,0xB4};

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
            uint32_t _size16;
            ::apache::thrift::protocol::TType _ktype17;
            ::apache::thrift::protocol::TType _vtype18;
            xfer += iprot->readMapBegin(_ktype17, _vtype18, _size16);
            uint32_t _i20;
            for (_i20 = 0; _i20 < _size16; ++_i20)
            {
              int32_t _key21;
              xfer += iprot->readI32(_key21);
              std::set<int32_t> & _val22 = this->cluster[_key21];
              {
                _val22.clear();
                uint32_t _size23;
                ::apache::thrift::protocol::TType _etype26;
                xfer += iprot->readSetBegin(_etype26, _size23);
                uint32_t _i27;
                for (_i27 = 0; _i27 < _size23; ++_i27)
                {
                  int32_t _elem28;
                  xfer += iprot->readI32(_elem28);
                  _val22.insert(_elem28);
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
            uint32_t _size29;
            ::apache::thrift::protocol::TType _ktype30;
            ::apache::thrift::protocol::TType _vtype31;
            xfer += iprot->readMapBegin(_ktype30, _vtype31, _size29);
            uint32_t _i33;
            for (_i33 = 0; _i33 < _size29; ++_i33)
            {
              int32_t _key34;
              xfer += iprot->readI32(_key34);
              std::set<Edge> & _val35 = this->neighbors[_key34];
              {
                _val35.clear();
                uint32_t _size36;
                ::apache::thrift::protocol::TType _etype39;
                xfer += iprot->readSetBegin(_etype39, _size36);
                uint32_t _i40;
                for (_i40 = 0; _i40 < _size36; ++_i40)
                {
                  Edge _elem41;
                  xfer += _elem41.read(iprot);
                  _val35.insert(_elem41);
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
      case 3:
        if (ftype == ::apache::thrift::protocol::T_LIST) {
          {
            this->nodes.clear();
            uint32_t _size42;
            ::apache::thrift::protocol::TType _etype45;
            xfer += iprot->readListBegin(_etype45, _size42);
            this->nodes.resize(_size42);
            uint32_t _i46;
            for (_i46 = 0; _i46 < _size42; ++_i46)
            {
              xfer += this->nodes[_i46].read(iprot);
            }
            xfer += iprot->readListEnd();
          }
          this->__isset.nodes = true;
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
    std::map<int32_t, std::set<int32_t> > ::const_iterator _iter47;
    for (_iter47 = this->cluster.begin(); _iter47 != this->cluster.end(); ++_iter47)
    {
      xfer += oprot->writeI32(_iter47->first);
      {
        xfer += oprot->writeSetBegin(::apache::thrift::protocol::T_I32, static_cast<uint32_t>(_iter47->second.size()));
        std::set<int32_t> ::const_iterator _iter48;
        for (_iter48 = _iter47->second.begin(); _iter48 != _iter47->second.end(); ++_iter48)
        {
          xfer += oprot->writeI32((*_iter48));
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
    std::map<int32_t, std::set<Edge> > ::const_iterator _iter49;
    for (_iter49 = this->neighbors.begin(); _iter49 != this->neighbors.end(); ++_iter49)
    {
      xfer += oprot->writeI32(_iter49->first);
      {
        xfer += oprot->writeSetBegin(::apache::thrift::protocol::T_STRUCT, static_cast<uint32_t>(_iter49->second.size()));
        std::set<Edge> ::const_iterator _iter50;
        for (_iter50 = _iter49->second.begin(); _iter50 != _iter49->second.end(); ++_iter50)
        {
          xfer += (*_iter50).write(oprot);
        }
        xfer += oprot->writeSetEnd();
      }
    }
    xfer += oprot->writeMapEnd();
  }
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("nodes", ::apache::thrift::protocol::T_LIST, 3);
  {
    xfer += oprot->writeListBegin(::apache::thrift::protocol::T_STRUCT, static_cast<uint32_t>(this->nodes.size()));
    std::vector<Node> ::const_iterator _iter51;
    for (_iter51 = this->nodes.begin(); _iter51 != this->nodes.end(); ++_iter51)
    {
      xfer += (*_iter51).write(oprot);
    }
    xfer += oprot->writeListEnd();
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
  swap(a.nodes, b.nodes);
  swap(a.__isset, b.__isset);
}

Graph::Graph(const Graph& other52) {
  cluster = other52.cluster;
  neighbors = other52.neighbors;
  nodes = other52.nodes;
  __isset = other52.__isset;
}
Graph& Graph::operator=(const Graph& other53) {
  cluster = other53.cluster;
  neighbors = other53.neighbors;
  nodes = other53.nodes;
  __isset = other53.__isset;
  return *this;
}
std::ostream& operator<<(std::ostream& out, const Graph& obj) {
  using apache::thrift::to_string;
  out << "Graph(";
  out << "cluster=" << to_string(obj.cluster);
  out << ", " << "neighbors=" << to_string(obj.neighbors);
  out << ", " << "nodes=" << to_string(obj.nodes);
  out << ")";
  return out;
}

