#####################################################################
## tst_qmodbusdataunit Test:
#####################################################################

qt_internal_add_test(tst_qmodbusdataunit
    SOURCES
        tst_qmodbusdataunit.cpp
    PUBLIC_LIBRARIES
        Qt::SerialBus
)
