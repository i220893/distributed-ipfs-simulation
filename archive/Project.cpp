#pragma once
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <string>
#include <conio.h>                  // for GetCh (Just For Asthetics)
#include <direct.h>                // For mkdir()
#include <fstream>
#include "sha1.h"
#include "BigInt.cpp"
using namespace std;

//******************************************************
//************** SINGLY LINKED LIST ********************
//******************************************************


template <class Type>
class Node
{
public:
    Type data;
    Node<Type>* next;

    Node(Type value = 0)
    {
        data = value;
        next = NULL;
    }
};

template <class Type>
class SLinkedList
{
public:
    Node<Type>* head;

    SLinkedList()
    {
        head = NULL;
    }

    void insert(Type value)
    {
        Node<Type>* temp = new Node<Type>(value);
        Node<Type>* mover = head;

        if (head == NULL)
        {
            head = temp;
        }

        else
        {
            while (mover->next != NULL)
            {
                mover = mover->next;
            }

            mover->next = temp;
        }

    }

    void insertAtHead(Type value)
    {
        Node<Type>* temp = new Node<Type>(value);

        if (head == NULL)
        {
            head = temp;
        }

        else
        {
            temp->next = head;
            head = temp;
        }
    }

    bool isEmpty()
    {
        if (head == NULL)
        {
            return true;
        }

        return false;
    }

    bool search(Type Value)
    {
        Node <Type>* mover = head;
        int count = 0;

        while (mover != NULL)
        {
            if (mover->data == Value)
                return true;

            count++;
            mover = mover->next;
        }

        return false;
    }

    void update(int location, Type Value)
    {
        Node <Type>* mover = head;

        for (int i = 0; i < location; i++)
        {
            mover = mover->next;
        }

        mover->data = Value;
    }

    void InsertAtIndex(Type Value, int index)
    {
        Node <Type>* mover1 = head;
        Node <Type>* mover2 = head->next;
        Node <Type>* temp = new Node<Type>(Value);

        for (int i = 0; i < index - 1; i++)
        {
            mover1 = mover2;
            mover2 = mover2->next;
        }

        mover1->next = temp;
        temp->next = mover2;
    }

    void remove(Type Value)
    {
        Node <Type>* mover1 = head;
        Node <Type>* mover2 = head->next;

        while (mover2->data != Value)
        {
            mover1 = mover2;
            mover2 = mover2->next;
        }

        mover1->next = mover2->next;
        delete mover2;
    }

    void print()
    {
        Node <Type>* mover1 = head;

        while (mover1 != NULL)
        {
            cout << mover1->data << endl;

            mover1 = mover1->next;
        }
    }
};


//******************************************************
//****************** FILE SYSTEM ***********************
//******************************************************

struct File
{
    long int key;
    string path;

    File(long int k = 0, string p = "EMPTY")
    {
        key = k;
        path = p;
    }
};

//******************************************************
//********************* B-TREE *************************
//******************************************************

#define MAX 4
#define MIN 2

struct btnode
{
    int count;
    File value[MAX + 1];
    btnode* child[MAX + 1];
};

btnode* insert(File, btnode*);

int setval(File, btnode*, int*, btnode**);

btnode* search(File, btnode*, int*);

int searchnode(File, btnode*, int*);

void fillnode(File, btnode*, btnode*, int);

void split(File, btnode*, btnode*, int, int*, btnode**);

btnode* del(File, btnode*);

int delhelp(File, btnode*);

void clear(btnode*, int);

void copysucc(btnode*, int);

void restore(btnode*, int);

void rightshift(btnode*, int);

void leftshift(btnode*, int);

void merge(btnode*, int);

void display(btnode*);


// search for the node
int searchnode(File val, btnode* bt_node, int* position)
{
    if (val.key < bt_node->value[1].key)
    {
        *position = 0;
        return 0;
    }
    else
    {
        *position = bt_node->count;
        while ((val.key < bt_node->value[*position].key) && *position > 1)
        {
            (*position)--;
        }
        if (val.key == bt_node->value[*position].key)
        {
            return 1;
        }
        else
            return 0;
    }
}

