#####################################################################
## PeakCanBusPlugin Plugin:
#####################################################################

qt_internal_add_plugin(PeakCanBusPlugin
    OUTPUT_NAME qtpeakcanbus
    TYPE canbus
    SOURCES
        main.cpp
        peakcan_symbols_p.h
        peakcanbackend.cpp peakcanbackend.h peakcanbackend_p.h
    PUBLIC_LIBRARIES
        Qt::Core
        Qt::SerialBus
)
