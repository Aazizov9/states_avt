#include <iostream>
#include <map>
#include <vector>
#include <fstream>

using namespace std;
typedef long long ll;

vector<string> q;
vector<string> q2;
string y, x;
map<string, pair<string, char>> mp;

string to2(ll n, ll k) {
    string s;
    while (k) {
        s = char('0' + (n & 1)) + s;
        n >>= 1;
        k--;
    }
    return s;
}

int main(int argc, char* argv[]) {
    ifstream fin;
    ofstream fout;
    fin.open(argv[1]);
    fout.open(argv[2]);
    string u;
    ll n, cnt;
    q.resize(1);
    fin >> n >> u;
    fin >> cnt >> cnt;
    q.resize(1 << cnt); q2.resize(1 << cnt);
    for (ll i = 0; i < n; i++) {
        char c;
        for (ll i = 0; i < (1 << cnt); i++) {
            fin >> c;
            q2[i] += c;
        }
        fin >> cnt >> cnt;
    }
    fin >> y;
    for (ll i = 0; i < (1 << cnt); i++) {
        ll tmp = i;
        x += char((tmp & 1) + '0');
        for (ll j = 0; j < n; j++) {
            tmp >>= 1;
            q[i] = char((tmp & 1) + '0') + q[i];
        }
        mp[q[i] + x[i]] = make_pair(q2[i], y[i]);//2^cnt-1 - q[i] + x[i]

    }

    vector<pair<string, string>> ans;
    bool bn;
    string ad1, ad2
    for (ll i = 0; i < (1 << cnt); i += 2) {
        for (ll j = i + 2; j < (1 << cnt); j += 2) {
            //cout << q[i] << " : " << q[j] << endl;
            ad1 = q[i]; ad2 = q[j];
            bn = 1;
            for (ll k = 0; k < (1 <<1 << n); k++) {
                ll tmp = k;
                for (ll b = 1; b < (1 << n); b++) {
                    //n=2 2^2=4 1,2,3
                    //n=3 2^3=8 1234567
                    char A = '0' + (tmp & 1);
                    // n=2  k = 0  000
                    // n=2  k=6   110  11 1 0

                    tmp >>= 1;
                    //  mp[q[i] + x[i]]
                    if (mp[ad1 + A].second != mp[ad2 + A].second) {
                        bn = 0;
                        break;
                    }
                    //  cout << "Kogda A=" << A << "  -> " << mp[ad1 + A].second << " : " << mp[ad2 + A].second << endl;
                    ad1 = mp[ad1 + A].first;
                    ad2 = mp[ad2 + A].first;
                }
                if (!bn) break;
            }
            if (bn) {
                ans.push_back(make_pair(to2(i / 2, n), to2(j / 2, n)));
            }
            //cout << endl;
        }
    }
    for (auto i : ans) {
        fout << i.first << " " << i.second << " ";
    }


    /*for (int i = 0; i < (1 << cnt); i++) {
      cout << q[i] << " " << x[i] << " " << q2[i] << " " << y[i] << endl;
    }
    */

    // cnt-1 (2-1)   cnt-

    /*
    1 0
    2 2 0101-4 4/2 =n n=n-1;2-1=1 (0,1) 2^n-1
    2 2 1110
      q2_0 01
      q2_1 11
      2 00
  2 3 00110100
  2 3 11000000
  2 3 01010110


  000
  001
  010
  011
  100
  101
  110
  111
      */

}
