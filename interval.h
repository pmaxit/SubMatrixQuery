#ifndef SEGMENT_INTERVAL
#define SEGMENT_INTERVAL

#include<ostream>

struct Interval{
  int begin;
  int end;
  bool isBeginInclusive;
  bool isEndInclusive;

  Interval(int b, int e):Interval(b, true, e, true){}
  Interval(int b, bool isBeginInclusive, int e, bool isEndInclusive):begin(b), isBeginInclusive(isBeginInclusive), end(e), isEndInclusive(isEndInclusive){}
  Interval(int b, bool isBeginInclusive, int e):Interval(b, isBeginInclusive, e, true ){}
  Interval(int b, int e, bool isEndInclusive):Interval(b, true, e, isEndInclusive){}
  Interval(const Interval &b):Interval(b.begin, b.isBeginInclusive, b.end, b.isEndInclusive){}

  static Interval range(Interval first, Interval second){
    return Interval(first.begin, first.isBeginInclusive, second.end, second.isEndInclusive);
  }

  friend std::ostream &operator<<(std::ostream& out, const Interval &interval){
    out<<"[" <<interval.begin<<" , "<<interval.end <<"]";
    return out;
  }


  bool contains(int point){

    return ((isBeginInclusive && begin == point) ||
            (begin <= point && end >= point)     ||
            (isEndInclusive && end == point)) ;
  }

  bool intersects(Interval &other){
    //std::cout<<"CHECKING INTERSECTION "<<*this<<"  "<<other<<"  "<<(compare(this->begin, other.end) && compare(other.begin,this->end))<<std::endl;
    bool compareAImplicit = this->isBeginInclusive && other.isBeginInclusive;
    bool compareBImplicit = this->isEndInclusive && other.isBeginInclusive;
    return compare(compareAImplicit, this->begin, other.end) && compare(compareBImplicit , other.begin,this->end);
  }

  bool contains(Interval other){
    bool compareBeginPoints = this->isBeginInclusive || !other.isBeginInclusive;
    bool compareEndPoints   = this->isEndInclusive || !other.isEndInclusive;
    return compare(compareBeginPoints, this->begin, other.begin) && compare(compareEndPoints, other.end, this->end);
  }

  bool compare(bool compFlag , int a , int b){
    return compFlag? a <= b : a < b ;
  }

  bool operator<(const Interval &interval) const{
    if(this->begin != interval.begin)
      return this->begin < interval.begin;

    if(this->end != interval.end)
      return this->end < interval.end;

    return false;
  }
};

#endif
