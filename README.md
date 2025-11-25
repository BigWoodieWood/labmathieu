# lab5 MQTT Integration

Real-time Linux application demonstrating multi-tasking and MQTT communication for 6 modules.

## Features
- Threaded producers/consumers (existing tasks 1-4)
- Shared singleton `TPartage` extended with 6 module states
- Keyboard control: press digits 1-6 to toggle module ON/OFF and publish via MQTT
- Press `p` to toggle protection mutex behavior for existing lab logic
- Press `q` to quit
- MQTT task connects to broker and subscribes to `MODULE/#`
- Incoming messages like `MODULE/3 ON` update local state
- Outgoing publishes follow same topic/payload format
- Configuration file `mqtt.def` auto-created with default `localhost` if missing.

## Build
Compiled by VS Code task (g++). Libraries: `-lmosquitto -lmosquittopp -lpthread`.

## Runtime
Ensure Mosquitto broker is running (default localhost:1883):
```bash
sudo systemctl start mosquitto || mosquitto -v &
```
Run program:
```bash
./lab5
```
File `mqtt.def` can be edited to change broker host (re-run program to apply).

## Manual MQTT Test
Open two terminals:

1. Subscribe to all modules:
```bash
mosquitto_sub -h localhost -t 'MODULE/#' -v
```
2. Publish a change (turn module 2 ON):
```bash
mosquitto_pub -h localhost -t 'MODULE/2' -m 'ON'
```
Observe program UI updating Module 2 to ON.

Toggle a module locally (e.g. press `2`) and watch publish reflected in subscriber.

## Topics & Payloads
- Topic format: `MODULE/<n>` where `<n>` is 1..6
- Payload: `ON` or `OFF`

## Graceful Shutdown
Program stops all threads and disconnects MQTT on `q`. MQTT network loop thread stopped in destructor.

## Next Steps / Ideas
- Add resend of all module states after reconnect
- Add JSON structured status message
- Implement heartbeat topic for monitoring
- Add unit tests for parsing logic
