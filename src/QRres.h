/**
 * \file      QRres.h
 * \author    lue
 * \version   0.1
 * \date      13/02/2019
 * \brief     results of QR scan
 *
 * \details   QRres class for QR scan results and methods
 */
#include <opencv2/imgproc/imgproc.hpp>
#include <zbar.h>
using namespace cv;
using namespace zbar;

/**
 * \class QRres
 * \brief Class of QR scan results
 *
 * It contains the results of the image scan and methods to use it
*/
class QRres
{
public:
    QRres(SymbolSet qrs):qrs(qrs){};
    const SymbolSet qrs;
    void draw(Mat &frame);
};