// Adjust value of the node
void fillnode(File val, btnode* c, btnode* bt_node, int k)
{
    int i;
    for (i = bt_node->count; i > k; i--)
    {
        bt_node->value[i + 1] = bt_node->value[i];
        bt_node->child[i + 1] = bt_node->child[i];
    }
    bt_node->value[k + 1] = val;
    bt_node->child[k + 1] = c;
    bt_node->count++;
}

// split in node
void split(File val, btnode* c, btnode* bt_node, int k, File* y, btnode** newnode)
{
    int i, mid;
    if (k <= MIN)
        mid = MIN;
    else
        mid = MIN + 1;

    *newnode = new btnode;
    for (i = mid + 1; i <= MAX; i++)
    {
        (*newnode)->value[i - mid] = bt_node->value[i];
        (*newnode)->child[i - mid] = bt_node->child[i];
    }
    (*newnode)->count = MAX - mid;
    bt_node->count = mid;
    if (k <= MIN)
    {
        fillnode(val, c, bt_node, k);
    }
    else
        fillnode(val, c, *newnode, k - mid);
    *y = bt_node->value[bt_node->count];

    (*newnode)->child[0] = bt_node->child[bt_node->count];
    bt_node->count--;
}

// search value in node
btnode* search(File val, btnode* root, int* position)
{
    if (root == nullptr)
    {
        return nullptr;
    }
    else
    {
        if (searchnode(val, root, position))
        {
            return root;
        }
        else
            return search(val, root->child[*position], position);
    }
}

// set value in B-Tree
int setval(File val, btnode* bt_node, File* p, btnode** c)
{
    int k;
    if (bt_node == nullptr)
    {
        *p = val;
        *c = nullptr;
        return 1;
    }
    else
    {
        if (searchnode(val, bt_node, &k))
        {
            cout << "Key value already exists" << endl;
        }
        if (setval(val, bt_node->child[k], p, c))
        {
            if (bt_node->count < MAX)
            {
                fillnode(*p, *c, bt_node, k);
                return 0;
            }
            else
            {
                split(*p, *c, bt_node, k, p, c);
                return 1;
            }
        }
        return 0;
    }
}

// Insert value in B-Tree
btnode* insert(File val, btnode* root)
{
    File i;
    btnode* c;
    btnode* bt_node;
    int flag;
    flag = setval(val, root, &i, &c);
    if (flag)
    {
        btnode* bt_node = new btnode;
        bt_node->count = 1;
        bt_node->value[1] = i;
        // bt_node->value[1].path = val.path;
        // cout << bt_node->value[1].path << endl;
        bt_node->child[0] = root;
        bt_node->child[1] = c;
        return bt_node;
    }
    return root;
}

btnode* del(File val, btnode* root)
{
    btnode* temp;
    if (!delhelp(val, root))
    {
        cout << endl;
        cout << "Value " << val.key << " not found.";
    }
    else
    {
        if (root->count == 0)
        {
            temp = root;
            root = root->child[0];
            delete temp;
        }
    }
    return root;
}


/* helper function for del() */
int delhelp(File val, struct btnode* root)
{
    int i;
    int flag;
    if (root == NULL)
        return 0;
    else
    {
        flag = searchnode(val, root, &i);
        if (flag)
        {
            if (root->child[i - 1])
            {
                copysucc(root, i);
                flag = delhelp(root->value[i], root->child[i]);
                if (!flag)
                {
                    cout << endl;
                    cout << "Value " << val.key << "not found.\bt_node";
                }
            }
            else
                clear(root, i);
        }
        else
            flag = delhelp(val, root->child[i]);

        if (root->child[i] != NULL)
        {
            if (root->child[i]->count < MIN)
                restore(root, i);
        }
        return flag;
    }
}

