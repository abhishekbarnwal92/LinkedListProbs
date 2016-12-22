#include <iostream>
#include <stdlib.h>

using namespace std;

struct node
{
    int data;
    struct node * next;
};

struct node * newnode(int data)
{
    struct node * temp = (struct node *)malloc(sizeof(struct node));
    temp->data = data;
    temp->next = NULL;
    return temp;
}

void insertlast(struct node ** head, int data)
{
    if (*head == NULL)
    {
	*head = newnode(data);
	return;
    }
    struct node * temp = *head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    struct node * newtemp = newnode(data);
    temp->next = newtemp;
}

void inserthead(struct node ** head, int data)
{
    if (*head == NULL)
    {
	*head = newnode(data);
	return;
    }
    struct node * temp = newnode(data);
    temp->next = *head;
    *head = temp;
}

void print(struct node * head)
{
    if (head == NULL)
    {
      	cout << "empty" << endl;
    }
    else
    {
        struct node * temp = head;
        while(temp != NULL)
        {
            cout << temp->data << "\t";
            temp = temp->next;
        }
        cout << endl;
    }
}

int length(struct node * head)
{
    if (head == NULL)
    {
      	return 0;
    }
    int count = 0;
    struct node * temp = head;
    while (temp != NULL)
    {
        count ++;
        temp = temp->next;
    }
    return count;
}

int count(struct node * head, int n)
{
    if (head == NULL)
    {
      	return -1;
    }
    int count = 0;
    struct node * temp = head;
    while (temp != NULL)
    {
	if (temp->data == n)
	{
	    count ++;
	}
	temp = temp->next;
    }
    return count;
}

void deletelist(struct node ** head)
{
    while (*head != NULL)
    {
	struct node * temp = *head;
	*head = (*head)->next;
	temp->next = NULL;
	free(temp);
    }
}

void insertnth(struct node ** head, int index, int data)
{
    if (index < 0 || index > length(*head))
    {
	cout << "index out of range\n";
	return;
    }
    if (index == 0)
    {
      	inserthead(head, data);
    }
    else
    {
	struct node * temp = newnode(data);
	struct node * curr = *head;
	int count = 1;
        while (count != index)
        {
            curr = curr->next;
            count = count+1;
        }
        temp->next = curr->next;
        curr->next = temp;
    }
}

void sortedinsert(struct node ** head, int data)
{
    if (*head == NULL || (*head)->data > data)
    {
	inserthead(head, data);
	return;
    }
    struct node * temp = *head;
    while (temp->next != NULL && temp->next->data < data)
    {
      	temp = temp->next;
    }
    struct node * newn = newnode(data);
    newn->next = temp->next;
    temp->next = newn;
}

void sortedinsertnode(struct node ** head, struct node * data)
{
    if (*head == NULL || (*head)->data > data->data)
    {
        data->next = *head;
        *head = data;
        return;
    }
    struct node * temp = *head;
    while (temp->next != NULL && temp->next->data < data->data)
    {
	temp = temp->next;
    }
    data->next = temp->next;
    temp->next = data;
}

void sort(struct node ** head)
{
    struct node * result = NULL;
    struct node * temp = *head;
    struct node * curr = NULL;
    while (temp != NULL)
    {
        curr = temp->next;
        sortedinsertnode(&result, temp);
	      temp = curr;
    }
    *head = result;
}

void split(struct node * head, struct node ** first, struct node ** sec)
{
    if (head == NULL)
    {
	      return;
    }
    struct node * tr1 = head;
    struct node * tr2 = head;
    struct node * temp = NULL;
    *first = head;
    while (tr2 != NULL && tr2->next != NULL)
    {
        temp = tr1;
        tr1 = tr1->next;
        tr2 = tr2->next->next;
    }
    if (tr2 == NULL)
    {
        temp->next = NULL;
        *sec = tr1;
    }
    else if (tr2->next == NULL)
    {
        *sec = tr1->next;
        tr1->next = NULL;
    }
}

