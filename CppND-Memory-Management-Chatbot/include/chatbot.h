// Copyright 2020
// Udacity Project
// Author: Christian Leininger <info2016frei@gmail.com>

#ifndef CPPND_MEMORY_MANAGEMENT_CHATBOT_INCLUDE_CHATBOT_H_
#define CPPND_MEMORY_MANAGEMENT_CHATBOT_INCLUDE_CHATBOT_H_

#include <wx/bitmap.h>
#include <string>

class GraphNode;  // forward declaration
class ChatLogic;  // forward declaration

class ChatBot {
 private:
  // data handles (owned)
  wxBitmap *_image;  // avatar image

  // data handles (not owned)
  GraphNode *_currentNode;
  GraphNode *_rootNode;
  ChatLogic *_chatLogic;

  // proprietary functions
  int ComputeLevenshteinDistance(std::string s1, std::string s2);

 public:
  // constructors / destructors
  ChatBot();                                     // constructor WITHOUT memory allocation
  explicit ChatBot(std::string filename);                 // constructor WITH memory allocation
  ChatBot(const ChatBot &source);                // copy constructor
  ChatBot& operator=(const ChatBot &source);     // copy assigment operator
  ChatBot(ChatBot &&source);                     // move constructor
  ChatBot& operator=(ChatBot &&source);          // move assigment operator
  ~ChatBot();                       // destructur


  // getters / setters
  void SetCurrentNode(GraphNode *node);
  void SetRootNode(GraphNode *rootNode) { _rootNode = rootNode; }
  void SetChatLogicHandle(ChatLogic *chatLogic) { _chatLogic = chatLogic; }
  wxBitmap *GetImageHandle() { return _image; }

  // communication
  void ReceiveMessageFromUser(std::string message);
};

#endif  // CPPND_MEMORY_MANAGEMENT_CHATBOT_INCLUDE_CHATBOT_H_
