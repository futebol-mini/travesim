## Setup general ROS stuff
# https://registry.hub.docker.com/_/ros/

FROM ros:noetic-robot

ENV CATKIN_WS /root/catkin_ws
ENV PROJECT_NAME travesim_adapters

RUN mkdir -p ${CATKIN_WS}/src/
WORKDIR ${CATKIN_WS}

# Create catkin workspace
RUN /ros_entrypoint.sh catkin_make

COPY package.xml src/${PROJECT_NAME}/

RUN . devel/setup.sh && apt update --fix-missing && rosdep install ${PROJECT_NAME} -y

COPY . src/${PROJECT_NAME}

# Compile project
RUN /ros_entrypoint.sh catkin_make

RUN /ros_entrypoint.sh catkin_make install

RUN /ros_entrypoint.sh catkin_make run_tests

## By default, 'catkin_make run_tests' will only return non zero exit code
# if the execution of tests returned an error. To throw an error upon test
# failure, it is needed to run the following command. As we want to upload
# the tests results (success and failure), we leave this line commented
# and let the test report throw an error if needed

# RUN /ros_entrypoint.sh catkin_test_results

CMD cp -r ${CATKIN_WS}/build/test_results /var/