void removedup(struct node ** head)
{
    if (*head == NULL || (*head)->next == NULL)
    {
	return;
    }
    struct node * temp = *head;
    while (temp != NULL && temp->next != NULL)
    {
	struct node * next = temp->next;
	while (next != NULL && next->data == temp->data)
	{
	    struct node * del = next->next;
	    temp->next = next->next;
	    next->next = NULL;
	    free(next);
	    next = del;
	}
	if (temp != NULL)
	{
	    temp = temp->next;
	}
    }
}

void altsplit(struct node * head, struct node ** first, struct node ** sec)
{
    if (head == NULL)
    {
	return;
    }
    struct node * tr1 = head;
    *first = tr1;
    struct node * tr2 = head->next;
    *sec = tr2;
    while (tr1->next != NULL && tr2->next != NULL)
    {
	tr1->next = tr1->next->next;
	tr2->next = tr2->next->next;
	tr1 = tr1->next;
	tr2 = tr2->next;
    }
    tr1->next = NULL;
}

void shufflemerge(struct node ** head, struct node ** first, struct node ** sec){
    if (*first != NULL)
    {
	*head = *first;
	*first = (*first)->next;
    }
    else if (*sec != NULL)
    {
	*head = *sec;
	return;
    }
    else
    {
	*head = NULL;
	return;
    }
    struct node * temp = NULL;
    struct node * curr = *head;
    while (*first != NULL && *sec != NULL)
    {
	temp = *sec;
	*sec = (*sec)->next;
	temp->next = *first;
	*first = (*first)->next;
	curr->next = temp;
	curr = curr->next->next;
    }
    if (*first != NULL)
    {
	curr->next = *first;
	*first = NULL;
	free(*first);
    }
    if (*sec != NULL)
    {
	curr->next = *sec;
	*sec = NULL;
	free(*sec);
    }
}

void sortedmerge(struct node ** head, struct node ** first, struct node ** sec)
{
    struct node * curr = NULL, * prev = NULL;
    while (1)
    {
	if (*first == NULL)
	{
	    curr = *sec;
	    *sec = NULL;
	    free(*sec);
	    if (prev == NULL)
	    {
		prev = curr;
		prev->next = NULL;
		*head = prev;
	    }
	    else
	    {
		prev->next = curr;
	    }
	    return;
	}
	else if (*sec == NULL)
	{
	    curr = *first;
	    *first = NULL;
	    free(*first);
	    if (prev == NULL)
	    {
		prev = curr;
		prev->next = NULL;
		*head = prev;
	    }
	    else
	    {
		prev->next = curr;
	    }
	    return;
	}
	else
	{
	    if ((*first)->data <= (*sec)->data)
	    {
		curr = (*first)->next;
		if (prev == NULL)
		{
		    prev = *first;
		    prev->next = NULL;
		    *head = prev;
		}
		else
		{
		    prev->next = *first;
		    prev = prev->next;
		    prev->next = NULL;
		}
		*first = curr;
	    }
	    else
	    {
		curr = (*sec)->next;
		if (prev == NULL)
		{
		    prev = *sec;
		    prev->next = NULL;
		    *head = prev;
		}
		else
		{
		    prev->next = *sec;
		    prev = prev->next;
		    prev->next = NULL;
		}
		*sec = curr;
	    }
	}
    }
}

void  mergesort(struct node ** head)
{
    if (*head == NULL || (*head)->next == NULL)
    {
	return;
    }
    struct node * result;
    struct node * first, * sec;
    split(*head, &first, &sec);
    mergesort(&first);
    mergesort(&sec);
    sortedmerge(&result, &first, &sec);
    *head = result;
}

