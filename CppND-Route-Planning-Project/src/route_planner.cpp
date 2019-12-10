#include "route_planner.h"
#include <algorithm>

RoutePlanner::RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y): m_Model(model) {
  // Convert inputs to percentage:
  start_x *= 0.01;
  start_y *= 0.01;
  end_x *= 0.01;
  end_y *= 0.01;
  // TODO 2: Use the m_Model.FindClosestNode method to find the closest nodes to the starting and ending coordinates.
  // Store the nodes you find in the RoutePlanner's start_node and end_node attributes.

  // std::cout << "Route" << std::endl;
  // std::cout <<"end : " << this->end_node  <<" star " << typeid(this->start_node).name()  << std::endl;
  this->start_node = &model.FindClosestNode(start_y, start_y);
  
  this->end_node = &model.FindClosestNode(end_x, end_y);
  
}


// TODO 3: Implement the CalculateHValue method.
// Tips:
// - You can use the distance to the end_node for the h value.
// - Node objects have a distance method to determine the distance to another node.

float RoutePlanner::CalculateHValue(RouteModel::Node const *node) {
  return node->distance(*(this->end_node));
}


// TODO 4: Complete the AddNeighbors method to expand the current node by adding all unvisited neighbors to the open list.
// Tips:
// - Use the FindNeighbors() method of the current_node to populate current_node.neighbors vector with all the neighbors.
// - For each node in current_node.neighbors, set the parent, the h_value, the g_value. 
// - Use CalculateHValue below to implement the h-Value calculation.
// - For each node in current_node.neighbors, add the neighbor to open_list and set the node's visited attribute to true.

void RoutePlanner::AddNeighbors(RouteModel::Node *current_node) {
current_node->FindNeighbors();
current_node->h_value = this->CalculateHValue(current_node);
// std::cout << "size " << current_node->neighbors.size() << std::endl;
for (int i=0; i < current_node->neighbors.size(); i++) {
  current_node->neighbors[i]->parent = current_node;
  current_node->neighbors[i]->h_value = this->CalculateHValue(current_node->neighbors[i]);
  //float diff = fabs(current_node->neighbors[i]->h_value - current_node->h_value);
  current_node->neighbors[i]->g_value = current_node->g_value + current_node->neighbors[i]->distance(*(current_node));
  current_node->neighbors[i]->visited = true;
  current_node->neighbors[i]->f_value = current_node->neighbors[i]->h_value + current_node->neighbors[i]->g_value ;
  this->open_list.push_back(current_node->neighbors[i]);
  
  
  //current_node->neighbors[i]->g_value = current_node->g_value 
  
  //std::cout << "cuurent h " << current_node->h_value << std::endl;
  
  
  // std::cout << "neighbor h " << current_node->neighbors[i]->h_value << std::endl;
  //std::cout << "neighbor g " << current_node->neighbors[i]->g_value << std::endl;
  }
}


// TODO 5: Complete the NextNode method to sort the open list and return the next node.
// Tips:
// - Sort the open_list according to the sum of the h value and g value.
// - Create a pointer to the node in the list with the lowest sum.
// - Remove that node from the open_list.
// - Return the pointer.

RouteModel::Node *RoutePlanner::NextNode() {
  // std::cout << "size list " << this->open_list.size() << std::endl;
  std::sort(this->open_list.begin(), this->open_list.end(), [](auto && l, auto && r) { return l->f_value < r->f_value; });
  RouteModel::Node * returnNode = this->open_list.at(0);
  this->open_list.erase(this->open_list.begin());
  return returnNode;
}


// TODO 6: Complete the ConstructFinalPath method to return the final path found from your A* search.
// Tips:
// - This method should take the current (final) node as an argument and iteratively follow the 
//   chain  of parents of nodes until the starting node is found.
// - For each node in the chain, add the distance from the node to its parent to the distance variable.
// - The returned vector should be in the correct order: the start node should be the first element
//   of the vector, the end node should be the last element.

std::vector<RouteModel::Node> RoutePlanner::ConstructFinalPath(RouteModel::Node *current_node) {
    // Create path_found vector
    distance = 0.0f;
    std::vector<RouteModel::Node> path_found;
    // RouteModel::Node *parentNode = current_node->parent;

    std::cout << "start" << this->start_node->x << " : y " << this->start_node->y << std::endl;
    std::cout << "end" << current_node->x << " : y " << current_node->y << std::endl;
   
    while (true) {
    
      path_found.push_back(*current_node);
      distance += current_node->distance(*current_node->parent);
      std::cout << "distnace"<< distance << std::endl;
      std::cout << "h"<< current_node->h_value << std::endl;
      current_node = current_node->parent;
      if (current_node->parent == nullptr) break;
    }
      // Get next Node check if its finial node
      // add last node
   
    
  
    path_found.push_back(*current_node);
    // TODO: Implement your solution here.
    std::reverse(path_found.begin(), path_found.end());
    std::cout << "path size " << path_found.size() << std::endl;

    distance *= m_Model.MetricScale(); // Multiply the distance by the scale of the map to get meters.
    return path_found;

}


// TODO 7: Write the A* Search algorithm here.
// Tips:
// - Use the AddNeighbors method to add all of the neighbors of the current node to the open_list.
// - Use the NextNode() method to sort the open_list and return the next node.
// - When the search has reached the end_node, use the ConstructFinalPath method to return the final path that was found.
// - Store the final path in the m_Model.path attribute before the method exits. This path will then be displayed on the map tile.

void RoutePlanner::AStarSearch() {
  RouteModel::Node *current_node = start_node;
  std::cout << start_node->parent << std::endl;

  while (true) {
    this->AddNeighbors(current_node);
    current_node = this->NextNode();
    
    if (current_node == this->end_node) break;
  }
  std::cout << "found end" << std::endl;
  std::cout << start_node->parent << std::endl;
  this->start_node->parent = nullptr; 
  // this->CalculateHValue(this->start_node);  
  this->m_Model.path =  this->ConstructFinalPath(this->end_node);
  // TODO: Implement your solution here.

}
