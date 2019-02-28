#ifndef Constants_hh
#define Constants_hh

namespace Constants
{
    static const int nCh                    = 3;
    static const int nPnt                   = 1024;
    static const double dTime               = 0.3125;   // [ns]
//    static const double dTime               = 2.5;      //for only some ions 2016
    static const double Level[]             = {0.200,0.006,0.006};
    static const double ChargeLevel[]       = {0.0,150.0,150.0};
    static const double CF[]                = {0.5, 0.5, 0.5};
    static const int nPeakMax               = 100;
    static const double separTime           = 20.0; // nsec
    static const double charge_wind_left    = 10.0; //nsec
    static const double charge_wind_right   = 20.0; //nsec
    static const double posMaxLim           = 71.4; //mm
    static const double posMinLim           = 69.0; //mm
    static const double ChargeLength        = 6*16*dTime;
    static const double pCtoAu              = (1.19179e+01)/(6.23137e+04); // from USBWC pC to a.u. of the waveform analysis
}

#endif