void sortedintersect(struct node ** head, struct node * one, struct node * two)
{
    struct node * t1 = one;
    struct node * t2 = two;
    while(1)
    {
	if (t1 == NULL || t2 == NULL)
	{
	    break;
	}
	else
	{
	    if (t1->data < t2->data)
	    {
	        t1 = t1->next;
	    }
	    else if (t1->data > t2->data)
	    {
	        t2 = t2->next;
	    }
	    else
	    {
		insertlast(head, t1->data);
	    }
	}
    }
}

void reverse (struct node ** head)
{
    if (*head == NULL || (*head)->next == NULL)
    {
	return;
    }
    struct node * temp = (*head)->next;
    struct node * prev = *head;
    while (temp != NULL)
    {
        prev->next = temp->next;
	temp->next = *head;
	*head = temp;
	temp = prev->next;
    }
}

void recursivereverse (struct node ** head)
{
    if (*head == NULL || (*head)->next == NULL)
    {
	return;
    }
    struct node * temp = *head;
    struct node * rest = temp->next;
    recursivereverse(&rest);
    temp->next->next = temp;
    temp->next = NULL;
    *head = rest;
}

void onetwothree(struct node ** head, int n)
{
    for (int i=0; i<n; i++)
    {
	insertlast(head, i);
    }
}

int main()
{
    struct node * head = NULL;
    while (true)
    {
        int n;
        cout << "Enter choice\n";
        cin >> n;
        int data, index;
        struct node * first = NULL;
        struct node * sec = NULL;
        switch (n)
        {
            case 1:
                cout << "Length of list is " << length(head) << endl;
                break;
            case 2:
                cout << "Enter data\n";
                cin >> data;
                insertlast(&head, data);
                break;
            case 3:
                cout << "Enter number\n";
                cin >> data;
                cout << count(head, data) << " occurrence(s)\n";
                break;
            case 4:
                cout << "deleting...\n";
                deletelist(&head);
                break;
            case 5:
                cout << "Enter data\n";
                cin >> data;
                inserthead(&head, data);
                break;
            case 6:
                cout << "Enter index and data\n";
                cin >> index >> data;
                insertnth(&head, index, data);
                break;
            case 7:
                cout << "Enter data\n";
                cin >> data;
                sortedinsert(&head, data);
                break;
            case 8:
                cout << "Sorting list...\n";
                sort(&head);
                break;
            case 9:
                cout << " Splitting...\n";
                split(head, &first, &sec);
                cout << "First list\n";
                print(first);
                cout << "Second list\n";
                print(sec);
                break;
	    case 10:
		cout << "duplicates removal\n";
		removedup(&head);
		break;
	    case 11:
		cout << "Alternate Splitting...\n";
		altsplit(head, &first, &sec);
		cout << "First list\n";
		print(first);
		cout << "Second list\n";
		print(sec);
		break;
	    case 12:
		cout << "Shuffle merging\n";
		onetwothree(&first, 4);
		cout << "First list\n";
		print(first);
		onetwothree(&sec, 8);
		cout << "Second list\n";
		print(sec);
		shufflemerge(&head, &first, &sec);
		break;
	    case 13:
		cout << "Sorted merging\n";
		onetwothree(&first, 4);
		cout << "First list\n";
		print(first);
		onetwothree(&sec, 8);
		cout << "Second list\n";
		print(sec);
		sortedmerge(&head, &first, &sec);
		break;
	    case 14:
		cout << "merge sort...\n";
		mergesort(&head);
		break;
	    case 15:
		cout << "First list\n";
		onetwothree(&first, 4);
		print(first);
		cout << "Second list\n";
		onetwothree(&sec, 8);
		print(sec);
		cout << "Intersection of lists\n";
		sortedintersect(&head, first, sec);
		break;
	    case 16:
		cout << "Reverse list\n";
		reverse(&head);
		break;
	    case 17:
		cout << "recursive reverse\n";
		recursivereverse(&head);
		break;
	    case 0:
		cout << "List elements\n";
		print(head);
		break;
            case -1:
                exit(0);
            default:
                break;
        }
    }
    return 0;
}
