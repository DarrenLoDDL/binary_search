#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <limits>
#include <utility> 
#include <algorithm>
#include <string>
#include <cstdlib>
#include <cmath>
using namespace std;

template <typename T>
class Leaf {
    public:
        
        Leaf<T>* left;
        Leaf<T>* right;
        Leaf<T>* parent;
        T weight;
        string name;
};

template <typename T>
class BST {
    //data:
    vector<string> children;
    vector<pair<string, T>> wd_vertex_list;
    vector<string> vertex_list;
    vector<pair<string, string>> edge_list;
    int size;
    T weight_counter;
    Leaf<T>* root;
	public:
        /* define your data structure to represent a binary search tree (bst) */
        /* test1 */
		BST(); // the contructor function.
		~BST(); // the destructor function.
		size_t num_vertices(); // returns the total number of vertices in the bst.
		size_t num_edges(); // returns the total number of edges in the bst.
        T sum_weight(); // return the total weight of all the vertices in the bst.

        /* test2 */
        //Leaf<T>* add_vertex_recursive(Leaf<T>*, Leaf<T>*, const string&, const T&);
        void add_vertex(const string&, const T&); // adds a vertex, which has a weight, to the tree -- every vertex uses a string as its unique identifier.
        bool contains(const string&); // checks if a vertex is in the bst -- returns true if the bst contains the given vertex; otherwise, returns false.
        
        /* test3 */
        vector<string> get_vertices(); // returns a vector of all the vertices in the bst.
        vector<string> get_leaves(); // returns a vector of all the leaves in the bst.
        void go_to_leaves(vector<string> children, Leaf<T>* leaf);
        /* test4 */
        bool adjacent(const string&, const string&); // check if there is an edge between the two vertices in the bst -- returns true if the edge exists; otherwise, returns false.
		
        /* test5 */
        vector<pair<string,string>> get_edges(); // returns a vector of all the edges in the bst -- each edge is represented by a pair of vertices incident to the edge.
        
        /* test6 */
        vector<string> get_neighbours(const string&); // returns a vector of all the vertices, each of which is directly connected with the given vertex via an edge.
        size_t degree(const string&); // returns the degree of a vertex.

        /* test7 */
		vector<string> preorder_traversal(); // returns a vector of all the vertices in the visiting order of a preorder traversal over the bst.
		vector<string> preorder_recursive(Leaf<T>* child, vector<string> visits);
       
        /* test8 */
        vector<string> inorder_traversal(); // returns a vector of all the vertices in the visiting order of an inorder traversal over the bst.
        vector<string> inorder_recursive(Leaf<T>* child, vector<string> visits);
        /* test9 */
        vector<string> postorder_traversal(); // returns a vector of all the vertices in the visiting order of a postorder traversal over the bst.
        vector<string> postorder_recursive(Leaf<T>* child, vector<string> visits);
        /* test10 */
        vector<string> breadth_first_traversal(); // returns a vector of all the vertices in the visiting order of a breadth first traversal over the bst.
		vector<string> generic_remove(const string& u, vector<string> list);
        bool generic_contains(const string& u, vector<string> list);

        /* test11 */
        vector<string> path(const string&, const string&); // returns a vector of all the vertices in the path from the first vertex to the second vertex.
        vector<string> path_to_root(const string& u, vector<string> path);
        string get_parent(const string& u);  //     A path should include the source and destination vertices at the begining and the end, respectively.
        
        /* test12 */
        vector<string> path_with_largest_weight(); // returns a path that has the largest weight in the bst.
        T get_node_weight(const string& u);                               //    The weight of a path is the sum of the weights of all the vertices (including the source and destination vertices) in the path.

        /* test13 */
        size_t height(); // returns the height of bst. Height of a tree is the number of edges that form the longest path from root to any leaf.

        /* test14 */
        void remove_vertex(const string&); // delete the given vertex from bst -- note that, all incident edges of the vertex should be deleted as well.
};

/* test1 */
template <typename T>
BST<T>::BST() {
    this -> size = 0; 
    this -> root = NULL;
    this -> weight_counter = 0;
}
 
template <typename T>
BST<T>::~BST() {}


template <typename T>
size_t BST<T>::num_vertices() {
    return vertex_list.size();
}

template <typename T>
size_t BST<T>::num_edges() {
   return edge_list.size();;
}

template <typename T>
T BST<T>::sum_weight() {
    return weight_counter;
}

