QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

ICON = ../images/icon/smartcalc.png

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../controller/credit_calc/controller_credit_calc.cc \
    ../model/credit_calc/model_credit_calc.cc \
    ../view/calc/qcustomplot/qcustomplot.cc \
    ../view/calc/view_validator.cc \
    ../view/credit_calc/view_credit_calc.cpp \
    main.cpp \
    ../controller/calc/controller_calc.cc \
    ../model/calc/model_calc.cc \
    ../model/calc/model_polish.cc \
    ../model/calc/model_validator.cc \
    ./../view/calc/view_calc.cc

HEADERS += \
    ../controller/calc/s21_calc_controller.h \
    ../controller/credit_calc/s21_credit_calc_controller.h \
    ../model/calc/s21_calc_model.h \
    ../model/credit_calc/s21_credit_calc_model.h \
    ../view/calc/qcustomplot/qcustomplot.h \
    ../view/credit_calc/s21_credit_calc_view.h \
    ./../view/calc/s21_calc_view.h

FORMS += \
    ../view/credit_calc/credit_calc.ui \
    ./../view/calc/calc.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