/*removes the value from the node and adjusts the values */
void clear(btnode* node, int k)
{
    int i;
    for (i = k + 1; i <= node->count; i++)
    {
        node->value[i - 1] = node->value[i];
        node->child[i - 1] = node->child[i];
    }
    node->count--;
}

// copies the successor of the value that is to be deleted 
void copysucc(btnode* node, int i)
{
    btnode* temp;

    temp = node->child[i];

    while (temp->child[0])
        temp = temp->child[0];

    node->value[i] = temp->value[1];
}

/* adjusts the node*/
void restore(btnode* node, int i)
{
    if (i == 0)
    {
        if (node->child[1]->count > MIN)
            leftshift(node, 1);
        else
            merge(node, 1);
    }
    else
    {
        if (i == node->count)
        {
            if (node->child[i - 1]->count > MIN)
                rightshift(node, i);
            else
                merge(node, i);
        }
        else
        {
            if (node->child[i - 1]->count > MIN)
                rightshift(node, i);
            else
            {
                if (node->child[i + 1]->count > MIN)
                    leftshift(node, i + 1);
                else
                    merge(node, i);
            }
        }
    }
}

// Adjusts the Values and Children while shifitng the value from parent to right child

void rightshift(btnode* node, int k)
{
    int i;
    btnode* temp;

    temp = node->child[k];

    for (i = temp->count; i > 0; i--)
    {
        temp->value[i + 1] = temp->value[i];
        temp->child[i + 1] = temp->child[i];
    }

    temp->child[1] = temp->child[0];
    temp->count++;
    temp->value[1].key = node->value[k].key;

    temp = node->child[k - 1];
    node->value[k].key = temp->value[temp->count].key;
    node->child[k]->child[0] = temp->child[temp->count];
    temp->count--;
}


// Adjusts the Values and Children while shifitng the value from parent to left child

void leftshift(btnode* node, int k)
{
    int i;
    btnode* temp;

    temp = node->child[k - 1];
    temp->count++;
    temp->value[temp->count] = node->value[k];
    temp->child[temp->count] = node->child[k]->child[0];

    temp = node->child[k];
    node->value[k] = temp->value[1];
    temp->child[0] = temp->child[1];
    temp->count--;

    for (i = 1; i <= temp->count; i++)
    {
        temp->value[i] = temp->value[i + 1];
        temp->child[i] = temp->child[i + 1];
    }
}

// merges two nodes

void merge(btnode* node, int k)
{
    int i;
    struct btnode* temp1, * temp2;

    temp1 = node->child[k];
    temp2 = node->child[k - 1];
    temp2->count++;
    temp2->value[temp2->count] = node->value[k];
    temp2->child[temp2->count] = node->child[0];

    for (i = 1; i < temp1->count; i++)
    {
        temp2->count++;
        temp2->value[temp2->count] = temp1->value[i];
        temp2->child[temp2->count] = temp1->child[i];
    }

    for (i = k; i < node->count; i++)
    {
        node->value[i] = node->value[i + 1];
        node->child[i] = node->child[i + 1];
    }

    node->count--;
    free(temp1);
}


void display(btnode* root)
{
    int i;

    if (root != NULL)
    {
        for (i = 0; i < root->count; i++)
        {
            display(root->child[i]);

            cout << root->value[i + 1].key << "  " << root->value[i + 1].path << endl;
        }

        display(root->child[i]);
    }
}
//******************************************************
//********************* MACHINE ************************
//******************************************************

class Machine
{
public:

    btnode* root;
    int ID;
    Machine* next;

    Machine(int name = 0)
    {
        root = NULL;
        ID = name;
        next = NULL;
    }

    void insert_in_Btree(File F)
    {
        root = insert(F, root);
    }
};

//******************************************************
//*************** DOUBLY LINKED LIST *******************
//******************************************************

