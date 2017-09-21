CXXFLAGS = -I/usr/local/include -I/opt/local/include -g -ggdb
LDFLAGS  = -L/usr/local/lib -L/opt/local/lib

LDLIBS   =   -lopencv_video -lopencv_videoio 
LDLIBS  +=  -lopencv_xfeatures2d -lopencv_features2d
LDLIBS  +=  -lopencv_ml -lopencv_plot -lopencv_highgui
LDLIBS  +=  -lopencv_imgproc -lopencv_face -lopencv_core
LDLIBS  +=  -lopencv_imgcodecs
LDLIBS  +=  -lopencv_calib3d
LDLIBS  +=  -lopencv_flann
LDLIBS  +=  -lopencv_ximgproc

TARGETS = stereocapture

all: ${TARGETS}

clean:
	${RM} -f *.o *~ ${TARGETS}
