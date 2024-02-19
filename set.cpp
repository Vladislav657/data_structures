#include <iostream>
#include <cstring>

using namespace std;
const int n = 10;
int T[n] = {34, 87, 465, 9, 3, 867, 100, 52, 18, 350};


class Set{
private:
    int setArray[n]{};

public:
    Set(){
        for (int &elem : setArray) elem = 0;
    }

    void add(int elem){
        for (int i = 0; i < n; ++i) if (T[i] == elem) setArray[i] = 1;
    }

    bool contains(int elem){
        for (int i = 0; i < n; ++i) if (T[i] == elem && setArray[i]) return true;
        return false;
    }

    void remove(int elem){
        for (int i = 0; i < n; ++i) if (T[i] == elem) setArray[i] = 0;
    }

    bool empty(){
        for (int elem : setArray) if (elem) return false;
        return true;
    }

    Set operator + (Set A){
        Set res = Set();
        for (int i = 0; i < n; ++i) res.setArray[i] = this->setArray[i] || A.setArray[i];
        return res;
    }

    Set operator * (Set A){
        Set res = Set();
        for (int i = 0; i < n; ++i) res.setArray[i] = this->setArray[i] && A.setArray[i];
        return res;
    }

    Set operator - (Set A){
        Set res = Set();
        for (int i = 0; i < n; ++i) res.setArray[i] = this->setArray[i] && !A.setArray[i];
        return res;
    }

    Set operator - (){
        Set res = Set();
        for (int i = 0; i < n; ++i) res.setArray[i] = !this->setArray[i];
        return res;
    }

    void show(){
        printf("\n");
        for (int i = 0; i < n; ++i) if (setArray[i]) printf("%d ", T[i]);
        printf("\n");
    }
};


Set A, B;
int created = 0;


bool exists(char *s){
    return !(strcmp(s, "A") == 0 && created == 0 || strcmp(s, "B") == 0 && created == 1 ||
    strcmp(s, "A") != 0 && strcmp(s, "B") != 0);
}


void create(){
    if (created == 0){
        A = Set();
        created++;
        printf("\nYou created Set A (1/2)\n");
    }
    else if (created == 1){
        B = Set();
        created++;
        printf("\nYou created Set B (2/2)\n");
    }
    else printf("\nYou already created 2 set\n");
}


void add(){
    char *s = new char[10];
    int elem;
    int c = scanf("%s %d", s, &elem);
    if (c == 2){
        if (strcmp(s, "A") == 0 && exists(s)) A.add(elem);
        else if (strcmp(s, "B") == 0 && exists(s)) B.add(elem);
        else printf("\nThere is NO such set\n");
    } else printf("\nWRONG operation\n");
}


void in(){
    char *s = new char[10];
    int elem;
    int c = scanf("%s %d", s, &elem);
    if (c == 2){
        if (strcmp(s, "A") == 0 && exists(s)) printf("%d", A.contains(elem));
        else if (strcmp(s, "B") == 0 && exists(s)) printf("%d", B.contains(elem));
        else printf("\nThere is NO such set\n");
    } else printf("\nWRONG operation\n");
}


void del(){
    char *s = new char[10];
    int elem;
    int c = scanf("%s %d", s, &elem);
    if (c == 2){
        if (strcmp(s, "A") == 0 && exists(s)) A.remove(elem);
        else if (strcmp(s, "B") == 0 && exists(s)) B.remove(elem);
        else printf("\nThere is NO such set\n");
    } else printf("\nWRONG operation\n");
}


void empty(){
    char *s = new char[10];
    int c = scanf("%s", s);
    if (c == 1){
        if (strcmp(s, "A") == 0 && exists(s)) printf("%d", A.empty());
        else if (strcmp(s, "B") == 0 && exists(s)) printf("%d", B.empty());
        else printf("\nThere is NO such set\n");
    } else printf("\nWRONG operation\n");
}


void un(){
    if (exists((char *)"A") && exists((char *)"B")){
        Set C = A + B;
        C.show();
    } else printf("\nYou need 2 sets\n");
}


