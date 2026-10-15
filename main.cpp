#pragma once
#include <iostream>
#include <cmath>
#include <random>
#include <cstdlib>
#include <cstring>
#include <string>
#include <conio.h>                  // for GetCh (Just For Asthetics)
#include <direct.h>                // For mkdir()
#include <fstream>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;


#include "BigInt.cpp"
#include "HashCheck.h"
using namespace std;

//******************************************************
//************** SINGLY LINKED LIST ********************
//******************************************************


template <class Type>
class Singly_Node
{
public:
    Type data;
    Singly_Node<Type>* next;

    Singly_Node(Type value = 0)
    {
        data = value;
        next = NULL;
    }
};

template <class Type>
class SLinkedList
{
public:
    Singly_Node<Type>* head;

    SLinkedList()
    {
        head = NULL;
    }

    void insert(Type value)
    {
        Singly_Node<Type>* temp = new Singly_Node<Type>(value);
        Singly_Node<Type>* mover = head;

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
        Singly_Node<Type>* temp = new Singly_Node<Type>(value);

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
        Singly_Node <Type>* mover = head;
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
        Singly_Node <Type>* mover = head;

        for (int i = 0; i < location; i++)
        {
            mover = mover->next;
        }

        mover->data = Value;
    }

    void InsertAtIndex(Type Value, int index)
    {
        Singly_Node <Type>* mover1 = head;
        Singly_Node <Type>* mover2 = head->next;
        Singly_Node <Type>* temp = new Singly_Node<Type>(Value);

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
        Singly_Node <Type>* mover1 = head;
        Singly_Node <Type>* mover2 = head->next;

        if (mover1->data == Value)
        {
            head = mover1->next;
        }

        if (mover2->data == Value)
        {
            head->next = NULL;
        }

        while (mover2->data != Value)
        {
            mover1 = mover2;
            mover2 = mover2->next;

            if (mover2 == NULL)
            {
                return;
            }


        }

        mover1->next = mover2->next;
        delete mover2;
    }

    void print()
    {
        Singly_Node <Type>* mover1 = head;

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

            cout << "D" << endl;
            cout << root->value[i + 1].key << "  " << root->value[i + 1].path << endl;
        }

        display(root->child[i]);
    }
}