class DoublyNode
{
public:

    Machine* data;
    DoublyNode* prev;
    DoublyNode* next;


    DoublyNode(Machine* M = NULL)
    {
        data = M;
        prev = NULL;
        next = NULL;
    }
};

class DoublyLinkedList
{
    DoublyNode* head;

public:
    DoublyLinkedList()
    {
        head = NULL;
    }

    bool isEmpty()
    {
        if (head == NULL)
            return true;

        return false;
    }

    void insert(Machine* num)
    {
        DoublyNode* temp = new DoublyNode(num);

        if (head == NULL)
        {
            head = temp;
        }

        else
        {
            DoublyNode* mover1 = head;
            DoublyNode* mover2 = head;

            while (mover2 != NULL)
            {
                mover1 = mover2;
                mover2 = mover2->next;
            }


            mover2 = temp;
            mover2->prev = mover1;
            mover1->next = mover2;
        }
    }

    void insertToHead(Machine* num)
    {
        DoublyNode* temp = new DoublyNode(num);

        if (head == NULL)
        {
            head = temp;
        }

        else
        {
            head->prev = temp;
            temp->next = head;
            head = temp;
        }
    }

    bool search(int num)
    {
        DoublyNode* mover = head;

        while (mover != NULL)
        {
            if (mover->data->ID == num)
                return true;

            mover = mover->next;
        }

        return false;
    }

    void update(Machine* num, Machine* replace_with)
    {
        DoublyNode* mover = head;

        while (mover != NULL)
        {
            if (mover->data->ID == num->ID)
                mover->data = replace_with;

            mover = mover->next;
        }
    }

    void insertAtIndex(Machine* num, int index)
    {
        DoublyNode* temp = new DoublyNode(num);

        if (index == 0)
        {
            insertToHead(num);
        }

        else
        {
            DoublyNode* mover1 = head;
            DoublyNode* mover2 = head;

            for (int i = 0; i < index; i++)
            {
                mover1 = mover2;
                mover2 = mover2->next;
            }

            mover2->prev = temp;
            temp->next = mover2;
            mover1->next = temp;
            temp->prev = mover1;
        }
    }

    void deleteData(Machine* num)
    {
        DoublyNode* mover1 = head;
        DoublyNode* mover2 = head->next;
        DoublyNode* mover3 = mover2->next;

        while (mover2 != NULL)
        {
            if (mover2->data->ID == num->ID)
            {
                mover3->prev = mover1;
                mover1->next = mover3;
                delete mover2;
                break;
            }

            mover1 = mover2;
            mover2 = mover2->next;
        }
    }

    void print()
    {
        DoublyNode* mover = head;

        while (mover != NULL)
        {

            cout << mover->data->ID << endl;
            mover = mover->next;
        }

    }
};

//******************************************************
//************** CIRCULAR LINKED LIST ******************
//******************************************************

class CircularNode
{
public:
    Machine M;
    DoublyLinkedList Routing_Table;
    CircularNode* next;
    int ID;

    CircularNode(int num = 0)
    {
        ID = num;
        next = NULL;
        M.ID = num;
    }

    void DisplayRoutingTable()
    {
        Routing_Table.print();
    }


};

class CircularLinkedList
{
public:
    CircularNode* head;


    CircularLinkedList()
    {
        head = NULL;
    }

    bool isEmpty()
    {
        if (head == NULL)
            return true;

        return false;
    }

    void insert(int value)
    {
        CircularNode* mover = new CircularNode(value);

        if (head == nullptr || value < head->ID)
        {
            if (head == nullptr)
            {
                mover->next = mover;
            }

            else
            {
                CircularNode* last = getLastNode();
                mover->next = head;
                last->next = mover;
            }

            head = mover;
        }

        else
        {
            CircularNode* current = head;

            while (current->next != head && current->next->ID < value)
            {
                current = current->next;
            }

            mover->next = current->next;
            current->next = mover;
        }
    }


