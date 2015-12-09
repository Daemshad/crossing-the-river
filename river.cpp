#include <iostream>
#include <string>
#include <stack>
#include <iomanip>
using namespace std;

/* - - - - - - - - - | River class | - - - - - - - - -*/

class river {
    
private:
    
    /* - Index Variables - */
    int B = 0;
    int F = 1;
    int M = 2;
    int P = 3;
    int S1 = 4;
    int S2 = 5;
    int D1 = 6;
    int D2 = 7;
    int T = 8;
    
    /* - Main Variables - */
    int aux;                     // pointer used in DFS algorythm
    string state = "000000000";  // 0 shows downside 1 shows upside
    string parent = "000000000";
    
    /* - Main Functions - */
    void doswitch(int);          // switches only one element from 0 to 1 or 1 to 0
    bool isvalid();              // validates each state
    bool isgoal();               // checks if current state is goal state or not
    void expand();               // expands children of each state
    bool visited();                //checks if a state is visited in ex or not
    void print_solution();         // prints the solution
    void return_names(int);      // returns each indexes name
    
    /* - Operations - */
    // checks if Boat and the passengers are at same side moves them
    void move_F();     // moves Father
    void move_M();     // moves Mother
    void move_P();     // moves Police
    void move_F_M();   // moves Father and Mother
    void move_F_P();   // moves Father and Police
    void move_M_P();   // moves Mother and Police
    void move_P_T();   // moves Police and Thief
    void move_P_S1();  // moves Police and First Son
    void move_P_S2();  // moves Police and Second Son
    void move_P_D1();  // moves Police and First Daughter
    void move_P_D2();  // moves Police and Second Daughter
    void move_F_S1();  // moves Father and First Son
    void move_F_S2();  // moves Father and Second Son
    void move_M_D1();  // moves Mother and First Daughter
    void move_M_D2();  // moves Mother and Second Daughter
    
    /* - Stacks - */
    stack<string> un;            // stack used in DFS algorithm
    stack<string> un_parent;     // parallel stack used for store parents of un
    
    /* - Arrays - */
    string ex[1000];             // array used in DFS algorithm
    string ex_parent[1000];     // parallel array of parents of each ex member
    
    public :
    
    void DFS();      // Depth First Search Algorithm
    
};

/* - - - - - - - - - | Swich side | - - - - - - - - - */

void river::doswitch(int i){
    
    if (state[i] == '0')
        state[i] = '1';
    else if (state[i] == '1')
        state[i] = '0';
    
}

/* - - - - - - - - | Validation check | - - - - - - - */

bool river::isvalid(){
    
    if ((state[F]==state[D1] || state[F]==state[D2]) && state[F]!=state[M])
        return false; // Father should not be alone with daughters
    
    else if ((state[M]==state[S1] || state[M]==state[S2]) && state[F]!=state[M])
        return false; // Mother should not be alone with sons
    
    else if (state[P] != state[T]  && (
                                       state[T] == state[F] ||
                                       state[T] == state[M] ||
                                       state[T] == state[S1] ||
                                       state[T] == state [S2] ||
                                       state[T] == state[D1] ||
                                       state[T] == state[D2]))
        return false; // Thief should not be alone with anyone
    
    else
        return true;
    
}

/* - - - - - - - - - | Goal check | - - - - - - - - - */

bool river::isgoal(){
    
    if (state == "111111111")
        return true;
    else
        return false;
    
}

/* - - - - - - - - - | Operations | - - - - - - - - - */

void river::move_F (){
    
    if (state[B] == state[F]){
        doswitch(B);
        doswitch(F);
    }
}

void river::move_M(){
    
    if (state[B] == state[M]){
        doswitch(B);
        doswitch(M);
    }
}

void river::move_P(){
    
    if (state[B] == state[P]){
        doswitch(B);
        doswitch(P);
    }
}

void river::move_F_M(){
    
    if (state[B] == state[F] and state[F] == state[M]){
        doswitch(B);
        doswitch(F);
        doswitch(M);
    }
}

void river::move_F_P(){
    
    if (state[B] == state[F] and state[F] == state[P]){
        doswitch(B);
        doswitch(F);
        doswitch(P);
    }
}

void river::move_M_P(){
    
    if (state[B] == state[M] and state[M] == state[P]){
        doswitch(B);
        doswitch(M);
        doswitch(P);
    }
}

