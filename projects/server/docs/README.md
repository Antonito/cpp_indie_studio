# Server's Guide

Our software provides two server's binaries. Each binary loads its configuration from a given .ini file.

The first one is called the "_connect manager_" which is a server monitoring all the game servers and game clients.

The second binary is the "_game server_", which is the core of the game.

In order to provide online services, you need to set up both a connect manager and a game server.

## Connect Manager 

### Configuration
A connect manager will load its configuration from connect_manager.ini.
Here's an example of configuration:
``` ini
[Network]
licenseServerPort=1123 # TCP (IPC)
gameServerPort=12345 # TCP
gameClientPort=12346 # TCP
publicIp=127.0.0.1 # This should be your public IPv4 address
allowInternet=no
```

### Startup

The connect manager needs a license server to be running.

``` bash
./license_manager.py # You need python3
06/07/2017 10:30:27 PM Starting license manager.
06/07/2017 10:30:27 PM Writing to file ./.license_keys
06/07/2017 10:30:27 PM Local server listening on port 1123
```
After it's started, simply start the connect manager.

``` bash
./connect_manager
```

Once everything is perfectly started, you can list or add licenses on the license_server, if needed.
Simply type "help", and you'll get a list of available commands.


>  **TL;DR** -> "_add_" adds a license, "_list_" lists all the valid licenses.

## Game Server

### Configuration

```ini
[Network]
connectManagerIp=127.0.0.1
connectManagerPort=12345
gameServerPort=12347
maxNumberClients=32
```

### Startup

Simply run the executable.
```bash
./game_server
```
The _game server_ should automatically connect to the selected _connect manager_.


## Client

```ini
# Network configuration of client
[Network]
address=127.0.0.1
port=12346
```

Clients must only know the address of the connect manager. They will connect to a game server through the connect manager.