    CircularNode* getLastNode()
    {
        if (head == nullptr)
        {
            return nullptr;
        }

        CircularNode* last = head;

        while (last->next != head)
        {
            last = last->next;
        }

        return last;
    }

    bool search(int num)
    {
        CircularNode* mover = head;
        do
        {
            if (mover->ID == num)
                return true;

            mover = mover->next;
        } while (mover != head);

        return false;
    }

    /*
    void deleteData(int num)
    {
        Node* mover1 = head;
        Node* mover2 = head->next;
        Node* mover3 = mover2->next;

        if (head->data == num)
        {
            head = head->next;
            mover1 = head;
            mover2 = head->next;
        }

        else
        {
            do
            {
                if (mover2->data == num)
                {
                    mover1->next = mover3;
                    delete mover2;
                    break;
                }

                mover1 = mover2;
                mover2 = mover3;
                mover3 = mover3->next;
            } while (mover2 != head);
        }


    }
    */
    void print()
    {
        CircularNode* mover = head;

        do
        {
            if (mover == NULL)
                break;
            cout << mover->M.ID << endl;
            mover = mover->next;

        } while (mover != head);

    }
};


//***********************************************************
//********* InterPlanetary File System (IPFS) ***************
//***********************************************************

class IPFS
{
public:
    CircularLinkedList Hosts;
    int bits;
    long long int total_machines;
    long long int num_activated_machines;
    SLinkedList<int>activated_machines;

    IPFS(int input_bits = 0)
    {
        bits = input_bits;
        total_machines = pow(2, bits);
        num_activated_machines = 0;
    }

    Machine* SearchMachine(long long int ID)
    {
        CircularNode* mover = Hosts.head;

        do
        {
            if (mover->ID == ID)
                return &(mover->M);

            mover = mover->next;

        } while (mover != Hosts.head);
    }

    void SetRoutingTable()
    {
        long long int temp = 0;
        CircularNode* mover = Hosts.head;
        int count = 0;

        do
        {
            if (activated_machines.search(mover->ID) == true)
            {
                count = 0;
                for (int i = 1; i <= bits; i++)
                {
                    temp = mover->ID + pow(2, i - 1);
                    temp = temp % total_machines;

                    for (long long int j = temp; j < total_machines; j++)
                    {
                        if (activated_machines.search(j) == true)
                        {
                            count++;
                            mover->Routing_Table.insert(SearchMachine(j));
                            break;
                        }

                        if (j + 1 == total_machines && count < bits)
                        {
                            j = 0;
                        }
                    }
                }
            }

            mover = mover->next;
        } while (mover != Hosts.head);
    }

    bool Insert_Machine(int Machine_ID)
    {
        if (Machine_ID == -1)
        {
            int random = rand() % total_machines;

            while (activated_machines.search(random) == true)
                random = rand() % total_machines;

            Hosts.insert(random);

            num_activated_machines++;

            activated_machines.insert(random);

            string Folder_Name = "Machine ID ";
            Folder_Name = Folder_Name + to_string(random);

            const char* folder_name = Folder_Name.c_str();

            int status = _mkdir(folder_name);

            if (status == 0)
            {
                cout << "Folder created successfully!" << endl;
            }

            else
            {
                cout << "Error creating folder." << endl;
            }

            return true;

        }

        else
        {
            if (activated_machines.search(Machine_ID) == true)
            {
                cout << "Error! Duplicate IDs Not Allowed!" << endl;
                return false;
            }

            Hosts.insert(Machine_ID);

            num_activated_machines++;

            activated_machines.insert(Machine_ID);

            string Folder_Name = "Machine ID ";
            Folder_Name = Folder_Name + to_string(Machine_ID);

            const char* folder_name = Folder_Name.c_str();

            int status = _mkdir(folder_name);

            if (status == 0)
            {
                cout << "Folder created successfully!" << endl;
            }

            else
            {
                cout << "Error creating folder." << endl;
            }

            return true;
        }
    }

