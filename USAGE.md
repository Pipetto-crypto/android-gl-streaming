## Setup streaming environment
### Server setup
- Build Server app using Android Studio with NDK installed.
- Install server APK.

### Client setup
```
cd /path/to/android-gl-streaming/gl_client

# Build the client
make

# Install the client libraries to /usr/local/lib/gl-streaming
make install

# To run OpenGL programs, build GL4ES and copy libGL.so.1 to somewhere.

# Override system libGLESv2.so.2, libEGL.so.1 and libGL.so.1
export LD_LIBRARY_PATH=$PATH_TO_STREAMINGLIB:$LD_LIBRARY_PATH
```

## Launch streaming!
### Launch server
- Do as title: Launch server.
- Enter server port and client address, or leave empty for default values.

### Launch client
- Run a program that requires OpenGL ES or OpenGL.

## Variables on compile
- (Server) `GL_DEBUG`: enable debug log write to `/sdard/mthr_log.txt`. Disabled by default.
