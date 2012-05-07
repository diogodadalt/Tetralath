TEMPLATE = app
HEADERS = \
	mainwindow.h \
    minimax.h
SOURCES = \
	main.cpp \
	mainwindow.cpp \
    minimax.cpp

QT += network webkit

RESOURCES = resources/imageanalyzer.qrc

OTHER_FILES += html/view/index.html
