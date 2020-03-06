// Copyright 2020
// Udacity Project
// Author: Christian Leininger <info2016frei@gmail.com>


#ifndef CPPND_MEMORY_MANAGEMENT_CHATBOT_INCLUDE_CHATLOGIC_H_
#define CPPND_MEMORY_MANAGEMENT_CHATBOT_INCLUDE_CHATLOGIC_H_

#include <vector>
#include <string>
#include <memory>
#include <utility>
#include "../include/chatgui.h"

// forward declarations
class ChatBot;
class GraphEdge;
class GraphNode;

class ChatLogic {
 private:
  //// STUDENT CODE
  ////

  // data handles (owned)
  std::vector<std::unique_ptr<GraphNode>> _nodes;

  ////
  //// EOF STUDENT CODE

  // data handles (not owned)
  GraphNode *_currentNode;
  ChatBot *_chatBot;
  ChatBotPanelDialog *_panelDialog;

  // proprietary type definitions
  typedef std::vector<std::pair<std::string, std::string>> tokenlist;

  // proprietary functions
  template <typename T>
  void AddAllTokensToElement(std::string tokenID, tokenlist &tokens, T &element);

 public:
  // constructor / destructor
  ChatLogic();
  ~ChatLogic();

  // getter / setter
  void SetPanelDialogHandle(ChatBotPanelDialog *panelDialog);
  void SetChatbotHandle(ChatBot *chatbot);

  // proprietary functions
  void LoadAnswerGraphFromFile(std::string filename);
  void SendMessageToChatbot(std::string message);
  void SendMessageToUser(std::string message);
  wxBitmap *GetImageFromChatbot();
};

#endif  // CPPND_MEMORY_MANAGEMENT_CHATBOT_INCLUDE_CHATLOGIC_H_
