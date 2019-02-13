/**
 * \file      QRapp.cpp
 * \author    lue
 * \version   0.1
 * \date      13/02/2019
 * \brief     QR code application
 *
 * \details   get and display a frame with the related QRs
 */
#include <thread>
#include <iostream>
#include "QRcapture.h"
#include "QRres.h"
using namespace std;

/**
 * \class QRapp
 * \brief Class of QR main thread
 *
 * Initialize, start and stop a thread which capture and display the image with the related QRs
*/
class QRapp
{
public:
    QRapp(char * videoFile):strRUNNING(false),capture(videoFile) {}
    QRapp():strRUNNING(false),capture(0) {}
    int init()
    {
        // initialize capture
        if (capture.init()!=0) return -1;
        // create "QRcode" window
        namedWindow("QRcode",CV_WINDOW_AUTOSIZE);
        return 0;
    }
    int start()
    {
        strRUNNING=true;
        // start scan and display
        gqr = new thread(&QRapp::getQR,this);
        return gqr==NULL?-1:1;
    }
    void stop() {
        strRUNNING=false;
    }
    void waitstop() {
        // wait the end of the thread
        if (strRUNNING) gqr->join();
        delete gqr;
    }
private:
    thread *gqr;
    bool strRUNNING;
    QRcapture capture;
    void getQR()
    {
        while (strRUNNING)
        {
            Mat frame;
            // get the frame from video
            bool bSuccess = capture.read(frame);
            if (!bSuccess)
            {
                cout << "Cannot read a frame from video stream" << endl;
                break;
            }
            // get the QRs
            QRres QRs(capture.getQR(frame));
            // show results
            QRs.draw(frame);
            // show the frame in "QRcode" window
            imshow("QRcode", frame);
            //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
            if ((char)waitKey(30) == 27)             {
                cout << "esc key is pressed by user" << endl;
                strRUNNING=false;
            }
        }
    }
};

int main(int argc, char* argv[])
{
    QRapp *app;

    // argument is a video file
    if (argc>1)
        app = new QRapp(argv[1]);
    else
        app = new QRapp;

    if (!app->init())
        app->start();

    // SOME STUFF MAY BE ADDED HERE

    app->waitstop();

    return 0;
}
