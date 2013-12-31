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

<dl>
  <dt>make compile</dt>
  <dd>Builds the project.</dd>

  <dt>make upload</dt>
  <dd>builds the project an uploads it to arduino</dd>
  <dt>make monitor</dt>
  <dd>opens a minicom session on the predefined port (minicom must be installed)</dd>
  <dt>make test</dt>
  <dd>builds the project, uploads is to arduino and starts the minicom session ;)</dd>
</dl>
