#include<iostream>
#include<stack>
#include<queue>
#include<omp.h>
using namespace std;

class TreeNode
{
  public:
          TreeNode* left;
          TreeNode* right;
          int data;
          
          TreeNode(int x)
          {
            data = x;
            left = right = NULL;
          }
};
class Tree
{
  public:
          TreeNode* root;
          Tree()
          {
            root = NULL;
          }
          TreeNode* find(TreeNode* root,int val)
          {
            if(!root) return NULL;
            if(root -> data == val) return root;
            TreeNode* left = find(root -> left,val);
            if(left) return left;
            return find(root->right,val);
          }
          void insert(TreeNode* parent,int value,char direction)
          {
            TreeNode* n=new TreeNode(value);
            if(!parent)
            {
              cout<<"Parent Not found\n";
              delete n;
              return;
            }
            if(direction == 'L')
            {
              if(!parent->left)
                parent->left = n;
              else
                cout<<"\n Left child already exists";
            }
            else if(direction == 'R')
            {
              if(!parent->right)
                parent->right = n;
              else
                cout<<"\n Right child already exists";
            }
            else
            {
              cout<<"\n Invalid Direction.Use L OR R";
              delete n;
            }   
          }
          
          void bfs()
          {
            if(!root)
              return;
              
            queue<TreeNode*> q;
            q.push(root);
            cout<<"\nParallel BFS : ";
            while(!q.empty())
            {
              int n = q.size();
              #pragma omp parallel for
              for(int i=0;i<n;i++)
              {
                  TreeNode* temp;
                  
                  #pragma omp critical
                  {
                      temp = q.front();
                      q.pop();
                      cout<<temp->data<<" | ";
                  }
                  #pragma omp critical
                  {
                      if(temp->left) q.push(temp->left);
                      if(temp->right) q.push(temp->right);
                  }
              }
            }
            cout<<endl;
          }
          void dfs()
          {
            if(!root)
              return;
            
            stack<TreeNode*> s;
            s.push(root);
            cout<<"\nParallel DFS : ";
            while(!s.empty())
            {
              int n = s.size();
              #pragma omp parallel for
              for(int i=0;i<n;i++)
              {
                TreeNode* temp;
                #pragma omp critical
                {
                  temp = s.top();
                  s.pop();
                  cout<<temp->data<<" | ";
                  
                  if(temp->right) s.push(temp->right);
                  if(temp->left) s.push(temp->left);
                }
              }
            }
            cout<<endl;
          }
};
int main()
{
    Tree *t = new Tree();
    int val;
    cout<<"\nEnter the root : ";
    cin>>val;
    t->root = new TreeNode(val);
    
    while(true)
    {
      int ch;
      cout<<"\nEnter 1.Insert 2.BFS 3.DFS 0.Exit : ";
      cin>>ch;
      if(ch == 1)
      {
        int pval;int nval;
        char dir;
        cout<<"\nEnter the parent value : ";
        cin>>pval;
        cout<<"\nEnter the Direction (L or R): ";
        cin>>dir;
        cout<<"\nEnter the new value : ";
        cin>>nval;
        
        TreeNode* parent = t->find(t->root,pval);
        t->insert(parent,nval,toupper(dir));
      }
      else if(ch == 2)
      {
        t->bfs();
      }
      else if(ch == 3)
      {
        t->dfs();
      }
      else if(ch == 0)
      {
        cout<<"\nExited Successfully";
        break;
      }
      else
      {
       cout<<"\nInvalid Input";
      }
    }
    return 0;
}




