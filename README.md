# mruby-denko-mqtt-esp32

This gem implements MQTT connectivity for the ESP32, running Denko on mruby.

It is part of [mruby-denko](https://github.com/denko-rb/mruby-denko), and should be used through the ESP-IDF projects in that repository.

You should enable it together with the accompanying [Wi-Fi gem](https://github.com/denko-rb/mruby-denko-wifi-esp32).

## Usage

```ruby
mqtt = MQTT::Client.new('test.mosquitto.org', 1883)
# mqtt.ssl = true
# mqtt.ca = IO.read('root-ca.pem')
# mqtt.cert = IO.read('certificate.pem.crt')
# mqtt.key = IO.read('private.pem.key')
mqtt.connect

mqtt.publish("tx-topic", 'message')

# Subscribe to a topic with a callback as a block.
mqtt.subscribe("rx-topic") do |message|
  puts "Message from rx-topic: #{message}"
end

# Message receive is event driven, so main loop can do whatever.
loop do
  sleep 1
end

mqtt.disconnect
```

## Dependencies

So far, this is purely a function remapping of [mruby-esp32-mqtt](https://github.com/mruby-esp32/mruby-esp32-mqtt), from `ESP32::MQTT::Client` into `MQTT::Client`. That repo is used as a submodule.
