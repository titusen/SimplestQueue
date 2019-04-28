# SimplestQueue
A try to make something faster than kafka and an exercise.

# Dependencies
  Following facebook libraries are reqiered to be in the same release (recommended v2019.03.04.00) :
  1. folly
  2. wangle
  3. fizz

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
