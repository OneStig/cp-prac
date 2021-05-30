#include <bits/stdc++.h>

using namespace std;

int n, q;
int avail[200001];

struct endp {
    int ind;
    int x;
    bool lr;
};

struct qr {
    int l;
    int r;
    int pos;
    int sol;
};

vector<int> ftree;

void fupd(int k, int x) {
    k += n;
    ftree[k] = x;

    for (k /= 2; k >= 1; k /= 2) {
        ftree[k] = ftree[2 * k] + ftree[2 * k + 1];
    }
}

int fsum(int a, int b) {
    a += n;
    b += n;

    int s = 0;

    while (a <= b) {
        if (a % 2 == 1) {
            s += ftree[a++];
        }

        if (b % 2 == 0) {
            s += ftree[b--];
        }

        a /= 2;
        b /= 2;
    }

    return s;
}

vector<int> segtree;

void upd(int k, int x) {
    k += n;
    segtree[k] = x;

    for (k /= 2; k >= 1; k /= 2) {
        segtree[k] = segtree[2 * k] + segtree[2 * k + 1];
    }
}

int treemin(int a, int b) {
    a += n;
    b += n;

    int m = INT_MAX;

    while (a <= b) {
        if (a % 2 == 1) {
            m = min(m, segtree[a]);
            a++;
        }

        if (b % 2 == 0) {
            m = min(m, segtree[b]);
            b--;
        }

        a /= 2;
        b /= 2;
    }

    return m;
}

int main() {
    ios_base::sync_with_stdio(); cin.tie(0); freopen("2.in", "r", stdin); freopen("test.out", "w", stdout);
    
    cin >> n >> q;
    vector<int> colors;
    vector<qr> queries(q);

    vector<int> newInd(n);

    for (int i = 0; i < n; i++) {
        int tmp;
        cin >> tmp;
        
        if (i == 0 || tmp != colors.back()) {
            colors.push_back(tmp);
        }

        newInd[i] = colors.size() - 1;

        avail[i] = -1;
    }

    

    n = colors.size();

    for (int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        qr tmp;
        tmp.l = newInd[a - 1];
        tmp.r = newInd[b - 1];
        tmp.pos = i;
        queries[i] = tmp;
    }

    sort(queries.begin(), queries.end(), [](qr a, qr b) { return a.r < b.r; });

    segtree.resize(2 * n, 0);

    vector<endp> endpoints;


    for (int i = 0; i < n; i++) {
        upd(i, colors[i]);

        if (avail[colors[i]] != -1 && treemin(avail[colors[i]], i) >= colors[i]) {
            endp l;
            l.lr = false;
            l.x = avail[colors[i]];
            l.ind = i;

            endp r;
            r.lr = true;
            r.x = i;
            r.ind = avail[colors[i]];

            endpoints.push_back(l);
            endpoints.push_back(r);
        }

        avail[colors[i]] = i;
    }

    sort(endpoints.begin(), endpoints.end(), [](endp a, endp b) { return a.x < b.x; });

    cout << "test" << endl;

    vector<int> openv(n);
    vector<int> closev(n);

    int closedcount = 0;
    int opencount = 0;

    ftree.resize(2 * n, 0);

    int qind = 0;

    for (int i = 0; i < endpoints.size(); i++) {
        if (!endpoints[i].lr) {
            opencount++;

            fupd(endpoints[i].ind, 1);
        }
        else {
            closedcount++;

            fupd(endpoints[i].x, 0);
        }

        openv[i] = opencount;
        closev[i] = closedcount;

        while (queries[qind].r == i) {
            int lsum = openv[i] - openv[queries[qind].l] - fsum(queries[qind].l, i);
            queries[qind].sol = i - queries[qind].l + 1 - lsum;

            // - (closev[i] - closev[queries[qind].l]
            // - (openv[i] - openv[queries[qind].l])
            // + fsum(queries[qind].l, i));
            qind++;
        }
    }

    sort(queries.begin(), queries.end(), [](qr a, qr b) { return a.pos < b.pos; });

    for (qr i : queries) {
        cout << i.sol << endl;
    }
}