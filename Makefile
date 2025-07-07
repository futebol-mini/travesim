
all:
	+make -C controllers/referee_controller
	+make -C controllers/vss_robot_controller

clean:
	+make -C controllers/referee_controller clean
	+make -C controllers/vss_robot_controller clean

