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