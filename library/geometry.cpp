#define X real()
#define Y imag()
const double PI = acos(-1);
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
    T ccw(const complex<T>& a, const complex<T>& b, const complex<T>& pos)
    {
        return cross_product(pos-a, pos-b);
    }
    ;
}