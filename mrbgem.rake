require_relative "mrblib/version"

MRuby::Gem::Specification.new('mruby-denko-mqtt-esp32') do |spec|
  spec.license = 'MIT'
  spec.authors = 'vickash'
  spec.version = MQTT::VERSION

  # Need to make some things conditional for ESP32 variants in future.
  if spec.cc.defines.include?("ESP_PLATFORM")
  end
  
  # Include files in the right order.
  spec.rbfiles = [
    "#{dir}/mrblib/mqtt.rb",
  ]
end
