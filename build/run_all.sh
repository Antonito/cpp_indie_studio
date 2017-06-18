#!/bin/sh

which tmux > /dev/null

if [ $? -eq 0 ]
then
    echo "launching script"
    tmux new-session -d -s foo 'echo license_manager.py;python3 license_manager.py;cat'
    tmux rename-window 'Foo'
    tmux select-window -t foo:0
    tmux split-window -h 'echo connect_manager;sleep 1; ./connect_manager;cat'
    tmux split-window -v -t 0 'echo game_server;sleep 2; ./game_server;cat'
    tmux -2 attach-session -t foo
  else
      echo "tmux not present !"
fi
