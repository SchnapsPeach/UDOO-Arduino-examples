UDOO-Arduino-examples
=====================

##### Examples and experiments with the arduino due on UDOO. Makefile projects in pure C/C++


### folder structure

<pre>
- libraries         --- Arduino libraries
- sketchbook        --- Arduino Code, all projects are based on Makefile
- linux_tools       --- Code to interact with Arduino 
</pre>

### Arduino Projects

<pre>
make compile    // builds the project
make upload     // builds the project an uploads it to arduino
make monitor    // opens a minicom session on the predefined port (minicom must be installed)
make test       // builds the project, uploads is to arduino and start the minicom session ;)
</pre>