    bool Check_ID(int Machine_ID)
    {
        if (activated_machines.search(Machine_ID) == false)
        {
            cout << "Error! Machine Not Turned On!" << endl;
            cout << "Enter ID Again: ";
            return false;
        }

        return true;
    }

    long long int MakeHashFunction(string path)
    {

    }

    void InsertFile(string path)
    {
        long long int File_ID = MakeHashFunction(path);
    }

    void MENU(int Machine_ID)
    {
        int selection = 1;

        cout << "Working On Machine With ID: " << Machine_ID << endl << endl;

        cout << "Press 1 To Insert A File" << endl;
        cout << "Press 2 To Delete A File" << endl;
        cout << "Press 3 To Display A File" << endl;
        cout << "Press 4 To Turn Off A Machine" << endl;
        cout << "Press 5 To Turn On A Machine" << endl;
        cout << "Press 6 To Display Routing Table" << endl;

        cout << endl << "Enter Command: ";
        cin >> selection;

        CircularNode* mover = Hosts.head;
        switch (selection)
        {

        case 1:
            //Inserting File


            break;


        case 2:
            //Deleting File


            break;


        case 3:
            //Displaying File


            break;


        case 4:
            //Turning off a machine


            break;


        case 5:
            //Turning on a machine


            break;



        case 6:

            do
            {
                cout << "Routing Table of ID # " << mover->ID << " is: " << endl;
                mover->DisplayRoutingTable();
                cout << endl;

                mover = mover->next;

            } while (mover != Hosts.head);

            break;

        default:
            cout << "Incorrect Option!" << endl;
        }






    }



