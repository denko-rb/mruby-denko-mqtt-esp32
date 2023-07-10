// Files from mruby-esp32 gems.
#include "../ext/mruby-esp32-mqtt/src/mrb_esp32_mqtt.c"

static mrb_value
mrb_mqtt_client_read(mrb_state *mrb, mrb_value self) {
  esp_mqtt_event_t event;
  mqtt_client_t *client = (mqtt_client_t *) DATA_PTR(self);

  mrb_value ary = mrb_ary_new(mrb);

  if(xQueueReceive(client->queue, (void*)&event, (TickType_t)(0))) {
    if(event.event_id == MQTT_EVENT_DATA) {
      // Return topic and message as array.
      mrb_value topic = mrb_str_new_static(mrb, event.topic, event.topic_len);
      mrb_value message = mrb_str_new_static(mrb, event.data, event.data_len);
      mrb_ary_push(mrb, ary, topic);
      mrb_ary_push(mrb, ary, message);
    }
  } else {
    // Return array with 2 nil.
    mrb_ary_push(mrb, ary, mrb_nil_value());
    mrb_ary_push(mrb, ary, mrb_nil_value());
  }
  return ary;
}

void
mrb_mruby_denko_mqtt_esp32_gem_init(mrb_state* mrb) {
  struct RClass *mqtt_module = mrb_define_module(mrb, "MQTT");
  struct RClass *client_class = mrb_define_class_under(mrb, mqtt_module, "Client", mrb->object_class);

  mrb_define_method(mrb, client_class, "initialize", mrb_mqtt_client_init, MRB_ARGS_REQ(2));
  mrb_define_method(mrb, client_class, "ssl=", mrb_mqtt_client_set_ssl, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, client_class, "connect", mrb_mqtt_client_connect, MRB_ARGS_NONE());
  mrb_define_method(mrb, client_class, "publish", mrb_mqtt_client_publish, MRB_ARGS_REQ(2));
  mrb_define_method(mrb, client_class, "subscribe", mrb_mqtt_client_subscribe, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, client_class, "unsubscribe", mrb_mqtt_client_unsubscribe, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, client_class, "get", mrb_mqtt_client_get, MRB_ARGS_NONE());
  mrb_define_method(mrb, client_class, "read", mrb_mqtt_client_read, MRB_ARGS_NONE());
  mrb_define_method(mrb, client_class, "disconnect", mrb_mqtt_client_disconnect, MRB_ARGS_NONE());

  mrb_define_class_under(mrb, mqtt_module, "TimeoutError", mrb->eStandardError_class);
  mrb_define_class_under(mrb, mqtt_module, "ConnectError", mrb->eStandardError_class);
  mrb_define_class_under(mrb, mqtt_module, "PublishError", mrb->eStandardError_class);
  mrb_define_class_under(mrb, mqtt_module, "SubscribeError", mrb->eStandardError_class);
  mrb_define_class_under(mrb, mqtt_module, "UnsubscribeError", mrb->eStandardError_class);
  mrb_define_class_under(mrb, mqtt_module, "DisconnectError", mrb->eStandardError_class);
}

void
mrb_mruby_denko_mqtt_esp32_gem_final(mrb_state* mrb) {
}