void river::move_P_T(){
    
    if (state[B] == state[P] and state[P] == state[T]){
        doswitch(B);
        doswitch(P);
        doswitch(T);
    }
}

void river::move_P_S1(){
    
    if (state[B] == state[P] and state[P] == state[S1]){
        doswitch(B);
        doswitch(P);
        doswitch(S1);
    }
}

void river::move_P_S2(){
    
    if (state[B] == state[P] and state[P] == state[S2]){
        doswitch(B);
        doswitch(P);
        doswitch(S2);
    }
}

void river::move_P_D1(){
    
    if (state[B] == state[P] and state[P] == state[D1]){
        doswitch(B);
        doswitch(P);
        doswitch(D1);
    }
}

void river::move_P_D2(){
    
    if (state[B] == state[P] and state[P] == state[D2]){
        doswitch(B);
        doswitch(P);
        doswitch(D2);
    }
}

void river::move_F_S1(){
    
    if (state[B] == state[F] and state[F] == state[S1]){
        doswitch(B);
        doswitch(F);
        doswitch(S1);
    }
}

void river::move_F_S2(){
    
    if (state[B] == state[F] and state[F] == state[S2]){
        doswitch(B);
        doswitch(F);
        doswitch(S2);
    }
}

void river::move_M_D1(){
    
    if (state[B] == state[M] and state[M] == state[D1]){
        doswitch(B);
        doswitch(M);
        doswitch(D1);
    }
}

void river::move_M_D2(){
    
    if (state[B] == state[M] and state[M] == state[D2]){
        doswitch(B);
        doswitch(M);
        doswitch(D2);
    }
}

/* - - - - - - - - - - | Expand | - - - - - - - - - - */

void river::expand(){
    
    /* this function does each operation and if it was valid
       pushes it and it's parent in stacks */
    
    move_F();
    if (isvalid()){
        un.push(state);
        move_F();
        un_parent.push(state);
    }
    else{
        move_F();
    }
    
    move_M();
    if (isvalid()){
        un.push(state);
        move_M();
        un_parent.push(state);
    }
    else{
        move_M();
    }
    
    move_P();
    if (isvalid()){
        un.push(state);
        move_P();
        un_parent.push(state);
    }
    else{
        move_P();
    }
    
    move_F_M();
    if (isvalid()){
        un.push(state);
        move_F_M();
        un_parent.push(state);
    }
    else{
        move_F_M();
    }
    
    move_F_P();
    if (isvalid()){
        un.push(state);
        move_F_P();
        un_parent.push(state);
    }
    else{
        move_F_P();
    }
    
    move_M_P();
    if (isvalid()){
        un.push(state);
        move_M_P();
        un_parent.push(state);
    }
    else{
        move_M_P();
    }
    
    move_P_T();
    if (isvalid()){
        un.push(state);
        move_P_T();
        un_parent.push(state);
    }
    else{
        move_P_T();
    }
    
    move_P_S1();
    if (isvalid()){
        un.push(state);
        move_P_S1();
        un_parent.push(state);
    }
    else{
        move_P_S1();
    }
    
    move_P_S2();
    if (isvalid()){
        un.push(state);
        move_P_S2();
        un_parent.push(state);
    }
    else{
        move_P_S2();
    }
    
    move_P_D1();
    if (isvalid()){
        un.push(state);
        move_P_D1();
        un_parent.push(state);
    }
    else{
        move_P_D1();
    }
    
    move_P_D2();
    if (isvalid()){
        un.push(state);
        move_P_D2();
        un_parent.push(state);
    }
    else{
        move_P_D2();
    }
    
    move_F_S1();
    if (isvalid()){
        un.push(state);
        move_F_S1();
        un_parent.push(state);
    }
    else{
        move_F_S1();
    }
    
    move_F_S2();
    if (isvalid()){
        un.push(state);
        move_F_S2();
        un_parent.push(state);
    }
    else{
        move_F_S2();
    }
    
    move_M_D1();
    if (isvalid()){
        un.push(state);
        move_M_D1();
        un_parent.push(state);
    }
    else{
        move_M_D1();
    }
    
    move_M_D2();
    if (isvalid()){
        un.push(state);
        move_M_D2();
        un_parent.push(state);
    }
    else{
        move_M_D2();
    }
    
}

/* - - - - - - - - - | Check Visited | - - - - - - - - */

