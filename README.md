
* for new app: cd ~/Sites/of/apps/work/; projectGenerator -d newApp
* nodemon -w src -x "make && make run" -e ".cpp"
* wmctrl -r "app" -b add,above;
* Modify libs/openFrameworks/app/ofAppGlutWindow.cpp
* Add GLUT_BORDERLESS|GLUT_CAPTIONLES to glutInitDisplayMode
* glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH | GLUT_ALPHA | GLUT_BORDERLESS|GLUT_CAPTIONLESS);
* Modify libs/openFrameworks/app/ofAppGLFWWindow.cpp
* Change glfwWindowHint(GLFW_DECORATED, settings.decorated);
* to be glfwWindowHint(GLFW_DECORATED, false);

