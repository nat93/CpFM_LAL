#ifndef Constants_hh
#define Constants_hh

namespace Constants
{
    static const int nCh = 3;
    static const int nPnt = 1024;
    static const double nVsTopC = (7188.0/1.345);
    static const double dTime = 0.3125; // for protons 2016
    //static const double dTime = 2.5; //for ions 2016
    static const double Level[] = {0.200,0.006,0.006};
    static const double ChargeLevel[] = {0.0,150.0,150.0};
    static const double CF[] = {0.5, 0.5, 0.5};
    static const int nPeakMax = 100;
    static const double separTime = 20.0; // nsec
    static const double charge_wind_left = 10.0; //nsec
    static const double charge_wind_right = 20.0; //nsec
    static const double posMaxLim = 71.4; //mm
    static const double posMinLim = 69.0; //mm
}

#endif
