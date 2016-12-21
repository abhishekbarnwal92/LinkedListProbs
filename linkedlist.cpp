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
            case -1:
                exit(0);
            default:
                break;
        }
    }
    return 0;
}
