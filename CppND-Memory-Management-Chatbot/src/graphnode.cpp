// Copyright 2020
// Udacity Project
// Author: Christian Leininger <info2016frei@gmail.com>

#include <memory>
#include <utility>
#include <string>
#include "../include/graphedge.h"
#include "../include/graphnode.h"

// ________________________________________________________________________________________________
GraphNode::GraphNode(int id) {
  _id = id;
}

// ________________________________________________________________________________________________
GraphNode::~GraphNode() {
  //// STUDENT CODE
  ////

  // delete _chatBot;

  ////
  //// EOF STUDENT CODE
}

// ________________________________________________________________________________________________
void GraphNode::AddToken(std::string token) {
  _answers.push_back(token);
}

// ________________________________________________________________________________________________
void GraphNode::AddEdgeToParentNode(GraphEdge *edge) {
  _parentEdges.push_back(edge);
}

// ________________________________________________________________________________________________
void GraphNode::AddEdgeToChildNode(std::unique_ptr<GraphEdge> edge) {
  _childEdges.push_back(std::move(edge));
}

//// STUDENT CODE
////

// ________________________________________________________________________________________________
void GraphNode::MoveChatbotHere(ChatBot chatbot) {
  _chatBot = std::move(chatbot);
  _chatBot.SetCurrentNode(this);
}

// ________________________________________________________________________________________________
void GraphNode::MoveChatbotToNewNode(GraphNode *newNode) {
  newNode->MoveChatbotHere(std::move(_chatBot));
}
////
//// EOF STUDENT CODE

// ________________________________________________________________________________________________
GraphEdge *GraphNode::GetChildEdgeAtIndex(int index) {
  // the vector stores unique pointer
  return _childEdges[index].get();
}
