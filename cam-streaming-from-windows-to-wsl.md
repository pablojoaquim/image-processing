If you want to get the stream from the webcam in WSL there're several ways to do it, but the most effective is to stream from windows to an url, and then read the stream in the application running in WSL from than url.

To do this, is necessary to install ffmpeg in windows.
- Download ffmpeg from https://www.gyan.dev/ffmpeg/builds/
- Uncompress and add the /bin folder to the windows PATH
- List all the available cameras with: 
  ```
  ffmpeg -list_devices true -f dshow -i dummy
  ```
- It should be something like "Integrated Camera"
- To read the frames from WSL is necessary to know which is the network address of the windows machine and the WSL machine. To do this execute from WSL and look for the eth0 address (i.e. 172.27.0.1) and the WSL machine address:
  ``` 
  ip route
  ```
- Stream the webcam in MJPEG to port 8090:      
  ```
  ffmpeg -f dshow -i video="Integrated Camera" -an -vcodec libx264 -preset ultrafast -tune zerolatency -x264-params keyint=15:scenecut=0:repeat-headers=1 -fflags nobuffer -flags low_delay -flush_packets 1 -f mpegts udp://172.27.15.197:5000
  ```

- To open the stream using OpenCV:
  ``` 
  cv::VideoCapture cap("udp://172.27.0.1:5000", cv::CAP_FFMPEG);
  ```




  