void getPath(btnode* root, long long int ID, string& str)
{
    int i;

    if (root != NULL)
    {
        for (i = 0; i < root->count; i++)
        {
            getPath(root->child[i], ID, str);

            if (root->value[i + 1].key == ID)
            {
                str += root->value[i + 1].path;
                str += '\n';
            }

        }

        getPath(root->child[i], ID, str);
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
public:
    DoublyNode* head;


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
    long long int ID;

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


    void deleteData(long long int num)
    {
        CircularNode* mover1 = head;
        CircularNode* mover2 = head->next;
        CircularNode* mover3 = head->next->next;

        if (head->ID == num)
        {
            mover3 = getLastNode();
            head = head->next;
            mover1 = head;
            mover2 = head->next;
            mover3->next = head;
        }

        else
        {
            do
            {
                if (mover2->ID == num)
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
        long long count = 0;

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
                            //cout << j << endl;
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

    void ClearRoutingTable()
    {
        CircularNode* mover = Hosts.head;

        do
        {
            mover = mover->next;

            mover->Routing_Table.head = NULL;

        } while (mover != Hosts.head);

    }

    bool Insert_Machine(int Machine_ID)
    {
        if (Machine_ID == -1)
        {
            random_device rd;
            mt19937_64 gen(rd());
            uniform_int_distribution<long long> dis(0, (1LL << 62) - 1);

            long long int random = dis(gen) % total_machines;

            while (activated_machines.search(random) == true)
                random = dis(gen) % total_machines;

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


    long long int MakeHashFunction(string& input_path, string& TextInFile, Mat& img)
    {

        int input_size = 0;

        string TextInLine;
        string Hash_Phase1;
        int Hash = 0;

        cout << "Please Enter The Path of The File You Want to Insert Into the Machine: ";
        cin >> input_path;

        input_size = input_path.length();

        if (input_path[input_size - 1] == 'g' || input_path[input_size - 1] == 'f' || input_path[input_size - 1] == 'p')
        {
            img = imread(input_path);

            if (img.empty() == false)
            {
                Hash_Phase1 = sha1(img);

                for (int i = 0; i < Hash_Phase1.length(); i++)
                {
                    Hash += int(Hash_Phase1[i]);
                }

                Hash = Hash % total_machines;

                return Hash;

            }

            else
            {
                cout << "Incorrect Path! No File Exists at: " << input_path << endl;
                return -1;
            }

        }

        else
        {

            fstream File;
            File.open(input_path, ios::in);

            if (File.is_open())
            {
                while (getline(File, TextInLine))
                {
                    TextInFile += TextInLine;
                    TextInFile += "\n";

                }

                File.close();

                Hash_Phase1 = sha1(TextInFile);


                for (int i = 0; i < Hash_Phase1.length(); i++)
                {
                    Hash += int(Hash_Phase1[i]);
                }

                Hash = Hash % total_machines;
                return Hash;

            }

            else
            {
                cout << "Incorrect Path! No File Exists at: " << input_path << endl;
                return -1;
            }
        }
    }

    CircularNode* Currently_at(int Machine_ID)
    {
        CircularNode* mover = Hosts.head;

        do
        {
            if (mover->ID == Machine_ID)
                break;

            mover = mover->next;
        } while (mover != Hosts.head);

        return mover;
    }

    long long int Previous_Machine_ID(CircularNode* mover, long long int Machine_ID)
    {
        CircularNode* mover2 = Hosts.head;
        CircularNode* temp = Hosts.head->next;

        while (mover2->next->M.ID != mover->M.ID) {
            mover2 = mover2->next;
        }
        // cout << "\nPrev ID = " << mover2->M.ID << endl;
        // cout << "\nPrev ID = " << mover2->next->M.ID << endl;
        return mover2->M.ID;
    }

    long long int Maximum_Machine_ID() {
        CircularNode* mover2 = Hosts.head;
        long long int greatest = Hosts.head->M.ID;
        do
        {
            if (mover2->M.ID > greatest)
                greatest = mover2->M.ID;
            mover2 = mover2->next;
        } while (mover2 != Hosts.head);
        return greatest;
    }

    Machine* Find_Responsible_Machine(CircularNode* mover, long long int File_ID, long long int Machine_ID)
    {
        if (Machine_ID == File_ID)
        {
            return &(mover->M);
        }

        while (1)
        {

            if (mover->M.ID == File_ID)
                return &(mover->M);

            else if (File_ID < mover->M.ID && Currently_at(mover->M.ID) == Hosts.head) {
                return &(mover->M);
            }
            else if (File_ID < Hosts.head->ID) {
                return &(Hosts.head->M);
            }
            else if (mover->M.ID > File_ID && File_ID > Previous_Machine_ID(mover, mover->ID))
            {
                return &(mover->M);
            }
            else if (mover->M.ID < File_ID && File_ID > Maximum_Machine_ID() && mover->next == Hosts.head)
            {
                return &(Hosts.head->M);
            }
            else if (mover->M.ID > File_ID && File_ID < Maximum_Machine_ID() && mover->next == Hosts.head)
            {
                if (Hosts.head->M.ID < File_ID)
                {
                    mover = Hosts.head;
                    continue;
                }
                //else 
                //    return &(Hosts.head->M);
            }
            else if (File_ID == Hosts.head->M.ID)
            {
                return &(Hosts.head->M);
            }
            else {
                DoublyNode* Routing_head = mover->Routing_Table.head;
                while (Routing_head != nullptr)
                {
                    if (Routing_head->data->ID >= File_ID && mover->M.ID < File_ID)
                    {
                        mover = Currently_at(Routing_head->data->ID);
                        break;
                    }
                    else if (Routing_head->next != nullptr && Routing_head->data->ID < File_ID && File_ID <= Routing_head->next->data->ID)
                    {
                        mover = Currently_at(Routing_head->data->ID);
                        break;
                    }
                    else if (Routing_head->next != nullptr && Routing_head->data->ID < File_ID && Currently_at(Routing_head->next->data->ID) == Hosts.head)
                    {
                        mover = Currently_at(Routing_head->data->ID);
                        break;
                    }
                    else if (Routing_head->next != nullptr && Routing_head->data->ID > File_ID && Currently_at(Routing_head->next->data->ID) == Hosts.head)
                    {
                        mover = Currently_at(Routing_head->data->ID);
                        break;
                    }
                    else if (Routing_head->next == nullptr && Routing_head->data->ID < File_ID)
                    {
                        mover = Currently_at(Routing_head->data->ID);
                        break;
                    }
                    else if (Routing_head->next == nullptr && Routing_head->data->ID > File_ID)
                    {
                        mover = mover->next;
                        break;
                    }
                    else
                    {
                        Routing_head = Routing_head->next;
                    }
                }
            }
        }
    }

    string CopyToFolder(long long int Machine_ID, string& TextInFile, Mat& img, string FileName = "")
    {
        if (TextInFile.empty() == false)
        {

            fstream File;
            string Folder_Name = "Machine ID ";
            Folder_Name = Folder_Name + to_string(Machine_ID);
            Folder_Name += "\\";
            Folder_Name += FileName;

            File.open(Folder_Name, ios::out);

            if (File.is_open())
            {
                File << TextInFile;
            }

            return Folder_Name;
        }

        else if (img.empty() == false)
        {
            string Folder_Name = "Machine ID ";
            Folder_Name = Folder_Name + to_string(Machine_ID);
            Folder_Name += "\\";
            Folder_Name += FileName;
            imwrite(Folder_Name, img);

            return Folder_Name;
        }

        else
        {
            cout << "File Not Found!" << endl;
            return "ERROR";
        }
    }

    void InsertFile(long long int Machine_ID)
    {
        string TextInFile;
        string Path;
        string NewPath;
        Mat img;
        long long int File_ID = MakeHashFunction(Path, TextInFile, img);
        File_ID = (File_ID + Machine_ID) % total_machines;

        cout << File_ID << endl;

        if (File_ID == -1)
            return;



        CircularNode* mover = Currently_at(Machine_ID);

        Machine* Responsible = Find_Responsible_Machine(mover, File_ID, Machine_ID);

        cout << Responsible->ID << endl;


        int str_size = Path.length() - 1;
        string result;
        while (str_size >= 0 && Path[str_size] != '\\')
        {
            result = Path[str_size] + result;
            str_size--;
        }

        NewPath = CopyToFolder(Responsible->ID, TextInFile, img, result);

        if (NewPath == "ERROR")
            return;

        File temp(File_ID, NewPath);

        Responsible->insert_in_Btree(temp);


    }

    string MoveFile(long long int Machine_ID_to, string PreviousPath)
    {

        string FileName;
        string TextInFile;
        string TextInLine;
        string Path;
        string NewPath;
        Mat img;

        int str_size = PreviousPath.length() - 1;

        while (str_size >= 0 && PreviousPath[str_size] != '\\')
        {
            FileName = PreviousPath[str_size] + FileName;
            str_size--;
        }

        int input_size = PreviousPath.length();

        if (PreviousPath[input_size - 1] == 'g' || PreviousPath[input_size - 1] == 'f' || PreviousPath[input_size - 1] == 'p')
        {
            img = imread(PreviousPath);

        }
        else
        {

            fstream File;
            File.open(PreviousPath, ios::in);

            if (File.is_open())
            {
                while (getline(File, TextInLine))
                {
                    TextInFile += TextInLine;
                    TextInFile += "\n";

                }

                File.close();



            }
        }


        NewPath = CopyToFolder(Machine_ID_to, TextInFile, img, FileName);

        return NewPath;


    }

    void DeleteFile(long long int Machine_ID)
    {
        long long int Hashvalue;
        cout << "Enter The Hash Of File: ";
        cin >> Hashvalue;

        CircularNode* mover = Currently_at(Machine_ID);

        Machine* Responsible = Find_Responsible_Machine(mover, Hashvalue, Machine_ID);

        File temp(Hashvalue, "");

        int* ptr = new int;
        *ptr = 0;

        search(temp, Responsible->root, ptr);

        if (*ptr == 0 || ptr == NULL)
        {
            cout << "File Not Found!" << endl;
            return;
        }
        string Path = searchfile(Machine_ID, Hashvalue);

        int input_size = 0;
        char input_path[100];
        int size = 0;
        int num_paths = 0;

        for (int i = 0; Path[i] != '\0'; i++)
        {
            if (Path[i] == '\n')
                num_paths++;
        }

        if (num_paths == 0)
        {
            cout << "Error! File Not Found!" << endl;
            return;
        }

        while (num_paths > 0)
        {
            for (int i = 0; i < 100; i++)
            {
                input_path[i] = '\0';
            }

            num_paths--;
            input_size = 0;
            int j = 0;

            for (int i = size; Path[i] != '\n'; i++)
            {
                input_size++;
                input_path[j] = Path[i];
                size++;
                j++;
            }

            input_path[size] = '\0';
            size++;

            string s = input_path;

            cout << "File with Path: " << input_path << " removed!" << endl;

            remove(s.c_str());

            Responsible->root = del(temp, Responsible->root);


        }

    }

    void ViewFile(string paths)
    {
        Mat img;
        int input_size = 0;
        string TextInFile;
        string TextInLine;
        string Hash_Phase1;
        int Hash = 0;

        char input_path[100];
        int size = 0;

        int num_paths = 0;

        for (int i = 0; paths[i] != '\0'; i++)
        {
            if (paths[i] == '\n')
                num_paths++;
        }

        if (num_paths == 0)
        {
            cout << "Error! File Not Found!" << endl;
            return;
        }



        while (num_paths > 0)
        {
            for (int i = 0; i < 100; i++)
            {
                input_path[i] = '\0';
            }
            TextInFile = "";
            num_paths--;
            input_size = 0;
            int j = 0;

            for (int i = size; paths[i] != '\n'; i++)
            {
                input_size++;
                input_path[j] = paths[i];
                size++;
                j++;
            }

            input_path[size] = '\0';
            size++;



            if (input_path[input_size - 1] == 'g' || input_path[input_size - 1] == 'f' || input_path[input_size - 1] == 'p')
            {
                cout << input_path << endl;
                img = imread(input_path);
                Mat imgresize;
                resize(img, imgresize, imgresize.size(), 0.5, 0.5);
                imshow("IMAGE", imgresize);
                waitKey(0);
                system("CLS");
            }

            else
            {

                fstream File;
                File.open(input_path, ios::in);

                if (File.is_open())
                {
                    while (getline(File, TextInLine))
                    {
                        TextInFile += TextInLine;
                        TextInFile += "\n";

                    }

                    File.close();

                    cout << TextInFile << endl;

                }


            }

        }
    }

    string searchfile(long long int Machine_ID, long long int Hashvalue)
    {

        CircularNode* mover = Currently_at(Machine_ID);

        Machine* Responsible = Find_Responsible_Machine(mover, Hashvalue, Machine_ID);

        string Path;

        getPath(Responsible->root, Hashvalue, Path);

        return Path;

    }

    void DisplayFile(long long int Machine_ID)
    {
        long long int Hashvalue;
        cout << "Enter The Hash Of File: ";
        cin >> Hashvalue;

        string Path = searchfile(Machine_ID, Hashvalue);

        ViewFile(Path);
    }

    void PrintRoutingTable(CircularNode* mover) {
        do
        {
            cout << "Routing Table of ID # " << mover->ID << " is: " << endl;
            mover->DisplayRoutingTable();
            cout << endl;

            mover = mover->next;

        } while (mover != Hosts.head);
    }

    void TurnMachineOff(long long int Machine_ID)
    {
        long long int Remove_ID;
        cout << "Enter The Machine ID to Turn Off: ";
        cin >> Remove_ID;

        if (Remove_ID == Machine_ID)
        {
            cout << "Invalid ID! Machine Is Currently Being Used!" << endl;
            return;
        }

        if (activated_machines.search(Remove_ID) == false)
        {
            cout << "Invalid ID! Machine Is Already Turned Off!" << endl;
            return;
        }

        CircularNode* mover = Currently_at(Remove_ID);

        long long int prev_ID = Previous_Machine_ID(mover, mover->ID);
        long long int i;
        long long int temp;
        if (prev_ID <= Remove_ID) {
            temp = prev_ID;
        }
        else if (prev_ID > Remove_ID) {
            temp = total_machines - prev_ID;
            for (int j = 0; j <= Remove_ID; j++) {
                temp++;
            }
        }
        long long int n;
        //I have to understand why Prev+1 is used in this code
        for (i = prev_ID + 1, n = 0; n <= temp; n++, i++)
        {
            if (i > total_machines) {
                i = 0;
            }
            int* ptr = new int;
            *ptr = 0;
            File temp(i, "");

            search(temp, mover->M.root, ptr);

            if (*ptr == 0 || ptr == NULL)
            {

                continue;
            }

            string path;
            getPath(mover->M.root, i, path);



            int input_size = 0;
            char input_path[100];
            int size = 0;
            int num_paths = 0;

            for (int i = 0; path[i] != '\0'; i++)
            {
                if (path[i] == '\n')
                    num_paths++;
            }

            while (num_paths > 0)
            {
                for (int i = 0; i < 100; i++)
                {
                    input_path[i] = '\0';
                }

                num_paths--;
                input_size = 0;
                int j = 0;

                for (int i = size; path[i] != '\n'; i++)
                {
                    input_size++;
                    input_path[j] = path[i];
                    size++;
                    j++;
                }

                input_path[size] = '\0';
                size++;


                string prevPath = input_path;




                string s = MoveFile(mover->next->ID, prevPath);

                if (s == "ERROR")
                    return;

                File Add(i, s);

                mover->next->M.root = insert(Add, mover->next->M.root);

                mover->M.root = del(Add, mover->M.root);
                remove(prevPath.c_str());

                // cout << "File with Path: " << input_path << " removed!" << endl;

            }



        }


        //display(mover->next->M.root);

        Hosts.deleteData(Remove_ID);
        activated_machines.remove(Remove_ID);
        num_activated_machines--;

        ClearRoutingTable();
        SetRoutingTable();




    }

    void TurnMachineOn(long long int Machine_ID)
    {
        long long int Add_ID;
        long long int Next_ID;

        cout << "Enter The Machine ID to Turn On: ";
        cin >> Add_ID;

        Next_ID = Add_ID;

        if (Add_ID < 0 || Add_ID >= total_machines)
        {
            cout << "Error - Invalid ID!" << endl;
            return;
        }

        if (activated_machines.search(Add_ID) == true)
        {
            cout << "Invalid ID! Machine Is Already Turned On!" << endl;
            return;
        }

        else
        {
            while (activated_machines.search(Next_ID) == false)
            {
                Next_ID++;

                Next_ID = Next_ID % total_machines;
            }
        }

        Insert_Machine(Add_ID);

        //Hosts.insert(Add_ID);
        //activated_machines.insert(Add_ID);
        //num_activated_machines++;

        ClearRoutingTable();
        SetRoutingTable();


        CircularNode* mover = Currently_at(Next_ID);
        CircularNode* Place_In = Currently_at(Add_ID);

        if (Next_ID > Add_ID)
        {
            for (int i = 0; i <= Add_ID; i++)
            {
                int* ptr = new int;
                *ptr = 0;
                File temp(i, "");

                search(temp, mover->M.root, ptr);

                if (*ptr == 0 || ptr == NULL)
                {
                    continue;
                }


                string path;
                getPath(mover->M.root, i, path);



                int input_size = 0;
                char input_path[100];
                int size = 0;
                int num_paths = 0;

                for (int i = 0; path[i] != '\0'; i++)
                {
                    if (path[i] == '\n')
                        num_paths++;
                }

                while (num_paths > 0)
                {
                    for (int i = 0; i < 100; i++)
                    {
                        input_path[i] = '\0';
                    }

                    num_paths--;
                    input_size = 0;
                    int j = 0;

                    for (int i = size; path[i] != '\n'; i++)
                    {
                        input_size++;
                        input_path[j] = path[i];
                        size++;
                        j++;
                    }

                    input_path[size] = '\0';
                    size++;


                    string prevPath = input_path;




                    string s = MoveFile(Add_ID, prevPath);

                    if (s == "ERROR")
                        return;

                    File Add(i, s);

                    Place_In->M.root = insert(Add, Place_In->M.root);

                    mover->M.root = del(Add, mover->M.root);
                    remove(prevPath.c_str());

                    // cout << "File with Path: " << input_path << " removed!" << endl;

                }


            }
        }

        else
        {
            for (int i = Next_ID + 1; i <= Add_ID; i++)
            {
                int* ptr = new int;
                *ptr = 0;
                File temp(i, "");

                search(temp, mover->M.root, ptr);

                if (*ptr == 0 || ptr == NULL)
                {
                    continue;
                }


                string path;
                getPath(mover->M.root, i, path);



                int input_size = 0;
                char input_path[100];
                int size = 0;
                int num_paths = 0;

                for (int i = 0; path[i] != '\0'; i++)
                {
                    if (path[i] == '\n')
                        num_paths++;
                }

                while (num_paths > 0)
                {
                    for (int i = 0; i < 100; i++)
                    {
                        input_path[i] = '\0';
                    }

                    num_paths--;
                    input_size = 0;
                    int j = 0;

                    for (int i = size; path[i] != '\n'; i++)
                    {
                        input_size++;
                        input_path[j] = path[i];
                        size++;
                        j++;
                    }

                    input_path[size] = '\0';
                    size++;


                    string prevPath = input_path;




                    string s = MoveFile(Add_ID, prevPath);

                    if (s == "ERROR")
                        return;

                    File Add(i, s);

                    Place_In->M.root = insert(Add, Place_In->M.root);

                    mover->M.root = del(Add, mover->M.root);
                    remove(prevPath.c_str());

                    // cout << "File with Path: " << input_path << " removed!" << endl;

                }


            }
        }




    }

    void PrintBTree()
    {
        long long int ID;
        cout << "Enter The Machine ID To Print B-Tree: ";
        cin >> ID;

        CircularNode* mover = Currently_at(ID);

        display(mover->M.root);
        cout << endl;
    }

    void MENU(int Machine_ID)
    {
        int selection = 1;

        while (selection != -1)
        {
            system("CLS");


            cout << "Working On Machine With ID: " << Machine_ID << endl << endl;

            cout << "Press 1 To Insert A File" << endl;
            cout << "Press 2 To Delete A File" << endl;
            cout << "Press 3 To Display A File" << endl;
            cout << "Press 4 To Turn Off A Machine" << endl;
            cout << "Press 5 To Turn On A Machine" << endl;
            cout << "Press 6 To Display Routing Table" << endl;
            cout << "Press 7 To Display B-Tree" << endl;

            cout << endl << "Enter Command: ";
            cin >> selection;

            if (selection > 7 || selection < -1)
            {
                cout << "Incorrect Option!" << endl;
                selection = 1;
                continue;
            }

            CircularNode* mover = Hosts.head;


            switch (selection)
            {

            case 1:
                InsertFile(Machine_ID);
                break;

            case 2:
                DeleteFile(Machine_ID);
                break;

            case 3:
                DisplayFile(Machine_ID);
                break;

            case 4:
                TurnMachineOff(Machine_ID);
                break;

            case 5:
                TurnMachineOn(Machine_ID);
                break;

            case 6:
                PrintRoutingTable(mover);
                break;

            case 7:
                PrintBTree();
                break;

            case -1:
                cout << "Closing IPFS!" << endl;
                return;

            default:
                cout << "Incorrect Option!" << endl;
                selection = 1;

            }


            cout << "Press Any Key to Continue! ";
            _getch();

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


        cout << "\n";
        cout << "\n";

        cout << "                            _    _                       ______                            ___  ___  _         ___   ___   ___ __         " << endl;
        cout << "                           | |  | |                     |  ____|                          |__ \\|__ \\(_)       / _ \\ / _ \\ / _ /_ |        " << endl;
        cout << "                           | |  | |_ __ ___   ___ _ __  | |__ __ _ _ __ ___   ___   __ _     ) |  ) |_ ______| | | | (_) | (_) | |        " << endl;
        cout << "                           | |  | | '_ ` _ \\ / _ | '__| |  __/ _` | '__/ _ \\ / _ \\ / _` |   / /  / /| |______| | | |> _ < \\__, | |        " << endl;
        cout << "                           | |__| | | | | | |  __| |    | | | (_| | | | (_) | (_) | (_| |  / /_ / /_| |      | |_| | (_) |  / /| |        " << endl;
        cout << "                            \\____/|_| |_| |_|\\___|_|    |_|  \\__,_|_|  \\___/ \\___/ \\__, | |____|____|_|       \\___/ \\___/  /_/ |_|        " << endl;
        cout << "                                                                                      | |                                                 " << endl;
        cout << "                                                                                      |_|                                                 " << endl;

        cout << "\n";
        cout << "\n";
        cout << "                    _    _                     _        __          __                             ___  ___  _         ___   ___   ___ ____        " << endl;
        cout << "                   | |  | |                   (_)       \\ \\        / /                            |__ \\|__ \\(_)       / _ \\ / _ \\ / _ |___ \\       " << endl;
        cout << "                   | |__| |_   _ ___ ___  __ _ _ _ __    \\ \\  /\\  / __ _ ___  ___  ___ _ __ ___      ) |  ) |_ ______| | | | (_) | (_) |__) |      " << endl;
        cout << "                   |  __  | | | / __/ __|/ _` | | '_ \\    \\ \\/  \\/ / _` / __|/ _ \\/ _ | '_ ` _ \\    / /  / /| |______| | | |> _ < \\__, |__ <       " << endl;
        cout << "                   | |  | | |_| \\__ \\__ | (_| | | | | |    \\  /\\  | (_| \\__ |  __|  __| | | | | |  / /_ / /_| |      | |_| | (_) |  / /___) |      " << endl;
        cout << "                   |_|  |_|\\__,_|___|___/\\__,_|_|_| |_|     \\/  \\/ \\__,_|___/\\___|\\___|_| |_| |_| |____|____|_|       \\___/ \\___/  /_/|____/       " << endl;

        cout << "\n";
        cout << "\n";
        cout << "\n";
        cout << "\n";


        cout << "                                 _____      _                   _  ___                   ___  ___  _         ___   ___ __ __         " << endl;
        cout << "                                |_   _|    | |                 | |/ | |                 |__ \\|__ \\(_)       / _ \\ / _ /_ /_ |        " << endl;
        cout << "                                  | |  _ __| |_ __ _ ______ _  | ' /| |__   __ _ _ __      ) |  ) |_ ______| | | | (_) | || |        " << endl;
        cout << "                                  | | | '__| __/ _` |_  / _` | |  < | '_ \\ / _` | '_ \\    / /  / /| |______| | | |\\__, | || |        " << endl;
        cout << "                                 _| |_| |  | || (_| |/ | (_| | | . \\| | | | (_| | | | |  / /_ / /_| |      | |_| |  / /| || |        " << endl;
        cout << "                                |_____|_|   \\__\\__,_/___\\__,_| |_|\\_|_| |_|\\__,_|_| |_| |____|____|_|       \\___/  /_/ |_||_|        " << endl;



        bits = _getch();
        system("CLS");





        cout << "       _____       _            _____  _                  _                     ______ _ _         _____           _                 " << endl;
        cout << "      |_   _|     | |          |  __ \\| |                | |                   |  ____(_) |       / ____|         | |                " << endl;
        cout << "        | |  _ __ | |_ ___ _ __| |__) | | __ _ _ __   ___| |_ __ _ _ __ _   _  | |__   _| | ___  | (___  _   _ ___| |_ ___ _ __ ___  " << endl;
        cout << "        | | | '_ \\| __/ _ \\ '__|  ___/| |/ _` | '_ \\ / _ \\ __/ _` | '__| | | | |  __| | | |/ _ \\  \\___ \\| | | / __| __/ _ \\ '_ ` _ \\ " << endl;
        cout << "       _| |_| | | | ||  __/ |  | |    | | (_| | | | |  __/ || (_| | |  | |_| | | |    | | |  __/  ____) | |_| \\__ \\ ||  __/ | | | | |" << endl;
        cout << "      |_____|_| |_|\\__\\___|_|  |_|    |_|\\__,_|_| |_|\\___|\\__\\__,_|_|   \\__, | |_|    |_|_|\\___| |_____/ \\__, |___/\\__\\___|_| |_| |_|" << endl;
        cout << "                                                                         __/ |                            __/ |                      " << endl;
        cout << "                                                                        |___/                            |___/                       " << endl;










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
        long long int Machine_ID = 0;
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

        cout << "       _____       _            _____  _                  _                     ______ _ _         _____           _                 " << endl;
        cout << "      |_   _|     | |          |  __ \\| |                | |                   |  ____(_) |       / ____|         | |                " << endl;
        cout << "        | |  _ __ | |_ ___ _ __| |__) | | __ _ _ __   ___| |_ __ _ _ __ _   _  | |__   _| | ___  | (___  _   _ ___| |_ ___ _ __ ___  " << endl;
        cout << "        | | | '_ \\| __/ _ \\ '__|  ___/| |/ _` | '_ \\ / _ \\ __/ _` | '__| | | | |  __| | | |/ _ \\  \\___ \\| | | / __| __/ _ \\ '_ ` _ \\ " << endl;
        cout << "       _| |_| | | | ||  __/ |  | |    | | (_| | | | |  __/ || (_| | |  | |_| | | |    | | |  __/  ____) | |_| \\__ \\ ||  __/ | | | | |" << endl;
        cout << "      |_____|_| |_|\\__\\___|_|  |_|    |_|\\__,_|_| |_|\\___|\\__\\__,_|_|   \\__, | |_|    |_|_|\\___| |_____/ \\__, |___/\\__\\___|_| |_| |_|" << endl;
        cout << "                                                                         __/ |                            __/ |                      " << endl;
        cout << "                                                                        |___/                            |___/                       " << endl;


        MENU(User_ID);




        cout << endl << endl << "Press Any Key To Continue: ";
        _getch();
        system("CLS");
    }

};


int main()
{


    IPFS check;

    check.Start();




    /*
        BigInt I("1234567891012121212121999");
        BigInt J;

        J = I;
        cout << J<<endl;
        J++;

        cout << J << endl;

        --J;
        cout << J << endl;

        return 0;

        */
}
