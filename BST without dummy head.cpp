

#include<iostream>
#include<queue>


// ANALOGY FOR RECURSION:
// picuture a toy that you created with your own hands...you pull its string from the back...it goes ahead and moves...after it leaves your hand..you are not responsbile for it
// Just dont forget to set the limiting factor for it..otherwise it will keep on moving and never return

struct Node {
	int data;
	Node* right;
	Node* left;

	Node(int d) {
		this->data = d;
		this->left = NULL;
		this->right = NULL;

	}
};


class BST {


	public:

	Node* root;

		BST() {
			root = NULL;

		}


		Node* insertIntoBST(Node* root, int d) {
			//base case
			if (root == NULL) {
				root = new Node(d);
				return root;


			}

			if (d > root->data) {
				//insert in the right part
				root->right = insertIntoBST(root->right, d);

			}

			else {

				root->left = insertIntoBST(root->left, d);
			}

			return root;


			//The two returns tell that if there was no node after the root then we would simply attach it  and leave
			//the 2nd return is for us to join the node to its parent and maintain the tree-like structure
			//See through deception..dont worry...recursion has boggled many programmers greater than you

		}


		//The purpose of this function is to form an entire tree...just by using this one function
		void take_input(Node*& root) {
			int data;
			std::cout << "Enter the value that you want to add onto the tree " << std::endl;
			std::cin >> data;

			while (data != -1) {
				root = insertIntoBST(root, data);				//the root pointer is updated at every point
				std::cin >> data;

			}
		}



		//level order traversal

		void lvl_orderTrav(Node* root) {

			std::queue<Node*>q;
			q.push(root);
			q.push(NULL);


			while (!q.empty()) {
				Node* temp = q.front();
				q.pop();

				if (temp == NULL) {
					//the old lvl has been traversed
					std::cout << std::endl;

					if (!q.empty()) {
						//queue still has some child nodes
						q.push(NULL);							//this goes at the back of the queue

					}

				}

				else {
					std::cout << temp->data << " ";
					if (temp->left) {
						q.push(temp->left);

					}

					if (temp->right) {
						q.push(temp->right);
					}
				}
			}


			//explanation to this code:

			//ok so first of all i will give the root node in the queue and pass a NULL after it to symbolize the ending of the level
			//then i will make a while loop that will check until the queue is empty...
			//I will make two conditional statements..one to check if temp has a NULL or does it have a value
			//If NULL , it will mean that i have finished that level...so i will make a sub condition to check if the queue has ended..as there are more nodes
			//If there is a value...then i will print that value and then check if it has a left or right node..i will push them if they are there
			//Then comes the next iteration...this time there will be a left node and right node..so it will first print the left node
			//then in next interation comes the right node
			//after that it will encounter a NULL in the 4th iteration so it will again check if the queue is empty..if yes then the condition makes it exit the loop
			//If no then there will be a NULL added at the end again
			//this will continue till the queue isnt empty
			//We will get a shape on the console just like the actual tree

		}

		bool search_node(Node* root, int x) {

			//base class
			if (root == NULL) {
				return false;

			}

			if (root->data == x) {
				return true;

			}

			if (root->data > x) {
				//lets go to the left part
				return search_node(root->left, x);
			}

			if (root->data < x) {
				//lets go to the right part
				return search_node(root->right, x);

			}





		}


		//Minimum and Maximum value inside a tree

		//the left most value inside a tree is the smallest and the right most value in the tree is the greatest


		Node* Max_node(Node* root) {

			Node* temp = root;

			while (temp->right!= NULL) {
				temp = temp->right;

			}

			return temp;

		}
		

		Node* Min_node(Node* root) {
			Node* temp = root;

			while (temp->left != NULL) {
				temp = temp->left;
			}

			return temp;

		}


};

int main() {


	BST bst;

	int values[] = { 10,5,7,8,11,12 };

	for (int val : values) {
		bst.root = bst.insertIntoBST(bst.root, val);
	}

	//perform lvl order traversal
	std::cout << "The level order traversal is " << std::endl;
	bst.lvl_orderTrav(bst.root);

	//search for elements in the bst

	int search_val[] = { 7,10 };

	for (int x : search_val) {
		std::cout << "searching for " << x << ": " << (bst.search_node(bst.root, x) ? " Found " : "Not Found ") << std::endl;

	}

	return 0;

}