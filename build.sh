cd 3rdparty;
cd glog-0.3.3;./configure && make;
cd ../libev-4.22;./configure && make;
cd ../..;
cmake;
make;