/* test2 */
template <typename T>
void BST<T>::add_vertex(const string& u, const T& w) {
    if(!this -> root){
        Leaf<T>* new_leaf = new Leaf<T>();
        new_leaf -> left = nullptr;
        new_leaf -> right = nullptr; //give new_leaf all its attributes
        new_leaf -> parent = nullptr;
        new_leaf -> name = u;
        new_leaf -> weight = w;
        pair<string,T> node;
        node.first = new_leaf -> name;
        node.second = new_leaf -> weight;
        wd_vertex_list.push_back(node);
        this -> root = new_leaf; //create the root
        vertex_list.push_back(u); //add to vertex list
        this -> weight_counter += w; //add weight
    }
    else if(this -> root){
        //create new leaf:
        Leaf<T>* new_leaf = new Leaf<T>;
        new_leaf -> left = nullptr;
        new_leaf -> right = nullptr;
        new_leaf -> parent = nullptr;
        new_leaf -> name = u;
        new_leaf -> weight = w;
        //this list is for test 12
        pair<string,T> node;
        node.first = new_leaf -> name;
        node.second = new_leaf -> weight;
        wd_vertex_list.push_back(node);
        //create pointer, it points to root initially:
        Leaf<T>* next = this -> root;
        //create parent pointer, points to the prev value of next
        Leaf<T>* prev = nullptr;
        //look for approprioate spot to insert
        bool left_child = false;
        bool right_child = false;//lets us know which pointer to add to
        while(next){
            if(w < next -> weight){
                prev = next;
                next = next -> left;
                if(!next){
                    left_child = true;
                    }
            }
            else if(w >= next -> weight){
                prev = next;
                next = next -> right;
                if(!next){
                    right_child = true;
                    }
        }
        }
    //now we do insertion and update stats of the tree: we're still in scope of if
    if(left_child == true){
        prev -> left = new_leaf;
        new_leaf -> parent = prev;
    }

    if(right_child == true){
        prev -> right = new_leaf;
        new_leaf -> parent = prev;
    }
    vertex_list.push_back(u); //add to vertex list
    pair<string,string> edge;
    edge.first = prev -> name;//get parent name
    edge.second = new_leaf -> name; //to be added name
    
    //checking

    /*cout<<prev -> name;
    cout<< next -> name + ", ";*/
    
    //
    edge_list.push_back(edge); //add edge
    weight_counter += w; //add weight

}
} 

/*template <typename T>
void BST<T>::add_vertex(const string& u, const T& w) {
    //if tree is empty do this. executed just once (probably)
    if(!root){
        Leaf<T>* new_leaf = new Leaf<T>(u, w);
        this -> root = new_leaf; //create the rot
        root -> rel_height = 0; //establish a height to compare
        vertex_list.push_back(u); //add to vertex list
        weight_counter += w; //add weight
    }
    
    if(w < root -> weight){
        root -> left = add_vertex_recursive(root, root->left, u, w); //Left
    }
    else{
        root -> right = add_vertex_recursive(root, root->right, u, w); //Right
    }
}*/


/*
template <typename T>
Leaf<T>* BST<T>::add_vertex_recursive(Leaf<T>* leaf_parent, Leaf<T>* leaf_ptr, const string& u, const T& w){
    //if pointer points at nothing, create node
    if(!leaf_ptr){
        Leaf<T>* new_leaf = new Leaf<T>(u, w);
        new_leaf -> parent = leaf_parent;
        //cout << "HERE" << endl;
        cout<< new_leaf -> parent << endl;
        vertex_list.push_back(u); //add to vertex list
        pair<string,string> edge;
        edge.first = leaf_parent -> name;//get parent name
        edge.second = u; //to be added name
        edge_list.push_back(edge); //add edge
        weight_counter += w; //add weight

        new_leaf -> rel_height = leaf_parent -> rel_height + 1;
        if (new_leaf -> rel_height > total_height){
            total_height = new_leaf -> rel_height; //update height if rel height > total height
        }
        return new_leaf;
    }
    else if(w >= root -> weight){
        cout << leaf_ptr->name << endl;
        return leaf_ptr -> right = add_vertex_recursive(leaf_ptr, leaf_ptr->right, u, w); //Right 
    }
    
    else{
        cout << leaf_ptr->name << endl;
        return leaf_ptr -> left = add_vertex_recursive(leaf_ptr, leaf_ptr->left, u, w); //Left
    }
}
*/

template <typename T>
bool BST<T>::contains(const string& u) {
    for(int i = 0; i < vertex_list.size(); i++){
        if(vertex_list[i] == u){
            return true;
        }
    }
    return false;
}
/* test3 */

template <typename T>
vector<string> BST<T>::get_vertices() {
    return vertex_list;
}

