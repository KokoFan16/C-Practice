#include <iostream>
#include <vector>
#include <numeric>
#include <random>
#include <time.h>

using namespace std;

/*The structure of node in skiplist, 
includes key, pointer and constructor.
The pointers is a vector, and the length
of this vector is level. 
Level means the layer of each node.
*/
struct SkipNode
{
	int key;
	vector<SkipNode*> next;

	SkipNode(int x, int level);
};

/*Constructor of SkipNode.
Initialize the pointer of SKipnode to null */
SkipNode::SkipNode(int x, int level): key(x)
{
	for (size_t i = 0; i < level; i++)
	{
		next.push_back(nullptr);
	}
}

/*class skipList, which includes variables
and several functions.
*/
class SkipList
{
public:
	//constructor
	SkipList();

	//destructor
	~SkipList();

	//The entry point of each level
	SkipNode* head;

	// const variables
	const int minInt = numeric_limits<int>::min();
	const int maxInt = numeric_limits<int>::max();

	/*log(n)/log(2)
	In this demo, n = 100
	log(100)/log(2) = 6.64*/
	const int maxLevel = 6;

	/*This function used to obtain the random 
	level of each node*/
	int randomLevel();

	/*These three functions are basic operations
	of Skiplist.*/
	SkipNode* insert(int x);
	SkipNode* find(int x);
	SkipNode* deleteNode(int x);

	/*This function is used to pretty print the 
	SkipList*/
	void printNode();

private:
	
	/*The tail of each level*/
	SkipNode* tail;
	
	/*This function is used to find the current max
	level of SkipList or SkipNode*/
	int nodeLevel(vector<SkipNode*> p);

};

/*Initialize SkipList*/
SkipList::SkipList()
{
	/*head and tail are initialized to smallest 
	possible key and largest possible key respectively*/
	head = new SkipNode(minInt, maxLevel);
	tail = new SkipNode(maxInt, maxLevel);

	/*connect all the levels pointers of header to tail*/
	for (size_t i = 0; i < maxLevel; i++)
	{
		head->next[i] = tail;
	}
}

SkipList::~SkipList()
{
	delete head;
	delete tail;
}

/*Using time as the seed to obtain the 
random vaule of (0,1). level++ until the
value of u(0,1) is 0 or exceed the maxLevel.*/
int SkipList::randomLevel()
{
	int random_level = 1; 
	int seed = time(NULL);
	static default_random_engine e(seed);
	static uniform_int_distribution<int> u(0, 1);
	
	while (u(e) && random_level < maxLevel)
	{
		random_level++;
	}
	
	return random_level;
}

/*
	This fucntion returns the number of non-null 
	pointers corresponding to the level of the 
	current node.
	If list empty returns 1.
*/
int SkipList::nodeLevel(vector<SkipNode*> next)
{
	int node_level = 0;

	if (next[0]->key == maxInt)
	{
		return node_level;
	}

	for (size_t i = 0; i < next.size(); i++)
	{
		if (next[i] != nullptr && next[i]->key != maxInt)
		{
			node_level++;
		}
		else
		{
			break;
		}
	}

	return node_level; 
}

/*
Insert a new node:
1) Using find(x) function to check whether 
this node has already existed in this SKipList. 
If yes, just return the current list.
2) Obtain the random level of this new node.
3) Find the suitable place for this node per level.
4) Insert this node, and modify the pointer per level.
*/
SkipNode* SkipList::insert(int x)
{
	int x_level = randomLevel();
	SkipNode* new_node = nullptr;
	SkipNode* tmp = head;

	new_node = find(x);

	if (new_node) {
		cout << "\nThis node " << x << " has already existed." << endl;
		return head;
	}

	cout << "key: " << x << ", randomLevel: " << x_level << endl;

	new_node = new SkipNode(x, x_level);

	for (int i = (x_level - 1); i > -1; i--)
	{
		while (tmp->next[i] != nullptr && tmp->next[i]->key < x)
		{
			tmp = tmp->next[i];
		}

		new_node->next[i] = tmp->next[i];
		tmp->next[i] = new_node;
	}

	return head;
}


/*Find whether the node exists:
Since SKipList is sorted, so the nearest and smaller node 
is found firstly. If the later one is equal to the new one,
return this node, else return null.*/
SkipNode* SkipList::find(int x)
{
	SkipNode* tmp = head;
	int current_level = nodeLevel(tmp->next);

	for (int i = (current_level-1); i > -1; i--)
	{
		while (tmp->next[i] != nullptr && tmp->next[i]->key < x)
		{
			tmp = tmp->next[i];
		}
	}
	tmp = tmp->next[0];
	
	if (tmp->key == x)
	{
		cout << "\nThis key " << x << " has been found\n";
		return tmp;
	}
	else
	{
		//cout << " \nThis key " << x << " doesn't exit\n";
		return nullptr;
	}
}

/*Delete a node in SkipList:
1) Using find(x) function to check if this node exists.
if doesn't, return current list.
2) Search the nearest and smaller one of this node per level.
3) Modify the poiner per level to delete this node.
*/
SkipNode* SkipList::deleteNode(int x)
{
	SkipNode* node = find(x);
	if (!node)
	{
		cout << "\n This deleting node" << x << "doesn't exist" << endl;
		return head;
	}
	else
	{
		SkipNode* tmp = head;
		int x_level = node->next.size();

		cout << "\nThe deleting node " << x <<  "'s level is " << x_level << endl;

		for (int i = (x_level-1); i > -1; i--)
		{
			while (tmp->next[i] != nullptr && tmp->next[i]->key < x)
			{
				tmp = tmp->next[i];
			}
			tmp->next[i] = tmp->next[i]->next[i];

			cout << "This node " << x << " has been deleted from level " << i << endl;
		}

		return head;
	}
}

/*Print nodes in SkipList:
Print all the nodes per level, and each level is split with '{}'.
Print 10 nodes each line of screen, and each nodes is split with ','*/
void SkipList::printNode()
{

	for (size_t i = 0; i < maxLevel; i++)
	{
		SkipNode* tmp = head;
		int lineLen = 1;
		
		if (tmp->next[i]->key != maxInt)
		{
			cout << "\n";
			cout << "This is level " << i << ":" << endl;
			cout << "{";

			while (tmp->next[i] != nullptr && tmp->next[i]->key != maxInt)
			{
				cout << "Key: " << tmp->next[i]->key;

				tmp = tmp->next[i];

				if (tmp->next[i] != nullptr && tmp->next[i]->key != maxInt)
				{
					cout << ", ";
				}

				if (lineLen++ % 10 == 0) cout << "\n";
			}
			cout << "}" << "\n";
		}
	}
}

//main function
int main()
{
	SkipList l;
	for (size_t i = 0; i < 50; i++)
	{
		l.insert(i);
	}

	l.printNode();

	l.insert(20);
	l.printNode();

	l.find(3);

	l.deleteNode(4);

	l.printNode();

}
