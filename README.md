# SimplestQueue
A try to make something faster than kafka and an exercise.

# Dependencies
  Following facebook libraries are requiered to be compatible releases (see recommended tags) :
  1. folly v2019.06.17.00
  2. wangle v2019.06.24.00
  3. fizz v2019.06.24.00

# Buidling
  In project directory run:
  1. cmake .
  2. make

# Running
  ./SimplestQueue
  
# Testing
  In test_clients directory
  1. cmake .
  2. make
  3. ./WangleSender
  4. ./SimpleReceiver localhost 4005
