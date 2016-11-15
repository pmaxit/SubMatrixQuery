#ifndef SEGMENT_UTILS
#define SEGMENT_UTILS

#include<iostream>
#include<vector>
#include<algorithm>
#include<limits>
#include<set>
#include "Interval.h"

#define CI(x, y) std::make_pair(x, y)


struct compareInterval{
   bool operator()(const Interval &it1, const Interval &it2){
      return it1 < it2;
   }
};

template<class T>
Interval getInterval(const T &rect, int dimension){
  if(dimension == 1)
    return Interval(rect.left(), rect.right());
  else
    return Interval(rect.top(), rect.bottom());
}

template<class T>
int area(T rect){
    return (rect.bottom() - rect.top()) * (rect.right() - rect.left());
}

template<class T>
bool operator<(T& rect1, T& rect2){
    return area(rect1) < area(rect2);
}

template<class T>
std::vector<Interval> getElementaryIntervals(std::vector<T> rects, int dimension){

  std::set<Interval, compareInterval> intervals;
  std::vector<Interval> results;

  if(rects.size() == 0 ){
    return results;
  }

  // get all the end points
  std::vector<int> endPoints;

  endPoints.push_back(INT_MIN);
  for(auto rect: rects){
    Interval i = getInterval(rect, dimension);
    endPoints.push_back(i.begin);
    endPoints.push_back(i.end);
  }
  endPoints.push_back(INT_MAX);

  // sort the endPoints
  sort(endPoints.begin(), endPoints.end(), std::less<int>());

  // adding the first interval
  intervals.insert(Interval(endPoints[0],endPoints[1],false));

  for(auto it = endPoints.begin()+1; it!= endPoints.end()-1;it++){
      int beg = *it;
      int end = *(it+1);
      intervals.insert(Interval(beg, beg));
      intervals.insert(Interval(beg, false, end, false));
  }

  int last = endPoints.size()-1;

  // adding the last interval
  intervals.insert(Interval(endPoints[last-1], false, endPoints[last]));

  copy(intervals.begin(), intervals.end(), std::back_inserter(results));
  return std::move(results);
}
#endif
