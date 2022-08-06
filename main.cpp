#include "tree.hpp"

int main(){

	BST<int> t;
	/*
	t.add_vertex("A", 1);
	t.add_vertex("B", 3);
	t.add_vertex("C", 5);
	t.add_vertex("D", 10);
	t.add_vertex("G", 20);
	t.add_vertex("E", 15);
	t.add_vertex("H", 30);
	t.add_vertex("F", 17);
	*/
	t.add_vertex("v0", 21);
	t.add_vertex("v1", 28);
	t.add_vertex("v2", 11);
	t.add_vertex("v3", 12);
	t.add_vertex("v4", 27);
	t.add_vertex("v5", 20);
	t.add_vertex("v6", 16);
	//delete
	t.get_vertices();
	t.get_leaves();
	t.preorder_traversal();
	t.inorder_traversal();
	t.postorder_traversal();
	t.breadth_first_traversal();
	t.path("v3", "v4");
	t.path_with_largest_weight();
	t.height();
	//t.remove_vertex();
	//delete

	cout << boolalpha;
	cout << t.num_vertices() << endl;
	cout << t.num_edges() << endl;

	cout << t.sum_weight() << endl;
	
	for(auto x : t.path_with_largest_weight()){
		cout << x << " ";
	}
	cout << endl;
}
