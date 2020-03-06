// Copyright 2020
// Udacity Project
// Author: Christian Leininger <info2016frei@gmail.com>


#include <string>
#include "../include/graphnode.h"
#include "../include/graphedge.h"

// ________________________________________________________________________________________________
GraphEdge::GraphEdge(int id) {
  _id = id;
}

// ________________________________________________________________________________________________
void GraphEdge::SetChildNode(GraphNode *childNode) {
  _childNode = childNode;
}

// ________________________________________________________________________________________________
void GraphEdge::SetParentNode(GraphNode *parentNode) {
  _parentNode = parentNode;
}

// ________________________________________________________________________________________________
void GraphEdge::AddToken(std::string token) {
    _keywords.push_back(token);
}