void intersection(){
    if (exists((char *)"A") && exists((char *)"B")){
        Set C = A * B;
        C.show();
    } else printf("\nYou need 2 sets\n");
}


void diff(){
    if (!(exists((char *)"A") && exists((char *)"B"))){
        printf("\nYou need 2 sets\n");
        return;
    }
    char *s1 = new char[10];
    char *s2 = new char[10];
    int c = scanf("%s %s", s1, s2);
    if (c == 2){
        if (strcmp(s1, "A") == 0 && strcmp(s2, "B") == 0){
            Set C = A - B;
            C.show();
        } else if (strcmp(s1, "B") == 0 && strcmp(s2, "A") == 0){
            Set C = B - A;
            C.show();
        } else printf("\nWRONG operation\n");
    }
}


void addition(){
    char *s = new char[10];
    int c = scanf("%s", s);
    if (c == 1){
        if (strcmp(s, "A") == 0 && exists(s)){
            Set C = -A;
            C.show();
        }
        else if (strcmp(s, "B") == 0 && exists(s)){
            Set C = -B;
            C.show();
        }
        else printf("\nThere is NO such set\n");
    } else printf("\nWRONG operation\n");
}


void show(){
    char *s = new char[10];
    int c = scanf("%s", s);
    if (c == 1){
        if (strcmp(s, "A") == 0 && exists(s)) A.show();
        else if (strcmp(s, "B") == 0 && exists(s)) B.show();
        else printf("\nThere is NO such set\n");
    } else printf("\nWRONG operation\n");
}


void show_all(){
    if (exists((char *)"A")){
        printf("\nA: ");
        A.show();
    }
    if (exists((char *)"B")){
        printf("\nB: ");
        B.show();
    }
}


void univ(){
    printf("\nUNIVERSAL set: ");
    for (int element : T) printf("%d ", element);
    printf("\n\n");
}


void help(){
    printf("\n\nOPERATIONS:\n"
           "    --create (create set)\n"
           "    --add 'set' 'elem' (add to set 'set' element 'elem')\n"
           "    --in 'set' 'elem' (checks if set 'set' contains element 'elem'(1) or not(0))\n"
           "    --del 'set' 'elem' (remove from set 'set' element 'elem')\n"
           "    --empty 'set' (checks if set 'set' is empty(1) or not(0))\n"
           "    --union (select COMMON elements from sets)\n"
           "    --intersect (select ALL elements from sets)\n"
           "    --diff 'set1' 'set2' (select elements from 'set1' which NOT in 'set2')\n"
           "    --addition 'set' (select elements from UNIVERSAL set which NOT in 'set')\n"
           "    --show 'set' (print set 'set')\n"
           "    --show_all (print ALL sets)\n"
           "    --exit (exit program)\n"
           "    --help (OPERATIONS list)\n"
           "    --univ (print UNIVERSAL set)\n");
}


int main(){
    printf("You can CREATE 2 sets and\nADD to it ONLY universal set elements\nuniversal set: ");
    for (int element : T) printf("%d ", element);
    help();
    do {
        char *operation = new char[10];
        scanf("%s", operation);
        if (strcmp(operation, "--create") == 0) create();
        else if (strcmp(operation, "--add") == 0) add();
        else if (strcmp(operation, "--in") == 0) in();
        else if (strcmp(operation, "--del") == 0) del();
        else if (strcmp(operation, "--empty") == 0) empty();
        else if (strcmp(operation, "--union") == 0) un();
        else if (strcmp(operation, "--intersect") == 0) intersection();
        else if (strcmp(operation, "--diff") == 0) diff();
        else if (strcmp(operation, "--addition") == 0) addition();
        else if (strcmp(operation, "--show") == 0) show();
        else if (strcmp(operation, "--show_all") == 0) show_all();
        else if (strcmp(operation, "--help") == 0) help();
        else if (strcmp(operation, "--univ") == 0) univ();
        else if (strcmp(operation, "--exit") == 0) break;
        else printf("\nWRONG operation\n");
    } while (true);
    return 0;
}
