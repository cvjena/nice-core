#ifndef _IMAGE_REGION_H
#define _IMAGE_REGION_H

#include <set>
#include <limits>
#include <utility>
#include <iostream>
#include <deque>

namespace NICE {

/**
 * @brief imported from ICE, thanks to noo
 **/
class SegList {
  public:
    class lseg { // Knoten in der Segmentliste
      public: // public _in SegList_
        int x1, x2;
        lseg *next;

        lseg() : x1 ( 0 ), x2 ( 0 ), next ( NULL ) {} ;
        lseg ( int x1p, int x2p ) : x1 ( x1p ), x2 ( x2p ), next ( NULL ) {} ;
        lseg ( int x1p, int x2p, lseg *n ) : x1 ( x1p ), x2 ( x2p ), next ( n ) {} ;
        lseg ( const lseg &p ) : x1 ( p.x1 ), x2 ( p.x2 ), next ( p.next ) {};
        ~lseg() {}

        void del() {
          if ( next != NULL )
          {
            next->del();
            delete next;
          }
        }

        bool inside ( int xp ) const
        {
          if ( xp < x1 ) return false;
          if ( xp <= x2 ) return true;
          if ( next == NULL ) return false;
          return next->inside ( xp );
        }

        bool connected ( int x1p, int x2p ) const
        {
          if ( x2p < x1 - 1 ) return false; // total unterhalb
          if ( x1p > x2 + 1 ) return false; // total oberhalb
          return true; // sonst (inklusive beruehrung)
        }

        int len() {
          return x2 -x1 + 1;
        }
    };

    typedef lseg * lsegp;

    // data
    lsegp list;
  private:

    int area;
    // methods

    void del ( lsegp &p )
    {
      if ( p != NULL )
      {
        del ( p->next );
        area -= p->x2 - p->x2 + 1;
        delete p;
        p = NULL;
      }
    }

    void delseg ( lsegp &lp );
    void divseg ( lsegp &lp, int x );
    int add ( lsegp &lp, int x1, int x2 );
    int del ( lsegp &lp, int x1, int x2 );
    int andop ( lsegp &p1, lsegp const &p2 );

  public:
    SegList() : list ( NULL ), area ( 0 ) {};
    SegList ( const SegList& );
    ~SegList() {
      del ( list );
    }

    int add ( int x1, int x2 );
    int add ( const SegList&s );
    int add ( int x ) {
      return add ( x, x );
    }

    int del ( int x1, int x2 );
    int del ( const SegList&s );
    int del ( int x ) {
      return del ( x, x );
    }

    int andop ( const SegList&s );

    bool isEmpty() const {
      return list == NULL;
    }
    bool inside ( int x ) const;
    int getArea() const {
      return area;
    }

    void free() {
      del ( list );
    }

    int getMin() const;
    int getMax() const;

    SegList & operator= ( const SegList&src );

    friend std::ostream& operator << ( std::ostream &, const SegList &s );
};

/**
* @brief partial imported from ICE, thanks to noo
**/
class Region {

  protected:
    int newy ( int y );
    int cuty();
    int y0;
    int area;
    std::deque<SegList> sl;

  public:
    /** Create an empty region */
    Region() : y0 ( 0 ), area ( 0 ) {};

    int getWidth () const;
    int getHeight () const;

    /** Get the top-left and bottom-right corner of the bounding box */
    void getRect ( int & xi, int & yi, int & xa, int & ya ) const;

    /** Add a point to the region */
    int add ( int x, int y );

    /** Add a rectangular area to the region
    @param xi x coordinate of the top left corner
    @param yi y coordinate of the top left corner
    @param xa x coordinate of the bottom right corner
    @param ya y coordinate of the bottom right corner
    */
    int add ( int x1, int y1, int x2, int y2 );
    int add ( const Region &r );

    int del ( int x, int y );
    int del ( int x1, int y1, int x2, int y2 );
    int del ( const Region &r );

    int andop ( const Region &r );

    /** Check whether a pixel is inside of the region */
    bool inside ( int xp, int yp ) const;

    bool inside ( int yp ) const;

    inline bool isEmpty() const {
      return area == 0;
    }
    inline int getArea() const {
      return area;
    }

    inline int size() const {
      return area;
    }

    friend Region operator + ( const Region &r1, const Region &r2 )
    {
      Region res ( r1 );
      res.add ( r2 );
      return res;
    }

    friend Region operator & ( const Region &r1, const Region &r2 )
    {
      Region res ( r1 );
      res.andop ( r2 );
      return res;
    }

    friend Region operator - ( const Region &r1, const Region &r2 )
    {
      Region res ( r1 );
      res.del ( r2 );
      return res;
    }

    /** Get the centroid of the region */
    void getCentroid ( double & x, double & y ) const;

    /** Set the current region to the intersection of region \c x
        and region \c y */
    void setIntersection ( const Region & x, const Region & y );
};

}
#endif
