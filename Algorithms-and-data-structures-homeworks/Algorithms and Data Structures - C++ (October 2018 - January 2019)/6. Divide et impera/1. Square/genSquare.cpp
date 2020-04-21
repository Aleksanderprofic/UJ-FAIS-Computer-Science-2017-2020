#include "ArrayList.hpp"
#include "Point.hpp"


void quickSort(Point arr[], int left, int right, bool byX = true) {
     Point x = arr[(left + right) / 2];
     int l = left;
     int r = right;

     if(byX) {
          while(l < r) {
               while(arr[l].getX() < x.getX()) {
                    
                    l++;
               }
               
               while(arr[r].getX() > x.getX()) {
                    
                    r--;
               }
               
               if(l <= r) {
                    std::swap(arr[l++], arr[r--]);
               }
          }
     } else {
          while(l < r) {
               while(arr[l].getY() < x.getY()) {
                    
                    l++;
               }
               
               while(arr[r].getY() > x.getY()) {
                    
                    r--;
               }
               
               if(l <= r) {
                    std::swap(arr[l++], arr[r--]);
               }
          }
     }
     
     
     if(left < r) quickSort(arr, left, r, byX);
     if(l < right) quickSort(arr, l, right, byX);
}

void quickSort(ArrayList<Point>& arr, int left, int right, bool byX = true) {
     Point x = arr[(left + right) / 2];
     int l = left;
     int r = right;

     if(byX) {
          while(l < r) {
               while(arr[l].getX() < x.getX()) {
                    l++;
               }
               
               while(arr[r].getX() > x.getX()) {
                    r--;
               }
               
               if(l <= r) {
                    std::swap(arr[l++], arr[r--]);
               }
          }
     } else {
          while(l < r) {
               while(arr[l].getY() < x.getY()) {
                    l++;
               }
               
               while(arr[r].getY() > x.getY()) {
                    r--;
               }
               
               if(l <= r) {
                    std::swap(arr[l++], arr[r--]);
               }
          }
     }
     
     if(left < r) quickSort(arr, left, r, byX);
     if(l < right) quickSort(arr, l, right, byX);
}

Point* minLengthBruteForce(ArrayList<Point>& tab, int left, int right) {
     double minLength = 5, l = 0;
     Point p1, p2;
     Point* p = new Point[2];
     for(int i = left; i < right; i++) {
          for(int j = i + 1; j < right; j++) {
               if((l = Point::length(tab[i], tab[j])) < minLength) {
                    p1 = tab[i];
                    p2 = tab[j];
                    minLength = l;
               }
          }
     }

     p[0] = p1;
     p[1] = p2;
     return p;
}

Point* closerThanD(Point middlePoints[], int size, double d) { 
     double min = d;  // Initialize the minimum distance as d 
     Point p1, p2;
     Point* p;
     bool found = false;
     
     quickSort(middlePoints, 0, size-1, false);
     
     for (int i = 0; i < size-1; i++) {
          for (int j = i+1; j < size && (middlePoints[j].getY() - middlePoints[i].getY()) < d; j++) {
               if ((min = Point::length(middlePoints[i], middlePoints[j])) < d) {
                    d = min;
                    found = true;
                    p1 = middlePoints[i];
                    p2 = middlePoints[j];
               }
          }
     }

     if(found) {
          p = new Point[2];
          p[0] = p1;
          p[1] = p2;  
     } else p = nullptr;    
   
     return p;
} 

Point* minLengthNLogN(ArrayList<Point>& tab, int l, int r) {
     if(r-l <= 3) return minLengthBruteForce(tab, l, r);

     int mid = (r+l)/2;
     Point middlePoint = tab[mid];

     Point* left = minLengthNLogN(tab, l, mid);
     Point* right = minLengthNLogN(tab, mid, r);

     double dleft = Point::length(left[0], left[1]);
     double dright = Point::length(right[0], right[1]);
     double d, dm = -1;

     if(dleft < dright) d = dleft;
     else d = dright;

     Point lr[r-l+1];
     int i = 0;

     for(int j = l; j < r; j++) {
          if(abs(tab[j].getX() - middlePoint.getX()) < d) {
               lr[i] = tab[j];
               i++;
          }
     }

     Point* closestFromMiddle = closerThanD(lr, i, d);
     if(closestFromMiddle != nullptr) {
          dm = Point::length(closestFromMiddle[0], closestFromMiddle[1]);
          return (d < dm) ? (dleft < dright ? left : right) : closestFromMiddle;
     } else 
          return dleft < dright ? left : right;
}

Point* closestPoints(ArrayList<Point>& tab, int n) {
     quickSort(tab, 0, n-1);

     return minLengthNLogN(tab, 0, n);
}

int main(int argc, char *argv[]) {
     if(argc != 2) {
          std::cout << "Too less arguments" << std::endl;
          exit(-1);
     }

     int n = atoi(argv[1]);

     ArrayList<Point> al(n);

     Point tab[n];

     for(int i = 0; i < n; i++) {
          al[i] = Point::genPoint();
     }

     for(auto a: al)
          *a;

     std::cout << std::endl;

     Point* punkty = minLengthBruteForce(al, 0, n);
     
     double length = Point::length(punkty[0], punkty[1]);

     printf("BruteForce -> Najkrotsza droga jest między punktami: \n");
     *punkty[0];
     printf("i\n");
     *punkty[1];
     printf("i wynosi: %f\n", length);

     std::cout << std::endl;

     delete punkty;
     punkty = closestPoints(al, n);
     length = Point::length(punkty[0], punkty[1]);
     printf("NlogN -> Najkrotsza droga jest między punktami: \n");
     *punkty[0];
     printf("i\n");
     *punkty[1];
     printf("i wynosi: %f\n", length);
}