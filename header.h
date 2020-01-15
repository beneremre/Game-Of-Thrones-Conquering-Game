#ifndef _BENEREMRE_BENER_EMRE_HW3_LINKEDLIST_H
#define _BENEREMRE_BENER_EMRE_HW3_LINKEDLIST_H

#include <string>

using namespace std;

struct neighborNode {  

	string neighborName;
	neighborNode * next; 
 
	//constructer
	neighborNode::neighborNode()
		:neighborName(""), next(NULL)
	{}
	
	neighborNode::neighborNode(string n, neighborNode* x)
		:neighborName(n), next(x)
	{}
};

struct houseNode {  

	string houseName;
	neighborNode * neighborListHead;  
	houseNode * next;
	
	//constructer 
	houseNode:: houseNode()
		:houseName(""),neighborListHead(NULL),next(NULL)
	{}
	
	houseNode:: houseNode(string n, neighborNode* p, houseNode * (h))
		:houseName(n),neighborListHead(p),next(h)
	{}
};


class linkedList { 

public:  

	linkedList();
	void addHouseNode(string hname); 
	int addNeighborNode(string hname, string nname);
	void printAll();
	bool hnExists(string hname); 
	bool nnExists(string hname, string nname);
	void deleteAll();  
	void conquerIt(string hname, string nname);
	void deleteLoser(string hname);
	void neighborDeleter(string hname, string nname);
	//other member functions…

private:
	
	houseNode * head;  

}; 

#endif //_BENEREMRE_BENER_EMRE_HW3_LINKEDLIST_H

