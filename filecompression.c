#include <stdio.h>
#include <stdlib.h>
struct heapnode{
    char ch;
    int frequency;
    struct heapnode * left, * right;
};
//creating a normal minheap but here we are storing the nodes of the huffamn tree instead of numbers and we make this min terminology on the basis of the frequency
//means least frequency node will occupy the root node
struct heap{
    int capacity;
    int size;
    struct heapnode ** arr;
};
struct heap * cre(char data[],int frequency[],int s);
struct heapnode * new(char c,int freq);
void hepify(struct heap * h,int index);
struct heapnode * delete(struct heap * h);
//inserting into heap means what? we will insert a newnode into the heap right as heap is storing nodes
void insert(struct heap * h,struct heapnode * newnode);
//into the heap h we are inserting a newnode i.e newnode;
void inserthelp(struct heap * h,int index);
struct heapnode * huffman(struct heap * h);
int onlyone(struct heap * h);
void print(struct heapnode * root, int a[],int top);
int leafnode(struct heapnode * root);
void printcodes(int a[],int top);
int main(){
    char arr[] = {'a','b','c','d','e','f'};
    //a,b,c,d,ei
    //5,3,6,4,2
    int frequency[] = {5,9,12,13,16,45};
    int s = sizeof(arr)/sizeof(arr[0]);
    //just creating min heap according to the frequencies and in each index we have heapnodes having attributes character, frequency, left, right pointer
    struct heap * h = cre(arr,frequency,s);
    //building huffman tree we just return root node after the application of huffman algoritham like extracting 2 smallest of frequencies and inserting the sum frequency into heap and doing so on until only one node i.e root node is left
    struct heapnode * root = huffman(h);
    //a is used to store the codes 
    int top = 0;
    int a[100];
    print(root,a,top);
}
struct heapnode * new(char c,int freq){
    struct heapnode * newnode;
    newnode = (struct heapnode *)malloc(sizeof(struct heapnode));
    newnode->left = newnode->right = NULL;
    newnode->ch = c;
    newnode->frequency = freq;
    return newnode;
}
struct heap * cre(char data[],int frequency[],int s){
    struct heap * h;
    h = (struct heap *)malloc(sizeof(struct heap));
    h->capacity = s;
    h->size = 0;
    h->arr = (struct heapnode**)malloc(h->capacity*sizeof(struct heapnode*));
    int i;
    for(i=0;i<s;i=i+1){
        //in every index of minheap we are storing nodes returned by this new function
        h->arr[i] = new(data[i],frequency[i]);
    }
    //s or i as now s will be equal to i
    h->size = i;
    //finding the last parent index in heap array by this from this we are going to hepify;
    int j = (h->size - 2)/2;
    while(j>=0){
        hepify(h,j);
        j=j-1;
    }
    //in minheap we storing nodes instead of numbers we did before
    //we created a minheap with all nodes in which we store data i.e character and frequency of the character
    return h;
}
void hepify(struct heap * h,int index){
    //assuming min frequency node is present in this index i.e last parent
    int min = index;
    //l means left child of the parent, r means right child of the parent
    int l = 2*index+1;
    int r = 2*index+2;
    if(l >= h->size || l < 0){
        //means for given parent left child doesnt exist so we made it -1;
        l = -1;
    }
    if(r >= h->size || r < 0){
        r = -1;
    }
    //h->arr[i] means in heap there is array in them in each index we stored node of the which store character, frequency
    //h->arr[i] means its a structure of heapnode it has all 4 attributes char,freq,left,right
    if(l!=-1 && h->arr[l]->frequency < h->arr[min]->frequency){
        min = l;
    }
    if(r!=-1 && h->arr[r]->frequency < h->arr[min]->frequency){
        min = r;
    }
    if(index!=min){
        struct heapnode * temp = h->arr[min];
        h->arr[min] = h->arr[index];
        h->arr[index] = temp;
        //we doing again hepification at min now it will considered as parent may have nodes of frequencys less than that min index
        hepify(h,min);
    }
}
struct heapnode * delete(struct heap * h){
    //storing the deleted i.e first node i.e h->arr[0] in temp heapnode object here it is p;
    struct heapnode * p = h->arr[0];
    h->arr[0] = h->arr[h->size-1];
    h->size = h->size-1;
    //as now last node in the tree has shifted to 0th index 
    //now hepify from this root node;
    hepify(h,0);
    return p;
}
void insert(struct heap * h,struct heapnode *newnode){
    if(h->size < h->capacity){
    // 10 20 30 40 are elements in heap and correspoinding index are 0 1 2 3 and no.of elements are 4 i.e size of heap so we used h->arr[h->size]
    h->arr[h->size] = newnode;
    inserthelp(h,h->size);
    //as one element is inserted now size will increase right;
    h->size = h->size+1;
    }
}
void inserthelp(struct heap * h,int index){
    //now we inserted at h->size i.e index (as parameter) the parent of this is given by (index-1)/2;
    int parent = (index-1)/2;
    if(parent >=0 && h->arr[parent] > h->arr[index]){
        struct heapnode * temp = h->arr[index];
        h->arr[index] = h->arr[parent];
        h->arr[parent] = temp;
        inserthelp(h,parent);
    }
}
int onlyone(struct heap * h){
    if(h->size==1){
        //no.of elements in heap is only one then return one;
        return 1;
    }
    return 0;
}
struct heapnode * huffman(struct heap * h){
    struct heapnode * newnode,* left,* right;
    while(!onlyone(h)){
        left = delete(h);
        right = delete(h);
        //creating newnode of frequency of sum of 2 smallest frequency from the heap
        //that symbol doesn't matter just taken an arbitary character
        newnode = new('#',left->frequency + right->frequency);
        //after creating newnode linking that newnode with node left to smallest frequency i.e 1st deleted i.e left heapnode
        //then linking that node with newnode with node right to second smallest frequency i.e 2nd deleted; 
        newnode->left = left;
        newnode->right = right;
        insert(h,newnode);
    }
    //now only one node is left in the heap i.e root node but it is linked by obeying all properties returning that node
    struct heapnode * p = delete(h);
    return p;
}
void print(struct heapnode * root,int a[],int top){
    //for left side we put all 0's
    if(root->left!=NULL){
        a[top] = 0;
        print(root->left,a,top+1);
    }
    //for right side of tree we put all 1's
    if(root->right!=NULL){
        a[top] = 1;
        print(root->right,a,top+1);
    }
    if(leafnode(root)){
        printf("%c = ",root->ch);
        printcodes(a,top);
    }
}
int leafnode(struct heapnode * root){
    if(root->left == NULL && root->right == NULL){
        return 1;
    }
    return 0;
}
void printcodes(int a[],int top){
    for(int i=0;i<top;i=i+1){
        printf("%d ",a[i]);
    }
    printf("\n");
}