#include <bits/stdc++.h>
using namespace std;
#define fastio cin.tie(0)->sync_with_stdio(0);
typedef __int128_t i128;
typedef int64_t i64;
typedef int32_t i32;
#define MULTITC
// #define int long long
void solve();
int32_t main()
{
	int tc = 1;
	fastio;
	#ifdef MULTITC
		cin>>tc;
	#endif
	while(tc--)
		solve();
}
//------------------------------------------------
#define X real()
#define Y imag()
namespace Geometry
{
	template<typename T>
	T area(vector<complex<T>>& pos)
	{
		pos.push_back(pos[0]);
		T ret = 0;
		for(int i=0;i<pos.size()-1;++i)
		{
			ret += pos[i].X*pos[i+1].Y-pos[i+1].X*pos[i].Y;
		}
		pos.pop();
		return abs(ret);
	}

	template<typename T>
	T cross_product(const complex<T>& a, const complex<T>& b)
	{
		return (conj(a)*b).Y;
	}
	
	template<typename T>
	T inner_product(const complex<T>& a, const complex<T>& b)
	{
		return a.X*b.X+a.Y+b.Y;
	}
	
	template<typename T>
	T ccw(const pair<complex<T>, complex<T>>& line, const complex<T>& pos)
	{
		return cross_product(pos-line.first, pos-line.second);
	}
}

void solve()
{
	int n;
	vector<complex<int>> arr;
	int ret[70][2];
	cin>>n;
	for(int i=0;i<n;++i)
	{
		int a, b;
		cin>>a>>b;
		arr.push_back({a, b});
	}
	arr.push_back(arr[0]);
	bool lft = false;
	for(int i=0;i<70;++i)
	{
		for(int j=0;j<2;++j)
		{
			ret[i][j] = 987654321;
		}
	}
	bool chk[70];
	memset(chk, 0, sizeof(chk));
	for(int i=0;i<n;++i)
	{
		const auto& here = arr[i];
		const auto& next = arr[i+1];
		// cout<<here<<endl;
		if(here.Y < next.Y)
		{
			lft = true;
		}
		if(here.Y == next.Y)
		{
			chk[here.Y+30] = true;
			continue;
		}
		if(!lft)
		{
			for(int j=here.Y;j>=next.Y;--j)
			{
				pair<int,int> v = {0, 60};
				for(int i=-30;i<=30;++i)
				{
					complex<int> p = {i, j};
					// cout<<here<<next<<p<<Geometry::cross_product(p-here, p-next)<<endl;
				}
				while(v.first < v.second)
				{
					complex<int> mid = {(v.first+v.second)/2-30, j};
					// cout<<v.first<<' '<<v.second<<' '<<mid<<'\n';
					if(Geometry::cross_product(mid-here, mid-next) < 0)
					{
						v.first = mid.X + 30 + 1;
					}
					else
					{
						v.second = mid.X + 30;
					}
				}
				// cout<<j<<' '<<v.first<<' '<<v.second<<endl;
				ret[j+30][1] = v.first-31;
			}
		}
		else
		{
			for(int j=here.Y;j<=next.Y;++j)
			{
				for(int i=1;i<=4;++i)
				{
					complex<int> p = {i, j};
					// cout<<here<<next<<p<<Geometry::cross_product(p-here, p-next)<<endl;
				}
				pair<int,int> v = {0, 60};
				while(v.first < v.second)
				{
					complex<int> mid = {(v.first+v.second)/2-30, j};
					if(Geometry::cross_product(mid-here, mid-next) >= 0)
					{
						v.first = mid.X + 30 + 1;
					}
					else
					{
						v.second = mid.X + 30;
					}
				}
				ret[j+30][0] = v.first-30;
			}
		}
	}
	vector<tuple<int,int,int>> pnt;
	for(int i=30;i>=-30;--i)
	{
		if(ret[i+30][0] <= ret[i+30][1] && ret[i+30][0] != 987654321 && ret[i+30][1] != 987654321 && !chk[i+30])
		{
			pnt.push_back({i, ret[i+30][0], ret[i+30][1]});
		}
	}
	cout<<pnt.size()<<'\n';
	for(auto& [a, b, c] : pnt)
	{
		cout<<a<<' '<<b<<' '<<c<<'\n';
	}
}