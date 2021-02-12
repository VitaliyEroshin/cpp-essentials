#include <bits/stdc++.h>
using namespace std;
 
const int ALPHABET_SIZE = 26;
const int ROOT = 0;
struct node {
    int next[ALPHABET_SIZE];

    int parent;
    int value;
    int suffLink;
    int terminal;
    vector<int> terminalIds;
    node(): parent(-1), value(-1), suffLink(-1), terminal(0) {
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            next[i] = -1;
        }
    }
};
 
vector<node> trie = {node()};
 
void add(string s, int id, int x = ROOT) {
    for (auto c : s) {
        c -= 'a';
        if (trie[x].next[c] == -1) {
            trie.push_back(node());
            trie.back().parent = x;
            trie.back().value = c;
            trie[x].next[c] = trie.size() - 1;
        }
        x = trie[x].next[c];
    }

    trie[x].terminal++;
    trie[x].terminalIds.push_back(id);
}
 

void AhoCorasick(int x = ROOT) {
    queue<int> q;
    for (int c = 0; c < ALPHABET_SIZE; c++) {
        if (trie[x].next[c] != -1) 
            q.push(trie[x].next[c]);
        else
            trie[x].next[c] = x;
    }
    
    while (!q.empty()) {
        int a = q.front();
        q.pop();

        int b = trie[a].parent;
        int d;

        if (a == ROOT || b == ROOT) {
            d = ROOT;
        } else {
            int c = trie[b].suffLink;
            d = trie[c].next[trie[a].value];
        }

        trie[a].suffLink = d;
        

        for (int ch = 0; ch < ALPHABET_SIZE; ch++) {
            if (trie[a].next[ch] != -1) {
                q.push(trie[a].next[ch]);
            } else {
                trie[a].next[ch] = trie[d].next[ch];
            }
        }
    }
}

 


void solve() {
    trie[0].suffLink = ROOT;
    
    string T;
    cin >> T;

    int n;
    cin >> n;
    vector<int> len(n);
    vector<int> pos[n];

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        len[i] = s.length();
        add(s, i);
    }
    AhoCorasick();
     
    int x = ROOT;
    for (int i = 0; i < T.size(); i++) {
        char c = T[i] - 'a';
        x = trie[x].next[c];

        for (int y = x; y > 0; y = trie[y].suffLink) {
            for (auto id : trie[y].terminalIds) {
                pos[id].push_back(i);
            }
        }

    }
 
    for (int i = 0; i < n; i++) {
        cout << pos[i].size() << ' ';
        for (auto x : pos[i]) cout << x - len[i] + 2 << ' ';
        cout << '\n';
    }
     
}
 
signed main() {
    freopen("inputik.txt", "r", stdin);
    freopen("outputik.txt", "w", stdout);
    #ifdef debug
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
 
    solve();
}