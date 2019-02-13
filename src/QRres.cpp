/**
 * \file      QRres.cpp
 * \author    lue
 * \version   0.1
 * \date      13/02/2019
 * \brief     results of QR scan
 *
 * \details   results and methods related
 */
#include <iostream>
#include "QRres.h"
using namespace std;

/**
 * \brief   add result to frame
 * \details add QR text data and rectangle around
 * \param   frame the image which has been scanned
 */
void QRres::draw(Mat& frame)
{
    for(SymbolIterator symbol = qrs.symbol_begin();
        symbol != qrs.symbol_end();
        ++symbol)
    {
        vector<Point> vp;
        // display results on standard output
        cout << "decoded " << symbol->get_type_name() << " symbol " << symbol->get_data() << '"' <<" "<< endl;
        // display results on frame rectangale and text
        int n = symbol->get_location_size();
        for(int i=0;i<n;i++)
            vp.push_back(Point(symbol->get_location_x(i),symbol->get_location_y(i)));
        RotatedRect r = minAreaRect(vp);
        Point2f pts[4];
        r.points(pts);
        putText(frame,symbol->get_data(),pts[1],FONT_HERSHEY_SIMPLEX, 1, Scalar(0,200,200), 4);
        for(int i=0;i<4;i++)
            line(frame,pts[i],pts[(i+1)%4],Scalar(255,0,0),3);
    }

}
