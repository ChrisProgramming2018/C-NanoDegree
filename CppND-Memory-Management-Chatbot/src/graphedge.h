// Copyright 2020
// Udacity Project
// Author: Christian Leininger <info2016frei@gmail.com>

#ifndef CPPND_MEMORY_MANAGEMENT_CHATBOT_INCLUDE_GRAPHEDGE_H_
#define CPPND_MEMORY_MANAGEMENT_CHATBOT_INCLUDE_GRAPHEDGE_H_

#include <vector>
#include <string>

class GraphNode;   // forward declaration

class GraphEdge {
 private:
  // data handles (not owned)
  GraphNode *_childNode;
  GraphNode *_parentNode;

  // proprietary members
  int _id;
  std::vector<std::string> _keywords;  // list of topics associated with this edge
 public:
  // constructor / desctructor
  explicit GraphEdge(int id);

  // getter / setter
  int GetID() { return _id; }
  void SetChildNode(GraphNode *childNode);
  void SetParentNode(GraphNode *parentNode);
  GraphNode *GetChildNode() { return _childNode; }
  std::vector<std::string> GetKeywords() { return _keywords; }

  // proprietary functions
  void AddToken(std::string token);
};

#endif  // CPPND_MEMORY_MANAGEMENT_CHATBOT_INCLUDE_GRAPHEDGE_H_
