// Copyright 2004-present Facebook. All Rights Reserved.

#pragma once

#include <map>
#include "TestSubscriber.h"
#include "TestSuite.h"
#include "src/Payload.h"
#include "src/ReactiveStreamsCompat.h"
#include "src/StandardReactiveSocket.h"

namespace folly {
class EventBase;
}

namespace reactivesocket {

class StandardReactiveSocket;

namespace tck {

class SubscribeCommand;
class RequestCommand;
class AwaitCommand;
class CancelCommand;
class AssertCommand;

class TestInterpreter {
 public:
  TestInterpreter(const Test& test, StandardReactiveSocket& reactiveSocket);

  bool run();

 private:
  void handleSubscribe(const SubscribeCommand& command);
  void handleRequest(const RequestCommand& command);
  void handleAwait(const AwaitCommand& command);
  void handleCancel(const CancelCommand& command);
  void handleAssert(const AssertCommand& command);

  std::shared_ptr<TestSubscriber> createTestSubscriber(const std::string& id);
  std::shared_ptr<TestSubscriber> getSubscriber(const std::string& id);

  StandardReactiveSocket* reactiveSocket_;
  const Test& test_;
  std::map<std::string, std::string> interactionIdToType_;
  std::map<std::string, std::shared_ptr<TestSubscriber>> testSubscribers_;
};

} // tck
} // reactivesocket
