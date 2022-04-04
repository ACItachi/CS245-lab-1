#include <bits/stdc++.h>
using namespace std;

class Bucket
{
public:
    int capacity;
    vector<int> data;
    int local_depth;
    int no_of_keys;

    Bucket(int capacity, int local_depth);
    void insert(int data);
    bool isFull();
    int search(int data);
};

Bucket::Bucket(int cap, int local_dep)
{

    capacity = cap;
    local_depth = local_dep;
    no_of_keys = 0;
    vector<int> temp_data(cap, 0);
    data = temp_data;
}

void Bucket::insert(int dat)
{

    if (isFull())
    {
        return;
    }
    data[no_of_keys] = dat;
    no_of_keys++;
}

bool Bucket::isFull()
{
    return (no_of_keys == capacity);
}
int Bucket::search(int dat)
{

    for (int i = 0; i < no_of_keys; i++)
    {
        if (data[i] == dat)
        {
            return i;
        }
    }
    return -1;
}
class Directory
{
public:
    Directory(int global_depth, int bucket_capacity);
    vector<Bucket *> dir;
    int global_depth;
    int bucket_capacity;

    bool isPresent(int data);
    void insert(int data);
    void delete_elem(int data);
    void print_bucket(int index);
    void display();
    void printDirectory();
};

Directory::Directory(int glob, int cap)
{
    global_depth = glob;
    bucket_capacity = cap;

    int sz = (1 << glob);
    vector<Bucket *> temp_dir(sz, nullptr);
    dir = temp_dir;

    for (int i = 0; i < sz; i++)
    {
        auto b = new Bucket(cap, global_depth);
        dir[i] = b;
    }
}

void Directory::insert(int dat)
{
    if(global_depth==20){
        return;
    }
    int sz = (1 << global_depth);
    int index = dat % sz;
    if (dir[index]->isFull())
    {
        if((dir[index]->local_depth) == global_depth){

            vector <Bucket*> temp_dir(2*sz);

            for(int i = 0;i<sz;i++){
                temp_dir[i] = dir[i];
                
                temp_dir[i+sz] = dir[i];

            }
            dir = temp_dir;
            global_depth++;
            insert(dat);

        }
        else{
            vector <int> curvalues;
            for(auto x: dir[index]->data){
                curvalues.push_back(x);
            }
            curvalues.push_back(dat);
            for(auto x: dir[index]->data){
                (dir[index]->data).assign((dir[index]->capacity),0);
            }
            dir[index]->no_of_keys = 0;
            dir[index]->local_depth ++;
            dir[index] = new Bucket(bucket_capacity,dir[index]->local_depth);

            for(auto x: curvalues){
                insert(x);
            }

        }
    }
    else
    {
        dir[index]->insert(dat);
    }
}
void Directory::print_bucket(int index)
{

    for (int i = 0; i < dir[index]->no_of_keys; i++)
    {
        cout << (dir[index]->data)[i] << " ";
    }
    cout << endl;
}

bool Directory::isPresent(int dat)
{
    bool yes = 0;
    int sz = (1 << global_depth);
    yes = ((dir[dat % sz]->search(dat)) != -1) ? 1 : 0;

    return yes;
}

void Directory::delete_elem(int dat)
{
    if (isPresent(dat))
    {
        int sz = (1 << global_depth);
        int ind = dir[dat % sz]->search(dat);

        auto it = (dir[dat%sz]->data).begin() + ind;

        (dir[dat%sz]->data).erase(it);
        dir[dat%sz]->no_of_keys--;
        dir[dat%sz]->data.push_back(0);

    }
}

void Directory::display(){
    int noofbuckets = 0;
    int directory_size = (1<<global_depth);
    cout << "Global Depth "<<global_depth<<endl;

    set <Bucket*> s;
    for(auto x: dir){
        s.insert(x);
    }
    cout << "No of Buckets "<<s.size()<<endl;
    for(int i=0; i<s.size(); i++){
        cout<<dir[i]->no_of_keys<<" "<<dir[i]->local_depth<<endl;
    }

}
void Directory::printDirectory(){
    display();

    int sz = (1<<global_depth);
    // for(int i = 0;i<sz;i++){
    //     for(int j = 0;j<dir[i]->no_of_keys;j++){
    //         cout << dir[i]->data[j]<<" ";
    //     }
    //     cout << endl;
    // }
}

int main()
{
    int gd, bc;
    cin>>gd;
    cin>>bc;
    Directory d(gd,bc);
    int f, val;
    while(1){
        cin>>f;
        if(f<5){
            cin>>val;
        }
        if(f==2) d.insert(val);
        else if(f==3) {
            if(d.isPresent(val)) cout<<"Yes"<<endl;
            else cout<<"No"<<endl;
        }
        else if(f==4) d.delete_elem(val);
        else if(f==5) d.display();
        else if(f==6) break;
    }
    
    return 0;
}