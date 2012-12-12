#include <algorithm>

#include "Region.h"

#include <assert.h>

using namespace NICE;
using namespace std;

void SegList::delseg(lsegp &lp)
{
    lsegp hp = lp;
    lp = lp->next;
    delete hp;
}

void SegList::divseg(lsegp &lp,int x)
{
    lp->next=new lseg(x+1,lp->x2,lp->next);
    lp->x2=x;
}


SegList & SegList::operator=(const SegList& src)
{
    if (this==&src) return *this;

    list->del();
    delete list;

    list=NULL;
    lsegp sourcep=src.list;

    if (sourcep!=NULL)
    {
        list=new lseg(*sourcep);
        list->next=NULL;
        lsegp destp=list;
        sourcep=sourcep->next;
        while (sourcep!=NULL)
        {
            destp->next=new lseg(*sourcep);
            sourcep=sourcep->next;
            destp=destp->next;
            destp->next=NULL;
        }
    }
    area=src.area;
    return *this;
}

SegList::SegList(const SegList& r)
{
    list=NULL;
    lsegp sourcep=r.list;
    if (sourcep!=NULL)
    {
        list=new lseg(*sourcep);
        list->next=NULL;
        lsegp destp=list;
        sourcep=sourcep->next;
        while (sourcep!=NULL)
        {
            destp->next=new lseg(*sourcep);
            sourcep=sourcep->next;
            destp=destp->next;
            destp->next=NULL;
        }
    }
    area=r.area;
}

int SegList::del(lsegp &lp,int x1,int x2)
{
    int da=0;
    if (lp==NULL) return 0; // leere Liste
    int lx1=lp->x1;
    if (lx1>x2) return 0; // Bereich völlig vor erstem Segment
    int lx2=lp->x2;
    if (lx2<x1) return del(lp->next,x1,x2); // Bereich völlig nach erstem Segment
    if (lx1>=x1) // Bereich beginnt vor erstem segment
    {
        if (lx2>x2) // Segment von vorne Kürzen
        {
            lp->x1=x2+1;
            da=x2+1-lx1;
            area-=da;
            return da;
        }
        else
        {
            delseg(lp); // Segment liegt innerhalb des bereiches
            da=lx2-lx1+1;
            area-=da;
            return del(lp,x1,x2)+da;
        }
    }
    // Bereich beginnt im ersten segment -> Segment kürzen
    lp->x2=x1-1;
    if (lx2>x2) // ragt altes Segment über Bereich hinaus?
    {
        // zweites teilsegment einfügen
        lp->next=new lseg(x2+1,lx2,lp->next);
        da=x2-x1+1;
        area-=da;
        return da;
    }
    else
    {
        da=lx2-x1+1;
        area-=da;
        return del(lp->next,x1,x2)+da;
    }
}

int SegList::del(int x1,int x2)
{
    assert(x1<=x2);
    return del(list,x1,x2);
}

int SegList::del(const SegList &s)
{
    int da=0;
    if (s.isEmpty()) return 0;
    if (isEmpty()) return 0;

    lsegp lp=s.list;
    while (lp!=NULL)
    {
        da+=del(lp->x1,lp->x2);
        lp=lp->next;
    }
    return da;
}

int SegList::getMin() const
{
    if ( list != NULL )
        return list->x1;
    else
        return -1;
}

int SegList::getMax() const
{
    if ( list != NULL )
    {
        lsegp l = list;
        while (l->next != NULL)
            l = l->next;
        return l->x2;
    } else {
        return -1;
    }
}

int SegList::add(lsegp &lp,int x1,int x2)
{
    int da;
    if (lp==NULL)
    {
        lp=new lseg(x1,x2);
        da=x2-x1+1;
        area+=da;
        return da;
    }

    int lx1=lp->x1;
    int lx2=lp->x2;

    if (lx2+1<x1)
    {
        return add(lp->next,x1,x2);
    }

    if (lp->connected(x1,x2))
    {
        if (lp->x1<x1) x1=lp->x1;
        if (lp->x2>x2) x2=lp->x2;
        delseg(lp);
        da=-lx2+lx1-1;
        area+=da;
        return add(lp,x1,x2)+da;
    }
    // Segment liegt vor der Liste
    lp=new lseg(x1,x2,lp);
    da= x2-x1+1;
    area+=da;
    return da;
}

int SegList::add(int x1,int x2)
{
    assert(x1<=x2);
    return add(list,x1,x2);
}

int SegList::add(const SegList &s)
{
    int da=0;
    if (s.isEmpty()) return 0;
    lsegp lp=s.list;
    while (lp!=NULL)
    {
        da+=add(lp->x1,lp->x2);
        lp=lp->next;
    }
    return da;
}

int SegList::andop(lsegp &p1,lsegp const &p2)
{
    if (p2==NULL)
    {
        del(p1);
        area=0;
        return 1;
    }
    if (p1==NULL) return 1;
    if (p1->x2<p2->x1)
    {
        area-=p1->len();
        delseg(p1);
        return andop(p1,p2);
    }
    if (p2->x2<p1->x1) return andop(p1,p2->next);
    if (p1->x1<p2->x1)
    {
        area-=p2->x1-p1->x1;
        p1->x1=p2->x1;
    }
    if (p1->x2<=p2->x2) return andop(p1->next,p2);
    else
    {
        divseg(p1,p2->x2);
        return andop(p1->next,p2->next);
    }
}

