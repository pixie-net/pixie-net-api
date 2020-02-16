# Pixie-Net API
This project provides an application interface to the Pixie-Net. We provide the following functionality in c libraries:
* Setup FPGA
* Read and Write configuration files
* Acquire data from module
* Write data to 
  * disk
  * Kafka
  * ZeroMQ

A RESTful interface provides access to the underlying C libraries for web 
applications. We used Flask for the rest interface. The web interface allows
external programs to access the c libraries without significant overhead.  

We forked this software from XIA LLC., and is available [here](http://support.xia.com/default.asp?W772). 

# Notice
XIA LLC neither endorses nor supports the development of this project.  

# Original Disclaimer
Copyright (c) 2017 XIA LLC
All rights reserved.

Redistribution and use in source and binary forms, 
with or without modification, are permitted provided 
that the following conditions are met:

 * Redistributions of source code must retain the above
    copyright notice, this list of conditions and the 
    following disclaimer.
 * Redistributions in binary form must reproduce the
    above copyright notice, this list of conditions and the 
    following disclaimer in the documentation and/or other 
    materials provided with the distribution.
 * Neither the name of XIA LLC
    nor the names of its contributors may be used to endorse 
    or promote products derived from this software without 
    specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE 
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON 
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR 
TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF 
THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF 
SUCH DAMAGE.