    void Start()
    {

        cout << "                                  __          __  _                            _          _____ _____  ______ _____       " << endl;
        cout << "                                  \\ \\        / / | |                          | |        |_   _|  __ \\|  ____/ ____|      " << endl;
        cout << "                                   \\ \\  /\\  / ___| | ___ ___  _ __ ___   ___  | |_ ___     | | | |__) | |__ | (___        " << endl;
        cout << "                                    \\ \\/  \\/ / _ | |/ __/ _ \\| '_ ` _ \\ / _ \\ | __/ _ \\    | | |  ___/|  __| \\___ \\       " << endl;
        cout << "                                     \\  /\\  |  __| | (_| (_) | | | | | |  __/ | || (_) |  _| |_| |    | |    ____) |      " << endl;
        cout << "                                      \\/  \\/ \\___|_|\\___\\___/|_| |_| |_|\\___|  \\__\\___/  |_____|_|    |_|   |_____/       " << endl;
                                                                                                 
                                                                                                
        cout<<"\n";                 
        cout<<"\n";                 
                                    
        cout << "                            _    _                       ______                            ___  ___  _         ___   ___   ___ __         " << endl;
        cout << "                           | |  | |                     |  ____|                          |__ \\|__ \\(_)       / _ \\ / _ \\ / _ /_ |        " << endl;
        cout << "                           | |  | |_ __ ___   ___ _ __  | |__ __ _ _ __ ___   ___   __ _     ) |  ) |_ ______| | | | (_) | (_) | |        " << endl;
        cout << "                           | |  | | '_ ` _ \\ / _ | '__| |  __/ _` | '__/ _ \\ / _ \\ / _` |   / /  / /| |______| | | |> _ < \\__, | |        " << endl;
        cout << "                           | |__| | | | | | |  __| |    | | | (_| | | | (_) | (_) | (_| |  / /_ / /_| |      | |_| | (_) |  / /| |        " << endl;
        cout << "                            \\____/|_| |_| |_|\\___|_|    |_|  \\__,_|_|  \\___/ \\___/ \\__, | |____|____|_|       \\___/ \\___/  /_/ |_|        " << endl;
        cout << "                                                                                      | |                                                 " << endl;
        cout << "                                                                                      |_|                                                 " << endl;
                                    
        cout<<"\n";                 
        cout<<"\n";                 
        cout << "                    _    _                     _        __          __                             ___  ___  _         ___   ___   ___ ____        " << endl;
        cout << "                   | |  | |                   (_)       \\ \\        / /                            |__ \\|__ \\(_)       / _ \\ / _ \\ / _ |___ \\       " << endl;
        cout << "                   | |__| |_   _ ___ ___  __ _ _ _ __    \\ \\  /\\  / __ _ ___  ___  ___ _ __ ___      ) |  ) |_ ______| | | | (_) | (_) |__) |      " << endl;
        cout << "                   |  __  | | | / __/ __|/ _` | | '_ \\    \\ \\/  \\/ / _` / __|/ _ \\/ _ | '_ ` _ \\    / /  / /| |______| | | |> _ < \\__, |__ <       " << endl;
        cout << "                   | |  | | |_| \\__ \\__ | (_| | | | | |    \\  /\\  | (_| \\__ |  __|  __| | | | | |  / /_ / /_| |      | |_| | (_) |  / /___) |      " << endl;
        cout << "                   |_|  |_|\\__,_|___|___/\\__,_|_|_| |_|     \\/  \\/ \\__,_|___/\\___|\\___|_| |_| |_| |____|____|_|       \\___/ \\___/  /_/|____/       " << endl;
                                                        
        cout<<"\n";                 
        cout<<"\n";                 
        cout<<"\n";                 
        cout<<"\n";                 
                         
        
        cout << "                                 _____      _                   _  ___                   ___  ___  _         ___   ___ __ __         " << endl;
        cout << "                                |_   _|    | |                 | |/ | |                 |__ \\|__ \\(_)       / _ \\ / _ /_ /_ |        " << endl;
        cout << "                                  | |  _ __| |_ __ _ ______ _  | ' /| |__   __ _ _ __      ) |  ) |_ ______| | | | (_) | || |        " << endl;
        cout << "                                  | | | '__| __/ _` |_  / _` | |  < | '_ \\ / _` | '_ \\    / /  / /| |______| | | |\\__, | || |        " << endl;
        cout << "                                 _| |_| |  | || (_| |/ | (_| | | . \\| | | | (_| | | | |  / /_ / /_| |      | |_| |  / /| || |        " << endl;
        cout << "                                |_____|_|   \\__\\__,_/___\\__,_| |_|\\_|_| |_|\\__,_|_| |_| |____|____|_|       \\___/  /_/ |_||_|        " << endl;
                                                                                              
                                                                                              

                                                                                                                           
                                                                                                                       


















        bits = _getch();
        system("CLS");





        cout << "                 _____       _            _____  _                  _                     ______ _ _         _____           _                 " << endl;
        cout << "                |_   _|     | |          |  __ \\| |                | |                   |  ____(_) |       / ____|         | |                " << endl;
        cout << "                  | |  _ __ | |_ ___ _ __| |__) | | __ _ _ __   ___| |_ __ _ _ __ _   _  | |__   _| | ___  | (___  _   _ ___| |_ ___ _ __ ___  " << endl;
        cout << "                  | | | '_ \\| __/ _ \\ '__|  ___/| |/ _` | '_ \\ / _ \\ __/ _` | '__| | | | |  __| | | |/ _ \\  \\___ \\| | | / __| __/ _ \\ '_ ` _ \\ " << endl;
        cout << "                 _| |_| | | | ||  __/ |  | |    | | (_| | | | |  __/ || (_| | |  | |_| | | |    | | |  __/  ____) | |_| \\__ \\ ||  __/ | | | | |" << endl;
        cout << "                |_____|_| |_|\\__\\___|_|  |_|    |_|\\__,_|_| |_|\\___|\\__\\__,_|_|   \\__, | |_|    |_|_|\\___| |_____/ \\__, |___/\\__\\___|_| |_| |_|" << endl;
        cout << "                                                                                   __/ |                            __/ |                      " << endl;
        cout << "                                                                                  |___/                            |___/                       " << endl;










        cout << "Enter Bits: ";
        cin >> bits;

        while (bits < 0)
        {
            cout << "Invalid Input! Enter Again: ";
            cin >> bits;
        }

        if (bits > 62)
        {
            total_machines = 9223372036854775807;
        }
        else
            total_machines = pow(2, bits);


        int to_activate = -1;
        int Machine_ID = 0;
        bool check = true;

        cout << "Enter Machines to Activate: ";
        cin >> to_activate;

        while (to_activate > total_machines || to_activate < 0)
        {
            cout << "Invalid Input! Enter Again: ";
            cin >> to_activate;
        }

        for (int i = 0; i < to_activate; i++)
        {
            if (num_activated_machines == total_machines)
            {
                cout << "Machines Limit Reached!" << endl;
                break;
            }

            cout << endl << "Enter The ID of the Machine to Be Inserted (Enter -1 to Randomly Choose):";
            cin >> Machine_ID;

            if (Machine_ID == -1)
            {
                cout << "Random Value Selected!" << endl;
                check = Insert_Machine(Machine_ID);

                if (check == false)
                    i--;
            }

            else if (Machine_ID > total_machines - 1)
            {
                cout << "Invalid ID! Please Enter A Smaller ID!" << endl;
                i--;
            }

            else if (Machine_ID < -1)
            {
                cout << "Invalid ID! Please Enter A Larger ID!" << endl;
                i--;
            }

            else
            {
                cout << "Custom Value Selected!" << endl;
                check = Insert_Machine(Machine_ID);

                if (check == false)
                    i--;
            }
        }

        SetRoutingTable();

        int User_ID = 0;

        cout << endl << "ID of Machines Currently Turned On: " << endl;
        Hosts.print();

        cout << endl << endl << "Enter The ID Of the Machine You Want To Use: ";
        cin >> User_ID;

        while (Check_ID(User_ID) == false)
        {
            cin >> User_ID;
        }




        cout << endl << endl << "Press Any Key To Continue: ";
        _getch();

        system("CLS");

        cout << "                 _____       _            _____  _                  _                     ______ _ _         _____           _                 " << endl;
        cout << "                |_   _|     | |          |  __ \\| |                | |                   |  ____(_) |       / ____|         | |                " << endl;
        cout << "                  | |  _ __ | |_ ___ _ __| |__) | | __ _ _ __   ___| |_ __ _ _ __ _   _  | |__   _| | ___  | (___  _   _ ___| |_ ___ _ __ ___  " << endl;
        cout << "                  | | | '_ \\| __/ _ \\ '__|  ___/| |/ _` | '_ \\ / _ \\ __/ _` | '__| | | | |  __| | | |/ _ \\  \\___ \\| | | / __| __/ _ \\ '_ ` _ \\ " << endl;
        cout << "                 _| |_| | | | ||  __/ |  | |    | | (_| | | | |  __/ || (_| | |  | |_| | | |    | | |  __/  ____) | |_| \\__ \\ ||  __/ | | | | |" << endl;
        cout << "                |_____|_| |_|\\__\\___|_|  |_|    |_|\\__,_|_| |_|\\___|\\__\\__,_|_|   \\__, | |_|    |_|_|\\___| |_____/ \\__, |___/\\__\\___|_| |_| |_|" << endl;
        cout << "                                                                                   __/ |                            __/ |                      " << endl;
        cout << "                                                                                  |___/                            |___/                       " << endl;


        MENU(User_ID);




        cout << endl << endl << "Press Any Key To Continue: ";
        _getch();
        system("CLS");
    }

};


int main()
{
    srand(time(0));

    IPFS check;
    check.Start();



    return 0;


}