int SegList::andop(const SegList &s)
{
    if (area==0) return 1;
    if (s.isEmpty())
    {
        // ganze Liste löschen
        area=0;
        del(list);
        return 1;
    }
    andop(list,s.list);
    return 1;
}

bool SegList::inside(int x1) const
{
    lsegp hp=list;
    while (hp!=NULL)
    {
        if (hp->inside(x1)) return true;
        hp=hp->next;
    }
    return false;
}

int Region::newy(int y)
{
    if (sl.size()==0) {
        y0=y;
    }
    while (y>=y0+(int)sl.size())
    {
        sl.push_back(SegList());
    }
    while (y<y0)
    {
        sl.push_front(SegList());
        y0--;
    }
    return 1;
}

int Region::cuty()
{
    if (sl.size()==0) return 1;

    while ((sl.size()>0)&&(sl[0].isEmpty()))
    {
        sl.pop_front();
        y0++;
    }

    while ((sl.size()>0)&&(sl[sl.size()-1].isEmpty()))
    {
        sl.pop_back();
    }
    return 1;
}


void Region::getRect ( int & xi, int & yi, int & xa, int & ya ) const
{
    yi = y0;
    ya = y0 + sl.size() - 1;
    xa = -1;
    xi = 0;

    for ( deque<SegList>::const_iterator i = sl.begin();
            i != sl.end();
            i++ )
    {
        if ( (xi > i->getMin()) || (i == sl.begin()) )
            xi = i->getMin();
        if ( xa < i->getMax() )
            xa = i->getMax();
    }

}

int Region::getWidth () const
{
    int max = 0;
    for ( deque<SegList>::const_iterator i = sl.begin();
            i != sl.end();
            i++ )
    {
        if ( max < i->getArea() ) max = i->getArea();
    }

    return max;
}

int Region::getHeight () const
{
    return sl.size();
}

int Region::add(int x,int y)
{
    int da;
    newy(y);
    da= sl[y-y0].add(x);
    area+=da;
    return da;
}

int Region::add(const Region &r)
{
    int y;
    int da=0;
    for (y=0;y<(int)r.sl.size();y++)
    {
        newy(y+r.y0);
        da+=sl[y+r.y0-y0].add(r.sl[y]);
    }
    area+=da;
    return da;
}

int Region::add(int x1,int y1,int x2,int y2)
{
    int y;
    int da=0;
    for (y=y1;y<=y2;y++)
    {
        newy(y);
        da+=sl[y-y0].add(x1,x2);
    }
    area+=da;
    return da;
}

int Region::del(int x,int y)
{
    int da;
    int yh=y-y0;
    if (yh<0) return 0;
    if (yh>=(int)sl.size()) return 0;
    da= sl[y-y0].del(x);

    cuty();

    area-=da;
    return da;
}

int Region::del(const Region &r)
{
    int y;
    int da=0;
    for (y=r.y0;y<r.y0+(int)r.sl.size();y++)
    {
        if (inside(y))
            da+=sl[y-y0].del(r.sl[y-r.y0]);
    }
    cuty();
    area-=da;
    return da;
}

int Region::del(int x1,int y1,int x2,int y2)
{
    int y;
    int da=0;
    for (y=y1;y<=y2;y++)
    {
        int yh=y-y0;
        if ((yh>=0)&&(yh<(int)sl.size()))
            da+=sl[yh].del(x1,x2);
    }
    cuty();
    area-=da;
    return da;
}

int Region::andop(const Region &r)
{
    int da=0;
    int y;
    for (y=0;y<(int)sl.size();y++)
    {
        if (r.inside(y+y0))
        {
            if (!sl[y].isEmpty())
            {
                da+=sl[y].andop(r.sl[y+y0-r.y0]);
            }
        }
        else sl[y].free();
    }
    area-=da;
    return da;
}

void Region::getCentroid ( double & x, double & y ) const
{
    int anz = 0;
    x = 0.0;
    y = 0.0;

    for (int ly=0;ly<(int)sl.size();ly++)
    {
        SegList::lsegp fp=sl[ly].list;
        while (fp != NULL)
        {
            for (int i = fp->x1; i <= fp->x2; i++)
            {
                x += i;
                y += ly+y0;
                anz++;
            }
            fp = fp->next;
        }
    }
    x /= (double)anz;
    y /= (double)anz;
}

void Region::setIntersection ( const Region & x, const Region & y )
{
    *this = x - (x - y);
}

bool Region::inside(int xp,int yp) const
{
    int yh=yp-y0;
    if (yh<0) return false;
    if (yh>=(int)sl.size()) return false;
    return sl[yh].inside(xp);
}

bool Region::inside(int yp) const
{
    int yh=yp-y0;
    if (yh<0) return false;
    if (yh>=(int)sl.size()) return false;
    return true;
}