template <typename T>
vector<string> BST<T>::get_leaves() {
    //the way that the edges are added are in a way that parents are index 0 and children are index 1, ALWAYS
    vector<string> temp_vertex_list = vertex_list;
    vector<string> first_edge; 
    for(int i = 0; i < edge_list.size(); ++i){//make list of vertices in first index of edge list
        first_edge.push_back(get<0>(edge_list[i]));
    }
    for(int i = 0; i < temp_vertex_list.size(); i++){ //for each temp vert, compare with each first edge, if mathcing delete
        for(int j = 0 ; j < first_edge.size(); j++){
            if(temp_vertex_list[i] == first_edge[j]){
                temp_vertex_list.erase(temp_vertex_list.begin() + i);
            --i;
            }
        }
    }
    return temp_vertex_list;
}


/* test4 */

template <typename T>
bool BST<T>::adjacent(const string& u, const string& v) {
    for(int i = 0; i < edge_list.size(); i++){
        if(get<0>(edge_list[i]) == u && get<1>(edge_list[i]) == v){ //check if either nodes are in any entry parent or child
               return true;
           }
        if(get<0>(edge_list[i]) == v && get<1>(edge_list[i]) == u){
            return true;
        }
    }
    return false;
}

/* test5 */

template <typename T>
vector<pair<string,string>> BST<T>::get_edges() {
    return edge_list;
}

/* test6 */

template <typename T>
vector<string> BST<T>::get_neighbours(const string& u) {
    vector<string> neighbours;
    for(int i = 0; i < edge_list.size(); i++){
        if(get<0>(edge_list[i]) == u){
            neighbours.push_back(get<1>(edge_list[i])); //get children of u
        }
        if(get<1>(edge_list[i]) == u){
            neighbours.push_back(get<0>(edge_list[i])); //get parent of u
        }
    }
    return neighbours;
}

template <typename T>
size_t BST<T>::degree(const string& u) {
    return get_neighbours(u).size();
}

/* test7 */

template <typename T>
vector<string> BST<T>::preorder_traversal() {
    //return vector<string>();
    vector<string> visits; 
    visits.push_back(root -> name); //push root name
    visits = preorder_recursive(root -> left, visits); //traverse left
    visits = preorder_recursive(root -> right, visits); //traverse right
    return visits;
}

template <typename T>
vector<string> BST<T>::preorder_recursive(Leaf<T>* child, vector<string> visits){
    if(child == NULL){
        return visits;
    }
    else{
        visits.push_back(child -> name);
        visits = preorder_recursive(child -> left, visits);
        visits = preorder_recursive(child -> right, visits);
        return visits;
    }
}
/* test8 */

template <typename T>
vector<string> BST<T>::inorder_traversal() {
    //return vector<string>();
    vector<string> visits;
    visits = inorder_recursive(root->left, visits); //traverse left subtree
    visits.push_back(root -> name); //push name of root
    visits = inorder_recursive(root->right, visits);    //traverse right subtree
    return visits;
   // for(int i =0; i<visited.size();i++){
  //      cout<<visited[i];
   // }
   // cout<<endl;
    
}

template <typename T>
vector<string> BST<T>::inorder_recursive(Leaf<T>* child, vector<string> visits) {
    if(child == NULL){
        return visits;
    }
    else{
        visits = inorder_recursive(child -> left, visits); //traverse left subtree
        visits.push_back(child -> name);      //add parent to list
        visits = inorder_recursive(child->right, visits); //traverse right subtree
        return visits;
    }
    
}


/* test9 */

template <typename T>
vector<string> BST<T>::postorder_traversal() {
    vector<string> visits;
    visits = postorder_recursive(root->left, visits); //traverse left subtree
    visits = postorder_recursive(root->right, visits); //traverse right subtree
    visits.push_back(root -> name); //finally, add root
    //
    //for(int i =0; i<visited.size();i++){
      //  cout<<visited[i];
 //  }
   // cout<<endl;
    //
    return visits;
}

template <typename T>
vector<string> BST<T>::postorder_recursive(Leaf<T>* child, vector<string> visits){
     if(child == NULL){
        return visits;
    }
    else{
        visits = postorder_recursive(child -> left, visits);
        visits = postorder_recursive(child -> right, visits);
        visits.push_back(child -> name);
        return visits;
    }
}

/* test10 */

template <typename T>
vector<string> BST<T>::breadth_first_traversal() {
    vector<string> visits; //all nodes visited
    vector<string> unmarked = vertex_list; //nodes not yet visited
    queue<Leaf<T>*> q; //queue of pointers
    q.push(root); //start at root
    Leaf<T>* top = new Leaf<T>();
    while(!q.empty()){
        top = q.front();//update top value, does work after first run
        if(generic_contains(top -> name, unmarked)){
            visits.push_back(top -> name); //if node is in unmrked, add it to visits
            q.pop();
            unmarked = generic_remove(top -> name, unmarked);//remove it from unmarked
            if(top -> left){
                q.push(top -> left);//if the left and right exist, add them
            }
            if(top -> right){
                q.push(top -> right);
            }
        }
        else{
             q.pop();
         }   
    }
    return visits;
}

