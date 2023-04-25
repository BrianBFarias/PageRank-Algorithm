#include <iostream>
#include <map>
#include <set>
#include<iterator>
#include <iomanip>

using namespace std;

class AdjacencyList {
    map<string, set<string> > Graph; //(in_degree)
    map<string, float > Rank ; //(page_rank)
    map<string, float> d; //(out_degree)

public:
    void initialPagerank();
    AdjacencyList();
    void insert (string from, string to);
    map<string, float > PageRank(int n);
};
//constructor
AdjacencyList::AdjacencyList(){
}

//inserting new page connections
void AdjacencyList::insert(string from, string to) {
    Graph[to].insert(from);
    d[from]+=1;

    if (Graph.find (from) == Graph.end()){
        Graph[from] = {};
    }
}

//setting initial page rank which is 1/V aka r(0)
void AdjacencyList::initialPagerank() {
    float V = Graph.size();
    auto itr = Graph.begin();
    for(int i =0; i < Graph.size(); i++){
        Rank[itr->first] = (1/V);
        itr++;
    }
}

//taking iteration power and finding final Rank
map<string, float > AdjacencyList::PageRank(int n){
    map<string, float > Multiplie = Rank;

    if (n == 1){
        return Rank;
    }
    // if n > 1 execute matrix multiplication
    else if(n > 1){
        for(auto & itr : Graph){
            double rank = 0;
            float value = 0;
            auto pageSet= Graph[itr.first];
            auto pages = pageSet.begin();
            while(pages != pageSet.end()){
                value = (1/d[*pages]);
                rank += Multiplie[*pages] * value;
                pages++;
            }
            Rank[itr.first] = rank;
        }
    }
    //loop matrix multiplication until (n-1)=1
    return PageRank((n-1));
}

int main()
{
    map<string, float > FinalRank;
    AdjacencyList PageGraph;
    int no_of_lines, power_iterations;
    string from, to;
    cin >> no_of_lines;
    cin >> power_iterations;

    for(int i = 0;i < no_of_lines; i++){
        cin >> from;
        cin >> to;

        PageGraph.insert(from, to);
    }

    PageGraph.initialPagerank();
    FinalRank = PageGraph.PageRank(power_iterations);

    auto itr = FinalRank.begin();
    while(itr != FinalRank.end()){

        cout<<itr->first << " ";
        //precision sets to 2 decimal places
        cout<< fixed << setprecision(2) << itr->second << endl;
        itr++;
    }
}
