#include <iostream>
#include "BENEREMRE_BENER_EMRE_HW3_LINKEDLIST.H"

using namespace std;

linkedList::linkedList(){
	head = NULL;
}

void linkedList::addHouseNode(string hname) {

	houseNode *ptr = head;
	houseNode *temp = new houseNode(hname, NULL, NULL);
	
	if(head == NULL) // list is empty
		head = temp; 
	else {

		while(ptr->next != NULL) {
			ptr = ptr->next;
		}   ptr->next = temp;	
	}
}

int linkedList::addNeighborNode(string hname, string nname) {

	if(nnExists(hname,nname))
		return true;
	
	houseNode*ptr=head;
	
	while(ptr!=NULL)
	{
		if(ptr->houseName == hname)
		{
			neighborNode *ptr1 = ptr->neighborListHead;
			if(ptr1==NULL)
			{
				neighborNode *temp = new neighborNode(nname,NULL);
				ptr->neighborListHead=temp;

			}
			else
			{
				while(ptr1->next!=NULL)
					ptr1 =ptr1->next;
				
				neighborNode *temp = new neighborNode(nname,NULL);
			    ptr1->next= temp;
			}
		} ptr = ptr->next;
	}
}

void linkedList::printAll() {

	houseNode * ptr = head;
	
	while(ptr != NULL) {
		neighborNode *temp;
		temp = ptr->neighborListHead;
		cout << ptr->houseName << ": ";
		
		while(temp != NULL) {
			
			cout << temp->neighborName << ", ";
			temp = temp->next;
		}   cout << endl;
		    ptr = ptr->next;
	}
}

bool linkedList::hnExists(string hname) {

	houseNode* ptr= head;
	
	if(ptr == NULL)
		return false;
	while (ptr!=NULL)
	{
		if(ptr->houseName == hname)
			return true;
		ptr=ptr->next;
	}
	return false;
}

bool linkedList::nnExists(string hname, string nname) {

	houseNode* searchhouse = head;

	while(searchhouse!=NULL)
	{
		if(searchhouse->houseName==hname)
		{
			neighborNode * searchneighbors = searchhouse->neighborListHead;
			if(searchneighbors==NULL)
				return false;
			
			while(searchneighbors!=NULL)
			{
				if(searchneighbors->neighborName==nname)
					return true;
				searchneighbors=searchneighbors->next;
			}
		}
		searchhouse=searchhouse->next;
	}
		return false;	
}

void linkedList::deleteAll() {

	houseNode*ptr=head;
	while(head!=NULL)
	{
		ptr=head;
		head=head->next;
		delete ptr;
	}
}

void linkedList::conquerIt(string hname, string nname) {

	houseNode *ptr = head;

	while(ptr != NULL && ptr->houseName != nname)
		ptr = ptr->next;
	
	houseNode *temp = head;
	
	while(temp != NULL && temp->houseName != hname)
		temp = temp->next;
	
	neighborNode *pýtýr = ptr->neighborListHead;

	while(pýtýr != NULL) {

		if(( !nnExists(temp->houseName,pýtýr->neighborName) ) && ( temp->houseName!=pýtýr->neighborName ) && ( temp->houseName != pýtýr->neighborName) )
			addNeighborNode(temp->houseName,pýtýr->neighborName);
		
		pýtýr = pýtýr->next;
	}
}

void linkedList::deleteLoser(string hname) {

	//do nothing if list is empty
	if (head != NULL) {
		houseNode *ptr = head;
		//update head if the head contains the data requested for deletion
		if (head->houseName == hname) {
			head = head->next;
			delete ptr;
		}
		else {
			//search for the node with the correct data
			//ptr != NULL is necessary for the special case where the last element is deleted and ptr is updated
			//to NULL and the program crashes when ptr->next is executed in the while boolean expression.
			while (ptr != NULL && ptr->next != NULL) {
				if (ptr->next->houseName == hname) {
					houseNode * temp = ptr->next;
					ptr->next = ptr->next->next;
					delete temp;
				}
				ptr = ptr->next;
			}
		}
	}
}

void linkedList::neighborDeleter(string hname, string nname) {

	houseNode *ptr = head;

	while(ptr != NULL) {
		
		neighborNode *temp = ptr->neighborListHead;
		neighborNode *previous = NULL;
		while (temp != NULL)
		{

			if (temp!=NULL && (temp->neighborName == nname))
			{
				if (previous != NULL)
				{
					previous->next = temp->next;
					delete temp;
					temp = NULL;
				}
				else
				{
					ptr->neighborListHead = ptr->neighborListHead->next;
					delete temp;
					temp = NULL;
				}
				if (!nnExists(ptr->houseName,hname))
				{
					addNeighborNode(ptr->houseName,hname);
				}
			}
			if (temp != NULL)
			{
			previous = temp;
			temp = temp->next;
			}
		}


		ptr = ptr->next;
	}


}