bool river::visited(){
    
    for (int i=0; i<=1000; i++)
        if (ex[i] == state)
            return true;
    
    return false;
    
}

/* - - - - - - - | Depth First Search | - - - - - - - */

void river::DFS(){
    
    /*
     1  procedure DFS-iterative(G,v):
     2      let S be a stack
     3      S.push(v)
     4      while S is not empty
     5            v = S.pop()
     6            if v is not labeled as discovered:
     7                label v as discovered
     8                for all edges from v to w in expand(v) do
     9                    S.push(w)
     */
    
    aux = -1;
    
    un.push(state);
    un_parent.push(parent);
    
    while (un.empty() == false) {
        
        parent = un_parent.top();
        un_parent.pop();
        state = un.top();
        un.pop();
        
        if (isgoal()) {
            cout << " - - - - - - - - - - - - - - -" << endl;
            cout << "| Answer Found Successfully ! |" << endl;
            cout << " - - - - - - - - - - - - - - -"  << endl << endl;
            aux ++;
            ex[aux] = state;
            ex_parent[aux] = parent;
            print_solution(); // print solution
            break;
        }
        else if (visited()==false) {
            aux++;
            ex[aux] = state;
            ex_parent[aux] = parent;
            expand();
        }
    }
    
    if (un.empty() == true){
        cout << " - - - - - - - - - - - - - - - -" << endl;
        cout << "| No Answer For This Problem !  |" << endl;
        cout << " - - - - - - - - - - - - - - - -" << endl << endl;
    }
    
}

/* - - - - - - - - | Print Solution | - - - - - - - - */

void river::print_solution(){
    
    string solution_arr_inverse[100];
    solution_arr_inverse[0] = state;
    
    int j = aux;
    int k = 0;
    
    while (true) {
        
        for (int i=0; i<aux+2; i++) {
            if (ex_parent[j] == ex[i]) {
                j = i;
                k++;
                solution_arr_inverse[k] = ex[j];
                break;
            }
        }
        if (ex[j] == "000000000")
            break;
    }
    
    string* solution_arr;
    long size = k+1;
    solution_arr = new string [size];
    
    for (int i=0; i<size; i++) {
        solution_arr[i] = solution_arr_inverse[k];
        k--;
    }
    
    cout << "Solution is :" << endl;
    
    int i;
    for (i=0; i < size-1; i++) {
        
        cout << "["<< setw(2) << setfill(' ') << i+1<<"] -> ";
        
        int side=0;
        int arr[2];
        arr[0]=0;
        arr[1]=0;
        int count=0;
        
        for (int j=1; j<9; j++) {
            
            if (solution_arr[i][j] == '0' && solution_arr[i+1][j] == '1') {
                arr[count] = j;
                count++;
                side++;
            }
            
            if (solution_arr[i][j] == '1' && solution_arr[i+1][j] == '0') {
                arr[count] = j;
                count++;
                side--;
            }
            
        }
        if ((side > 0) and count == 2) {
            return_names(arr[0]);
            cout << "and ";
            return_names(arr[1]);
            cout << "go upside!" << endl;
        }
        if ((side > 0) and count == 1){
            return_names(arr[0]);
            cout << "go upside!" << endl;
        }
        if ((side < 0) and count == 2) {
            return_names(arr[0]);
            cout << "and ";
            return_names(arr[1]);
            cout << "back downside!" << endl;
        }
        if ((side < 0) and count == 1){
            return_names(arr[0]);
            cout << "back downside!" << endl;
        }
    }
    cout << "- - - - - - - - -" << endl;
    cout << "Finished in " << i << " steps! \nAnd they are all at upside.";
    
}

/* - - - - - - - - - | Return Names | - - - - - - - - */

void river::return_names(int a){
    
    switch (a) {
        case 1:
            cout << "Father ";
            break;
        case 2:
            cout << "Mother ";
            break;
        case 3:
            cout << "Police ";
            break;
        case 4:
            cout << "First Son ";
            break;
        case 5:
            cout << "Second Son ";
            break;
        case 6:
            cout << "First Daughter ";
            break;
        case 7:
            cout << "Second Daughter ";
            break;
        case 8:
            cout << "Thief ";
            break;
            
        default:
            break;
    }
    
}

/* - - - - - - - - - - - | Main | - - - - - - - - - - */

int main(){
    
    river a;
    
    a.DFS();
    
    return 0;
}
