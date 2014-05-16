PyNumReader
===========

Native python number reader extension module in C++ 


You need to install python-dev and necessary utils to build this extension on your machine


Build:
python setup.py build


in your python code

import hafiz_num_reader

>>> a = hafiz_num_reader.read_number(2558414)<br/>
>>> a<br/>
>>>'two million  five hundred fifty eight  thousand  four hundred fourteen  '
>>> 
