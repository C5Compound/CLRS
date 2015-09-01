/**
 *  RK算法实现
 */
bool isMatch(string &P, string &T, int ps, int ts, int len) 
{
    while (len--) {
        if (P[ps + len] != T[ts + len]) {
            return false;
        }
    }
    return true;
}

void RabinKarp(string &P, string &T, unsigned int d, unsigned q) 
{
    if (P.size() > T.size() || P.empty()) {
        return;
    }
    // 预处理
    int m = P.size(), n = T.size(), h = 1;
    for (int i = 1; i < m; ++i) {
        h = (h * d) % q;
    }
    int p = 0, t = 0;
    for (int i = 0, i < m; ++i) {
        p = (d * p + P[i]) % q;
        t = (d * t + T[i]) % q;
    }
    // 匹配
    for (int s = -1; s < n - m; ++s) {
        if (p == t) {
            if (isMatch(P, T, 0, s + 1, m)) {
                // 匹配成功
                cout << "匹配成功索引：" << s + 1 << endl;
            }
        }
        if (s < n - m - 1) {
            t = (d * (t - h * T[s + 1]) + T[s + m + 1]) % q;
        }
    }
}

/**
 *  KMP算法实现
 */
void compute_prefix_function(string &P, vector<int> &pi)
{
    int m = P.size();
    pi[0] = -1;
    for (int k = -1, q = 1; q < m; ++q) {
        while (k > -1 && P[k + 1] != P[q]) {
            k = pi[k];
        }
        if (P[k + 1] == P[q]) {
            ++k;
        }
        pi[q] = k;
    }
}

void kmp_matcher(string &P, string &T)
{
    if (P.size() > T.size() || P.empty()) {
        return;
    }
    int m = P.size(), n = T.size();
    vector<int> pi(m);
    // 预处理
    compute_prefix_function(P, pi);
    for (int i = 0, q = -1; i < n; ++i) {
        while (q > -1 && P[q + 1] != T[i]) {
            q = pi[q];
        }
        if (P[q + 1] == T[i]) {
            ++q;
        }
        if (q == m - 1) {
            //匹配成功
            cout << "匹配成功索引：" << i << endl;
            q = pi[q];
        }
    }
}