template <typename T>
vector<string> BST<T>::generic_remove(const string& u, vector<string> list) {
    vector<string> new_list = list;
    for(int i = 0; i < new_list.size(); i++){
        if(new_list[i] == u){
            new_list.erase(new_list.begin() + i);
        }
    }
    return new_list;
}

template <typename T>
bool BST<T>::generic_contains(const string& u, vector<string> list) {
    vector<string> new_list = list;
    for(int i = 0; i < new_list.size(); i++){
        if(new_list[i] == u){
            return true;
        }
    }
    return false;
}

/* test11 */ 

template <typename T>
vector<string> BST<T>::path(const string& u, const string& v){
    vector<string> temp = vector<string>();
    vector<string> u_path = path_to_root(u, temp);//get path u

    vector<string> temp2 = vector<string>();
    vector<string> v_path = path_to_root(v, temp2); //get path v

    bool intersection = false;

    for(int i = 0; i < u_path.size(); i++){
        for(int j = 0; j < v_path.size(); j++){
        if(u_path[i] == v_path[j]){
            if(intersection == false){
                v_path.erase(v_path.begin() + j); //we dont delete the first intersection, as it is part of the path
                intersection = true;
                --j;
            }
            else if(intersection == true){
            v_path.erase(v_path.begin() + j);//one we find intersection, every other common node is removed
            u_path.erase(u_path.begin() + i);
            --i;
            --j;
            }
        } 
    }
    }
    
    //for(int i = 0; i < u_path.size() ; i++){cout<<u_path[i];}
    //cout<<endl;
      //for(int i = 0; i < v_path.size() ; i++){cout<<v_path[i];}
   // cout<<endl;

    for(int i = v_path.size() - 1 ; i >= 0; i--){
        u_path.push_back(v_path[i]);
    }

    //for(int i = 0; i < u_path.size() ; i++){cout<<u_path[i];}
   // cout<<endl;

    return u_path;
}

template<typename T>
vector<string> BST<T>::path_to_root(const string& u, vector<string> path){
    string current = u;
    if(current != this -> root -> name){
    for(int i = 0; i < edge_list.size(); i++){
        if(get<1>(edge_list[i]) == u){
            path.push_back(u);//push child
            return path_to_root(get<0>(edge_list[i]), path);//parent of child is treated as new child, recurse
        }
    }
    }
    else{
        path.push_back(root -> name);//root name isnt added after exiting if, add it here
        return path;
    }
    return path;
}



/* test12 */

template <typename T>
vector<string> BST<T>::path_with_largest_weight(){
    vector<vector<string>> all_paths;
    int path_weight = 0;
    for(int i = 0; i < vertex_list.size() ; i++){//make list of all paths
        for(int j = 0; j < vertex_list.size(); j++){
            vector<string> potential = path(vertex_list[i], vertex_list[j]);
            all_paths.push_back(potential);
        }
    }
    vector<string> heaviest = vector<string>();
    int heaviest_weight = 0; //things we need to use and reuse
    int potential_weight = 0;

    for(int i = 0; i < all_paths.size(); i++){
        vector<string> this_path = all_paths[i];
        for(int j = 0; j < this_path.size() ; j++){
            potential_weight += get_node_weight(this_path[j]);//find the total weight of a path
        }
        if(potential_weight >= heaviest_weight){ //check if bigger
            heaviest_weight = potential_weight;
            heaviest = this_path; // update the heaviest and weight total, then reset
            potential_weight = 0;
        }
        else{
            potential_weight = 0; //reset it anyway for repeated use

        }
    }
    return heaviest;
}

template <typename T>
T BST<T>::get_node_weight(const string& u){
    for(int i = 0 ; i < wd_vertex_list.size(); i++){
        if(get<0>(wd_vertex_list[i]) == u){
            return get<1>(wd_vertex_list[i]);  
        }
    }
    return 0;
    
}

/* test13 */

template <typename T>
size_t BST<T>::height() {
    vector<vector<string>> all_paths;
    vector<string> leaves = get_leaves();
    //get the path from the root to all children/leaves
    for(int i = 0; i < leaves.size(); i++){
        all_paths.push_back(path_to_root(leaves[i], vector<string>()));
    }
    //compare the length of all paths
    size_t longest_path = 0;
    for(int i = 0; i < all_paths.size() ; i++){
        if(all_paths[i].size() >= longest_path){
            longest_path = all_paths[i].size();
        }  
    }
    return longest_path - 1;//we are not including the root
}

/* test14 */

template <typename T>
void BST<T>::remove_vertex(const string& u) {
    
}
