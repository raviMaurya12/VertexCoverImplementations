//program to find minimal vertex covers for a given graph
#include<bits/stdc++.h>
using namespace std;

 //enter dimension of edjacency matrix of graph
void vertex_cover(int,int*); //prototype for vertex_cover

int dim;

int main()
{
// clrscr();
cout<<"Enter the graph in Adjacency Matrix format\n";
 //enter input as graph adjacency matrix

cin>>dim;
int i,j,*p,arr[dim][dim];

for(i=0;i<dim;i++)
 {
 for(j=0;j<dim;j++)
 cin>>arr[i][j];
 cout<<"\n";
 }
p=&arr[0][0];
for(i=0;i<dim;i++)
vertex_cover(i,p);
// getch();

char a_dumm;
cout<<"\nPress any alphabet and then press enter to exit."<<endl;
cin>>a_dumm;

return 0;
}//end of main
void vertex_cover(int v,int *q)
 //this function produces several different vertex covers
{
int a[dim][dim],count,max=0,flag,x=0,i,j;
int degree[dim],vertices_maxdegree[dim],vc[dim],l=0,r;
for(i=0;i<dim;i++)
 {
 for(j=0;j<dim;j++)
 {
 a[i][j]=*q;
 q++;
 }
 }
//remove the incident edges of correspanding vertex
for(j=0;j<dim;j++)
 {
 if(a[v][j]==1)
 {
 a[v][j]=0;
 a[j][v]=0;
 }
 }
//until all edges are removed
while(1)
{
int k=0,flag=0;
// 44
//
for(i=0;i<dim;i++)
 {
 count=0;
 for(j=0;j<dim;j++)
 {
 if(a[i][j]==1)
 {
 flag++;
 count++;
 }
 }
 degree[i]=count;
 }
//if all edges are removed then stop
if(flag==0)
break;
//find maximum degree
max=degree[0];
for(i=1;i<dim;i++)
 {
 if(max<degree[i])
 max=degree[i];
 }
//find vertices of maximum degree
for(i=0;i<dim;i++)
 {
 if(max==degree[i])
 vertices_maxdegree[k++]=i;
 }
/*Choose that vertex which has at least one edge that is not covered by others
 which have maximum number of edges.
 Otherwise choose an arbitary edge.*/
for(i=0;i<k;i++)
 {
 x=0;
 for(j=0;j<dim;j++)
 {
 if(a[vertices_maxdegree[i]][j]==1)
 {
 for(r=0;r<k;r++)
 {
 if(j==vertices_maxdegree[r])
 x++;
 }
 }
 }
 if(x<max)
 break;
 }
if(i==k)
i=0;
vc[l++]=vertices_maxdegree[i];
//remove the incident edges of selected vertex
// 45
for(j=0;j<dim;j++)
 {
 if(a[vertices_maxdegree[i]][j]==1)
 {
 a[vertices_maxdegree[i]][j]=0;
 a[j][vertices_maxdegree[i]]=0;
 }
 }
}//end of while
vc[l++]=v;
//it prints the vertex cover
cout<<"\n Vertex Cover of v="<<v+1;
cout<<" {";
for(i=0;i<l;i++)
 {
 cout<<" "<<vc[i]+1;
 }
cout<<"}";
}//end of vertex_cover