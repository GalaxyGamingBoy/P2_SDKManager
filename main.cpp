#include "p2_sdkmanager.h"

#include <QApplication>

// PROJECT VERSION: v1.1.0

//!
//! \brief qMain
//! Main Function
//! \param argc the argument count
//! \param argv the arguments
//! \return the return code
//!
int main(int argc, char *argv[])
    {
        QApplication a(argc, argv);
        P2_SDKManager w;
        w.show();
        return a.exec();
    }

