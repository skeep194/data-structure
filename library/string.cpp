vector<int> manacher(string& s)
{
    vector<int> manacher(s.size(), 0);
    int r = -1;
    int p = -1;
    for(int i=0;i<s.size();++i)
    {
        if(r >= i)
        {
            manacher[i] = min(r-i, manacher[2*p-i]);
        }
        int lft = i-manacher[i]-1;
        int rgt = i+manacher[i]+1;
        while(lft >= 0 && rgt < s.size() && s[lft] == s[rgt])
        {
            manacher[i]++;
            --lft;
            ++rgt;
        }
        if(r < manacher[i] + i)
        {
            r = manacher[i] + i;
            p = i;
        }
    }
    return manacher;
}

vector<int> suffix_array(const string& s)
{
    vector<int> group(s.size()+1, 0);
    group[s.size()] = -1;
    for(int i=0;i<s.size();++i)
    {
        group[i] = s[i];
    }
    vector<int> ret(s.size(), 0);
    for(int i=0;i<s.size();++i)
    {
        ret[i] = i;
    }

    int t = 1;
    auto compare = [&](int a, int b) {
        if(group[a] != group[b]) return group[a] < group[b];
        return group[a+t] < group[b+t];
    };
    
    while(t <= s.size())
    {
        stable_sort(ret.begin(), ret.end(), compare);
        vector<int> new_group(s.size()+1, -1);
        new_group[ret[0]] = 0;
        new_group[s.size()] = -1;
        for(int i=1;i<s.size();++i)
        {
            if(!compare(ret[i-1], ret[i]))
            {
                new_group[ret[i]] = new_group[ret[i-1]];
            }
            else
            {
                new_group[ret[i]] = new_group[ret[i-1]] + 1;
            }
        }
        t <<= 1;
        group = new_group;
    }
    return ret;
}

vector<int> lcp_array(const string& s, const vector<int>& arr)
{
    vector<int> ret(s.size(), -1);
    vector<int> inv(s.size(), 0);
    for(int i=0;i<s.size();++i)
    {
        inv[arr[i]] = i;
    }
    int prev = 0;
    for(int i=0;i<s.size();++i)
    {
        if(i == arr[0]) continue;
        prev = max(0, prev-1);
        ret[inv[i]] = prev;
        for(int j=i+prev, k=arr[inv[i]-1]+prev;j<s.size() && k<s.size() && s[j]==s[k];++j,++k)
        {
            ret[inv[i]]++;
        }
        prev = ret[inv[i]];
    }
    return ret;
}


vector<int> zarray(const string& s)
{
    vector<int> ret(s.size());
    int l = 0, r = 0;
    for(int i=1;i<s.size();++i)
    {
        if(r >= i)
        {
            ret[i] = ret[i-l];
            if(i + ret[i] > r)
            {
                ret[i] = r - i + 1;
            }
        }
        for(int j=i+ret[i], k=ret[i];j<s.size();++j, ++k)
        {
            if(s[j] == s[k])
                ret[i]++;
            else break;
        }
        if(r <= i+ret[i]-1)
        {
            r = i+ret[i]-1;
            l = i;
        }
    }
    return ret;
}